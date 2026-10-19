#!/usr/bin/env python3
"""コミットの前に実行する仕上げを 1 本にまとめたもの。次の順に実行する:

  1. normalize_sources.py  weekNN/・debugging/ の .c/.h を BOM 付き UTF-8・LF・末尾改行ありにそろえる
  2. gen_launch_vs.py      Visual Studio（File > Open > Folder）の起動構成 .vs/launch.vs.json を作り直す
  3. gen_readme_index.py   ルート README.md の「各回の解答と題材の表」（テスト数を含む）を作り直す

    python3 tools/update_generated.py          # そろえる・作り直す
    python3 tools/update_generated.py --check  # 書き換えずに確かめ，直すべきものがあれば失敗する（CI 用）
"""
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import gen_launch_vs  # noqa: E402
import gen_readme_index  # noqa: E402
import normalize_sources  # noqa: E402


def main():
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    args = sys.argv[1:]
    if any(a in ("-h", "--help") for a in args):
        print(__doc__)
        return 0
    unknown = [a for a in args if a != "--check"]
    if unknown:
        print(f"不明な引数: {' '.join(unknown)}")
        return 2
    check = "--check" in args
    results = [normalize_sources.run(check), gen_launch_vs.run(check), gen_readme_index.run(check)]
    return 0 if all(results) else 1


if __name__ == "__main__":
    sys.exit(main())
