#!/usr/bin/env python3
"""各回の表を weekNN/・debugging/ の内容から作り直す。

<!-- WEEK-TABLE:BEGIN --> と <!-- WEEK-TABLE:END --> の間を置き換える。
  - README.md（main と共通）の「各回の解答」: 回（weekNN/README.md へのリンク）・テーマ（weekNN/README.md の 1 行目の（）の中）・
    プロジェクト（.c のあるフォルダ）・演習ページ
  - TA.md（ta ブランチの入口）の「各回の解答と題材の表」: 上に加えてテスト数，デバッグの題材の行（題材数・テスト数），
    合計の行（テスト数の合計。ctest -N の総数と同じ）
テスト数は tests/*.out と variants/tests/*.out の数。ふだんは tools/update_generated.py から実行する。
README.md は main ブランチと同じ内容にする。ここで README.md が変わったら，main でも同じように直す（CONTRIBUTING.md の「ブランチ」）。
    python3 tools/gen_readme_index.py          # 作り直す
    python3 tools/gen_readme_index.py --check  # 書き換えずに，最新でなければ失敗する
"""
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from projects import (DEBUGGING, ROOT, count_tests, has_sources, project_dirs,  # noqa: E402
                      week_dirs, write_text)

BEGIN, END = "<!-- WEEK-TABLE:BEGIN -->", "<!-- WEEK-TABLE:END -->"


def weeks():
    """(weekNN フォルダ, 回の番号, テーマ, プロジェクトフォルダの一覧) を回の順に返す。"""
    for week in week_dirs():
        title = (week / "README.md").read_text(encoding="utf-8").splitlines()[0]
        m = re.search(r"（(.*)）", title)
        yield week, int(week.name[4:]), m.group(1) if m else "", [p for p in project_dirs(week) if has_sources(p)]


def exercise(n):
    return f"[ex{n:02d}](https://t-yokoga.github.io/softprac1/ex{n:02d}.html)"


def readme_table():
    rows = ["| 回 | テーマ | プロジェクト | 演習ページ |", "| --- | --- | --- | --- |"]
    for week, n, theme, projects in weeks():
        rows.append(f"| [第{n}回]({week.name}/README.md) | {theme} | {'，'.join(p.name for p in projects)} | {exercise(n)} |")
    return rows, f"{len(rows) - 2} 回"


def ta_table():
    rows = ["| 回 | テーマ | プロジェクト | テスト数 | 演習ページ |", "| --- | --- | --- | ---: | --- |"]
    total = 0
    for week, n, theme, projects in weeks():
        tests = sum(count_tests(p) for p in projects)
        total += tests
        rows.append(f"| [第{n}回]({week.name}/README.md) | {theme} | {'，'.join(p.name for p in projects)} | {tests} "
                    f"| {exercise(n)} |")
    debugging = ROOT / DEBUGGING
    if debugging.is_dir():
        topics = [p for p in project_dirs(debugging) if has_sources(p)]
        tests = sum(count_tests(p) for p in topics)
        total += tests
        rows.append(f"| [デバッグの題材]({DEBUGGING}/README.md) | バグ入りのプログラム（TA 用） "
                    f"| {len(topics)} 題 | {tests} | |")
    rows.append(f"| | | **合計** | **{total}** | |")
    return rows, f"テスト {total} 件"


def update(path: pathlib.Path, rows, summary, check):
    """path の表を置き換える。最新（または書き換えた）なら True。"""
    name = path.name
    text = path.read_bytes().decode("utf-8").replace("\r\n", "\n")
    if BEGIN not in text or END not in text:
        print(f"[NG] {name} に {BEGIN} と {END} がない")
        return False
    start, end = text.index(BEGIN) + len(BEGIN), text.index(END)
    new = text[:start] + "\n" + "\n".join(rows) + "\n" + text[end:]
    if write_text(path, new, check):
        print(f"{name} の各回の表: 最新（{summary}）")
        return True
    if check:
        print(f"[NG] {name} の各回の表が最新ではない（python3 tools/update_generated.py で作り直す）")
        return False
    print(f"{name} の各回の表: 作り直した（{summary}）")
    return True


def run(check=False):
    """生成する。check なら書き換えずに確かめる。すべて最新（または書き換えた）なら True。"""
    results = [update(ROOT / "README.md", *readme_table(), check), update(ROOT / "TA.md", *ta_table(), check)]
    return all(results)


def main():
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    if any(a in ("-h", "--help") for a in sys.argv[1:]):
        print(__doc__)
        return 0
    return 0 if run("--check" in sys.argv[1:]) else 1


if __name__ == "__main__":
    sys.exit(main())
