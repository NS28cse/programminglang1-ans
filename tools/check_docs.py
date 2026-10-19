#!/usr/bin/env python3
"""文書（.md）の整合を確かめる（CI 用）。

  1. リンク: すべての .md の相対リンク（[文字](先)・![画像](先)・[名前]: 先・href="先"・src="先"）について，
     リンク先のファイル・フォルダがあること（大文字・小文字まで一致。リポジトリの外は不可）。
     #見出し が付いていれば，リンク先の .md（# だけなら同じファイル）にその見出しがあること
     （GitHub と同じ規則で見出しから id を作る: 小文字にし，文字・数字・_・-・空白以外を除き，空白を - に。
     同じ見出しが続くと -1，-2 を付ける。<a id="..."> なども数える）。
     http(s): などの外部リンク，コードブロック・`インラインコード`・<!-- コメント --> の中は対象外。
  2. デバッグの題材の一覧: debugging/README.md の表に debugging/ のすべての題材（Bug で始まるフォルダ）が
     [Bug名](Bug名/README.md) の形でちょうど 1 回ずつ載っていて，余分な行がないこと。

    python3 tools/check_docs.py
"""
import os
import pathlib
import re
import subprocess
import sys
import unicodedata
import urllib.parse

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from projects import DEBUGGING, ROOT, project_dirs  # noqa: E402

SKIP_DIRS = {".git", "out", "build", "node_modules", "__pycache__"}


def markdown_files():
    """リポジトリの .md（git が無視するものを除く）。git がなければフォルダを走査する。"""
    try:
        r = subprocess.run(["git", "ls-files", "-z", "--cached", "--others", "--exclude-standard", "--", "*.md"],
                           cwd=ROOT, capture_output=True, check=True)
        files = [ROOT / f for f in r.stdout.decode("utf-8").split("\0") if f]
        return sorted(f for f in files if f.is_file())
    except (OSError, subprocess.CalledProcessError):
        files = []
        for dirpath, dirnames, filenames in os.walk(ROOT):
            dirnames[:] = [d for d in dirnames if d not in SKIP_DIRS]
            files += [pathlib.Path(dirpath) / f for f in filenames if f.endswith(".md")]
        return sorted(files)


def text_lines(path: pathlib.Path):
    """(行番号, 行) を返す。YAML の前付け・コードブロック・HTML コメントの中は空にする。"""
    lines = path.read_bytes().decode("utf-8-sig").replace("\r\n", "\n").split("\n")
    out = []
    fence = None
    in_comment = False
    front = bool(lines) and lines[0].strip() == "---"
    for i, line in enumerate(lines, 1):
        if front:
            if i > 1 and line.strip() in ("---", "..."):
                front = False
            out.append((i, ""))
            continue
        m = re.match(r" {0,3}(`{3,}|~{3,})", line)
        if fence:
            if m and m.group(1)[0] == fence[0] and len(m.group(1)) >= len(fence) and not line.strip(" `~"):
                fence = None
            out.append((i, ""))
            continue
        if m and not in_comment:
            fence = m.group(1)
            out.append((i, ""))
            continue
        # HTML コメント（複数行にわたるものも）を除く
        kept = ""
        rest = line
        while rest:
            if in_comment:
                end = rest.find("-->")
                if end < 0:
                    rest = ""
                else:
                    in_comment = False
                    rest = rest[end + 3:]
            else:
                start = rest.find("<!--")
                if start < 0:
                    kept += rest
                    rest = ""
                else:
                    kept += rest[:start]
                    in_comment = True
                    rest = rest[start + 4:]
        out.append((i, kept))
    return out


def strip_code_spans(line: str):
    """`インラインコード` を同じ長さの空白に置き換える（中のリンクらしきものを無視するため）。"""
    return re.sub(r"(`+)(.+?)\1", lambda m: " " * len(m.group(0)), line)


def slug(heading: str):
    """GitHub が見出しに付ける id（github-slugger と同じ規則）。"""
    text = heading.lower()
    kept = []
    for c in text:
        cat = unicodedata.category(c)
        if cat[0] in "LMN" or cat == "Pc" or c in "- ":
            kept.append(c)
    return "".join(kept).replace(" ", "-")


def heading_text(raw: str):
    """見出しの Markdown を表示される文字列に近づける（リンク・コード・強調・HTML タグを外す）。"""
    t = re.sub(r"!\[([^\]]*)\]\([^)]*\)", r"\1", raw)
    t = re.sub(r"\[([^\]]*)\]\([^)]*\)", r"\1", t)
    t = re.sub(r"(`+)(.+?)\1", lambda m: m.group(2).strip(), t)
    t = re.sub(r"<[^>]+>", "", t)
    t = re.sub(r"(\*+|(?<!\w)_+|_+(?!\w))", "", t)
    return t.strip()


_anchor_cache = {}


def anchors(path: pathlib.Path):
    """.md の見出しから GitHub が作る id の集合。"""
    if path not in _anchor_cache:
        ids = set()
        count = {}
        for _, line in text_lines(path):
            m = re.match(r" {0,3}#{1,6}(?:[ \t]+(.*?))?[ \t]*$", line)
            if m:
                raw = re.sub(r"[ \t]+#+[ \t]*$", "", m.group(1) or "")
                base = slug(heading_text(raw))
                n = count.get(base, 0)
                count[base] = n + 1
                ids.add(base if n == 0 else f"{base}-{n}")
            for a in re.findall(r"""<[a-zA-Z][^>]*\s(?:id|name)\s*=\s*["']([^"']+)["']""", line):
                ids.add(a)
        _anchor_cache[path] = ids
    return _anchor_cache[path]


