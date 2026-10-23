#!/usr/bin/env python3
"""weekNN/ と debugging/ 以下の .c/.h を「BOM 付き UTF-8・LF・末尾改行あり」にそろえる。

BOM を付けると，/utf-8 を指定していない Visual Studio のプロジェクトへ
ファイルをコピーしても日本語コメントが正しく読まれる（C4819 や文字化けを防ぐ）。
_ で始まるフォルダ（ビルドしないコード）も対象にする。ふだんは tools/update_generated.py から実行する。
    python3 tools/normalize_sources.py          # 修正する
    python3 tools/normalize_sources.py --check  # 確認だけ（CI 用）
    python3 tools/normalize_sources.py week05   # 指定した回（または debugging）だけ
"""
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from projects import ROOT, group_dirs  # noqa: E402

BOM = b"\xef\xbb\xbf"


def normalized(data: bytes) -> bytes:
    body = data[len(BOM):] if data.startswith(BOM) else data
    body.decode("utf-8")  # UTF-8 でなければ例外
    body = body.replace(b"\r\n", b"\n")
    if not body.endswith(b"\n"):
        body += b"\n"
    return BOM + body


def run(check=False, groups=None):
    """groups（回のフォルダ。省略時はすべて）の .c/.h をそろえる。check なら書き換えない。
    すでにそろっている（または書き換えた）なら True。"""
    if groups is None:
        groups = group_dirs()
    bad, not_utf8 = [], []
    paths = sorted({p for g in groups for p in g.rglob("*") if p.suffix in (".c", ".h") and p.is_file()})
    for path in paths:
        data = path.read_bytes()
        try:
            fixed = normalized(data)
        except UnicodeDecodeError as e:
            not_utf8.append(f"{path.relative_to(ROOT).as_posix()}（{e.start} バイト目）")
            continue
        if fixed != data:
            bad.append(path.relative_to(ROOT).as_posix())
            if not check:
                path.write_bytes(fixed)
    for p in not_utf8:
        print(f"[NG] UTF-8 ではない（Shift_JIS などで保存した？ エディタで UTF-8 にして保存し直す）: {p}")
    for p in bad:
        print(("[NG] 要修正: " if check else "修正: ") + p)
    if not_utf8:
        return False
    if not bad:
        print(f"ソースの BOM・改行: そろっている（{len(paths)} ファイル）")
    elif check:
        print("python3 tools/update_generated.py（または tools/normalize_sources.py）でそろえる")
    return not (check and bad)


def main():
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    args = sys.argv[1:]
    if any(a in ("-h", "--help") for a in args):
        print(__doc__)
        return 0
    unknown = [a for a in args if a.startswith("-") and a != "--check"]
    if unknown:
        print(f"不明なオプション: {' '.join(unknown)}")
        return 2
    names = [a.strip("/\\") for a in args if not a.startswith("-")]
    groups = None
    if names:
        known = {g.name: g for g in group_dirs()}
        missing = [n for n in names if n not in known]
        if missing:
            print(f"回のフォルダがない: {' '.join(missing)}（weekNN または debugging）")
            return 2
        groups = [known[n] for n in names]
    return 0 if run("--check" in args, groups) else 1


if __name__ == "__main__":
    sys.exit(main())
