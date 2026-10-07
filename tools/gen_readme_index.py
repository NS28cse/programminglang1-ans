#!/usr/bin/env python3
"""ルートの README.md の目次（各回の表）を weekNN/ の内容から作り直す。

    python tools/gen_readme_index.py
"""
import pathlib
import re

ROOT = pathlib.Path(__file__).resolve().parent.parent
BEGIN, END = "<!-- WEEK-TABLE:BEGIN -->", "<!-- WEEK-TABLE:END -->"


def main():
    rows = ["| 回 | テーマ | プロジェクト | テスト数 | 演習ページ |", "| --- | --- | --- | ---: | --- |"]
    total = 0
    for week in sorted(ROOT.glob("week[0-9][0-9]")):
        n = int(week.name[4:])
        title = (week / "README.md").read_text(encoding="utf-8").splitlines()[0]
        m = re.search(r"（(.*)）", title)
        theme = m.group(1) if m else ""
        projects = sorted(p.name for p in week.iterdir()
                          if p.is_dir() and not p.name.startswith(("_", ".")) and any(p.glob("*.c")))
        tests = len(list(week.glob("*/tests/*.out"))) + len(list(week.glob("*/variants/tests/*.out")))
        total += tests
        rows.append(f"| [第{n}回]({week.name}/README.md) | {theme} | {'，'.join(projects)} | {tests} "
                    f"| [ex{n:02d}](https://t-yokoga.github.io/softprac1/ex{n:02d}.html) |")
    rows.append(f"| | | **合計** | **{total}** | |")
    readme = ROOT / "README.md"
    text = readme.read_text(encoding="utf-8")
    start, end = text.index(BEGIN) + len(BEGIN), text.index(END)
    readme.write_text(text[:start] + "\n" + "\n".join(rows) + "\n" + text[end:], encoding="utf-8")
    print(f"README.md: {len(rows) - 3} 回，テスト {total} 件")


if __name__ == "__main__":
    main()