def link_targets(line: str):
    """1 行の中のリンク先を返す（インラインコードは除いておくこと）。"""
    targets = []
    # [文字](先) と ![画像](先)。先の中の ( ) は対になっていれば含める
    for m in re.finditer(r"\]\(", line):
        i = m.end()
        while i < len(line) and line[i] in " \t":
            i += 1
        if i < len(line) and line[i] == "<":
            end = line.find(">", i)
            if end > 0:
                targets.append(line[i + 1:end])
            continue
        depth = 0
        j = i
        while j < len(line):
            c = line[j]
            if c == "\\" and j + 1 < len(line):
                j += 2
                continue
            if c in " \t":
                break
            if c == "(":
                depth += 1
            elif c == ")":
                if depth == 0:
                    break
                depth -= 1
            j += 1
        if j < len(line) and line[j] in ") \t" and j > i:
            targets.append(line[i:j])
    # 参照の定義 [名前]: 先
    m = re.match(r" {0,3}\[[^\]]+\]:\s*<?([^\s>]+)>?", line)
    if m:
        targets.append(m.group(1))
    # HTML の href・src
    targets += re.findall(r"""\b(?:href|src)\s*=\s*["']([^"']+)["']""", line)
    return targets


def exists_exact(path: pathlib.Path):
    """path があり，各部分の大文字・小文字も一致するか（Windows・macOS でも GitHub と同じ判定にする）。"""
    try:
        rel = path.relative_to(ROOT)
    except ValueError:
        return False
    cur = ROOT
    for part in rel.parts:
        try:
            if part not in os.listdir(cur):
                return False
        except (NotADirectoryError, FileNotFoundError):
            return False
        cur = cur / part
    return True


def check_links(files):
    errors = []
    n_links = 0
    for md in files:
        rel_md = md.relative_to(ROOT).as_posix()
        for lineno, line in text_lines(md):
            for target in link_targets(strip_code_spans(line)):
                if re.match(r"[A-Za-z][A-Za-z0-9+.-]*:", target) or target.startswith("//"):
                    continue   # 外部リンク（http:・https:・mailto: など）
                n_links += 1
                where = f"{rel_md}:{lineno}: {target}"
                path_part, _, fragment = target.partition("#")
                path_part = urllib.parse.unquote(path_part.split("?")[0])
                fragment = urllib.parse.unquote(fragment)
                if path_part:
                    base = ROOT if path_part.startswith("/") else md.parent
                    dest = pathlib.Path(os.path.normpath(base / path_part.lstrip("/")))
                    if not exists_exact(dest):
                        inside = dest == ROOT or ROOT in dest.parents
                        errors.append(f"{where}: {'リンク先がない' if inside else 'リポジトリの外を指している'}")
                        continue
                else:
                    dest = md
                if fragment and dest.suffix.lower() == ".md" and dest.is_file():
                    if fragment.lower() not in anchors(dest):
                        errors.append(f"{where}: 見出し #{fragment} が {dest.relative_to(ROOT).as_posix()} にない")
    return errors, n_links


def check_debugging_list():
    debugging = ROOT / DEBUGGING
    readme = debugging / "README.md"
    if not debugging.is_dir():
        return [], 0
    if not readme.is_file():
        return [f"{DEBUGGING}/README.md がない"], 0
    errors = []
    dirs = project_dirs(debugging)
    for d in dirs:
        if not d.name.startswith("Bug"):
            errors.append(f"{DEBUGGING}/{d.name}: 題材のフォルダ名は Bug で始める（全回のプロジェクト名と重ならないように）")
    listed = []
    for lineno, line in text_lines(readme):
        if not line.lstrip().startswith("|"):
            continue
        for text, target in re.findall(r"\[([^\]]+)\]\(([^)#]+)/README\.md\)", line):
            if target.startswith("Bug") or text.startswith("Bug"):
                if text != target:
                    errors.append(f"{DEBUGGING}/README.md:{lineno}: 表示 {text} とリンク先 {target}/ が違う")
                listed.append(target)
    names = [d.name for d in dirs if d.name.startswith("Bug")]
    for name in sorted(set(names) - set(listed)):
        errors.append(f"{DEBUGGING}/README.md の題材の一覧に {name} がない")
    for name in sorted(set(listed) - set(names)):
        errors.append(f"{DEBUGGING}/README.md の題材の一覧の {name} に当たるフォルダ {DEBUGGING}/{name}/ がない")
    for name in sorted({n for n in listed if listed.count(n) > 1}):
        errors.append(f"{DEBUGGING}/README.md の題材の一覧に {name} が {listed.count(name)} 回ある")
    return errors, len(names)


def main():
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    if any(a in ("-h", "--help") for a in sys.argv[1:]):
        print(__doc__)
        return 0
    files = markdown_files()
    link_errors, n_links = check_links(files)
    print(f"リンク: {len(files)} ファイルの相対リンク {n_links} 件を確認")
    list_errors, n_topics = check_debugging_list()
    print(f"デバッグの題材の一覧: {n_topics} 題を確認")
    errors = link_errors + list_errors
    for e in errors:
        print("[NG]", e)
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
