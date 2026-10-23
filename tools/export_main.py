#!/usr/bin/env python3
"""ta ブランチの解答と解説を main ブランチの作業ツリーへ写す（main に反映するときに使う）。

    git fetch origin
    git worktree add ../main-sync origin/main --detach   # main の作業ツリーを別のフォルダに用意する（初回だけ。以後は git switch --detach origin/main）
    python3 tools/export_main.py ../main-sync            # 写す（main だけにあって ta にないファイルは消す）
    python3 tools/export_main.py ../main-sync --check    # 写さずに違いだけを表示する（違いがあれば終了コード 1）

写すもの（main と ta で同じ内容にするもの。git が管理しているファイルだけ）:
  - README.md，.gitattributes（改行コードの扱い）
  - weekNN/ 以下のすべて。ただし次を除く（ta だけに置くもの）:
      tests/・variants/（自動テスト），run.args（IDE の既定の引数），
      プロジェクトフォルダの CMakeLists.txt（書き換えた版の定義。main は MAIN_CMAKE の 3 つだけを独自の内容で持つ）
写さないもの: ルートの CMakeLists.txt・.gitignore（main は最小限の独自の内容），TA.md・ta-guide/・debugging/・tools/ など ta だけのもの。

main に新しいプロジェクトフォルダの CMakeLists.txt が要るとき（ライブラリなど，フォルダ直下の *.c をまとめる規則でビルドできないとき）は，
main で手で書き，MAIN_CMAKE に加える。
"""
import pathlib
import re
import shutil
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from projects import ROOT, tree_kind  # noqa: E402

# main が独自の内容で持つプロジェクトフォルダの CMakeLists.txt
MAIN_CMAKE = {
    "week12/CalcLib/CMakeLists.txt",
    "week12/CalcApp/CMakeLists.txt",
    "week13/DynamicVectorFail/CMakeLists.txt",
}
TA_ONLY = re.compile(r"^week\d\d/[^/]+/(tests/|variants/|run\.args$|CMakeLists\.txt$)")


def shared(path: str):
    if path in ("README.md", ".gitattributes"):
        return True
    return re.match(r"^week\d\d/", path) is not None and not TA_ONLY.match(path)


def tracked(root: pathlib.Path):
    out = subprocess.run(["git", "-C", str(root), "ls-files", "-z"], capture_output=True, check=True).stdout
    return {p for p in out.decode("utf-8").split("\0") if p}


def main():
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    args = [a for a in sys.argv[1:] if a != "--check"]
    if len(args) != 1 or args[0] in ("-h", "--help"):
        print(__doc__)
        return 0 if args and args[0] in ("-h", "--help") else 2
    check = "--check" in sys.argv[1:]
    dest = pathlib.Path(args[0]).resolve()
    kind = tree_kind(dest) if dest.is_dir() else None
    if dest == ROOT or not (dest / ".git").exists() or kind != "main":
        what = {"ta": "ta の作業ツリー", "practice": "practice の作業ツリー（cmake/RunTest.cmake・.vs/launch.vs.json がある）"}.get(kind, "main の作業ツリーではない")
        print(f"[NG] {dest} は {what}。main の作業ツリー（git worktree add <フォルダ> origin/main --detach）を渡す。何も書き換えていない")
        return 2

    # 写すのは commit 済みの内容だけにする（作業ツリーに未 commit の変更があれば止める）
    dirty = subprocess.run(["git", "-C", str(ROOT), "status", "--porcelain", "--", "README.md", ".gitattributes", "week*"],
                           capture_output=True, text=True, check=True).stdout.strip()
    if dirty:
        print("[NG] ta の作業ツリーの README.md・.gitattributes・weekNN/ に commit していない変更がある。commit してから写す:\n" + dirty)
        return 2
    src_files = {p for p in tracked(ROOT) if shared(p)}
    dest_files = {p for p in tracked(dest) if shared(p) and p not in MAIN_CMAKE}
    changed = []
    for p in sorted(src_files):
        s, d = ROOT / p, dest / p
        if not d.exists() or s.read_bytes() != d.read_bytes():
            changed.append(("更新" if d.exists() else "追加", p))
            if not check:
                d.parent.mkdir(parents=True, exist_ok=True)
                shutil.copyfile(s, d)
    for p in sorted(dest_files - src_files):
        changed.append(("削除", p))
        if not check:
            (dest / p).unlink()

    for kind, p in changed:
        print(f"{kind}: {p}")
    for p in sorted(tracked(ROOT)):
        if re.match(r"^week\d\d/[^/]+/CMakeLists\.txt$", p) and p not in MAIN_CMAKE and \
                not re.search(r"softprac_add_program\(", (ROOT / p).read_text(encoding="utf-8")):
            print(f"[注意] {p} は softprac_add_program を使っていない。main でフォルダの規則どおりにビルドできるか確かめる")
    if check:
        print(f"違い: {len(changed)} 件" if changed else "違いはない")
        return 1 if changed else 0
    print(f"{dest} へ {len(changed)} 件を反映した。main で git diff を確かめ，ビルドしてから commit する")
    return 0


if __name__ == "__main__":
    sys.exit(main())
