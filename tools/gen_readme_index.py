#!/usr/bin/env python3
"""ルートの README.md の目次（各回とデバッグの題材の表）を weekNN/・debugging/ の内容から作り直す。

<!-- WEEK-TABLE:BEGIN --> と <!-- WEEK-TABLE:END --> の間を置き換える。
  - 各回の行: 回（weekNN/README.md へのリンク）・テーマ（weekNN/README.md の 1 行目の（）の中）・
    プロジェクト（.c のあるフォルダ）・テスト数・演習ページ
  - デバッグの題材の行: debugging/README.md へのリンク・題材数・テスト数
  - 合計の行: テスト数の合計（ctest -N の総数と同じ）
テスト数は tests/*.out と variants/tests/*.out の数。ふだんは tools/update_generated.py から実行する。
    python3 tools/gen_readme_index.py          # 作り直す
    python3 tools/gen_readme_index.py --check  # 書き換えずに，最新でなければ失敗する
"""
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from projects import (DEBUGGING, ROOT, count_tests, has_sources, project_dirs,  # noqa: E402
                      week_dirs, write_text)

README = ROOT / "README.md"
BEGIN, END = "<!-- WEEK-TABLE:BEGIN -->", "<!-- WEEK-TABLE:END -->"


def table():
    rows = ["| 回 | テーマ | プロジェクト | テスト数 | 演習ページ |", "| --- | --- | --- | ---: | --- |"]
    total = 0
    for week in week_dirs():
        n = int(week.name[4:])
        title = (week / "README.md").read_text(encoding="utf-8").splitlines()[0]
        m = re.search(r"（(.*)）", title)
        theme = m.group(1) if m else ""
        projects = [p for p in project_dirs(week) if has_sources(p)]
        tests = sum(count_tests(p) for p in projects)
        total += tests
        rows.append(f"| [第{n}回]({week.name}/README.md) | {theme} | {'，'.join(p.name for p in projects)} | {tests} "
                    f"| [ex{n:02d}](https://t-yokoga.github.io/softprac1/ex{n:02d}.html) |")
    debugging = ROOT / DEBUGGING
    if debugging.is_dir():
        topics = [p for p in project_dirs(debugging) if has_sources(p)]
        tests = sum(count_tests(p) for p in topics)
        total += tests
        rows.append(f"| [デバッグの題材]({DEBUGGING}/README.md) | バグ入りのプログラム（TA 用） "
                    f"| {len(topics)} 題 | {tests} | |")
    rows.append(f"| | | **合計** | **{total}** | |")
    return rows, total


def run(check=False):
    """生成する。check なら書き換えずに確かめる。最新（または書き換えた）なら True。"""
    rows, total = table()
    text = README.read_bytes().decode("utf-8").replace("\r\n", "\n")
    if BEGIN not in text or END not in text:
        print(f"[NG] README.md に {BEGIN} と {END} がない")
        return False
    start, end = text.index(BEGIN) + len(BEGIN), text.index(END)
    new = text[:start] + "\n" + "\n".join(rows) + "\n" + text[end:]
    summary = f"テスト {total} 件"
    if write_text(README, new, check):
        print(f"README.md の目次: 最新（{summary}）")
        return True
    if check:
        print("[NG] README.md の目次が最新ではない（python3 tools/update_generated.py で作り直す）")
        return False
    print(f"README.md の目次: 作り直した（{summary}）")
    return True


def main():
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    if any(a in ("-h", "--help") for a in sys.argv[1:]):
        print(__doc__)
        return 0
    return 0 if run("--check" in sys.argv[1:]) else 1


if __name__ == "__main__":
    sys.exit(main())
