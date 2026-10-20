#!/usr/bin/env python3
"""すべてのテストを実行し，実際の出力を results/ に保存する（ta-results ブランチの中身を作る）。

    python3 tools/collect_results.py                    # ビルド先は out/build/results
    python3 tools/collect_results.py --build-dir <フォルダ> [-j <並列数>]

  1. -DSOFTPRAC_RESULTS_DIR=results/ を付けて構成・ビルドし，ctest ですべてのテストを実行する
     （警告をエラーにせず，sanitizer も付けない。授業と同じ Debug 構成）
  2. 各テストケースの実際の出力が，期待値（tests/・variants/tests/）と同じ形式で results/ に保存される
     （cmake/RunTest.cmake。<ケース>.out は必ず，.err は標準エラー出力があるとき，.code は 0 以外のとき，
      .files/ は実行で作られた・変わったファイルと，期待値の .files/ にあるファイル）
       weekNN/<プロジェクト>/tests/<ケース>.out           → results/weekNN/<プロジェクト>/tests/<ケース>.out
       weekNN/<プロジェクト>/variants/tests/<ケース>.out  → results/weekNN/<プロジェクト>/variants/tests/<ケース>.out
  3. results/README.md に，実行した環境と，テストごとの結果（一致・不一致）と実際の出力・期待値へのリンクを書く

テストが失敗しても results/ は作る（終了コードは失敗したテストがあれば 1）。
CI（.github/workflows/results.yml）が ta ブランチへの push ごとに実行し，ta-results ブランチを作り直す。
"""
import argparse
import datetime
import os
import pathlib
import platform
import re
import shutil
import subprocess
import sys
import xml.etree.ElementTree as ET

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from projects import ROOT, all_projects, programs  # noqa: E402

RESULTS = ROOT / "results"


def run(cmd, **kw):
    print("$", " ".join(str(c) for c in cmd), flush=True)
    return subprocess.run([str(c) for c in cmd], **kw)


def first_line(cmd):
    try:
        r = subprocess.run(cmd, capture_output=True, text=True)
        return (r.stdout or r.stderr).splitlines()[0].strip()
    except (OSError, IndexError):
        return "不明"


def cache_value(build: pathlib.Path, key):
    for line in (build / "CMakeCache.txt").read_text(encoding="utf-8", errors="replace").splitlines():
        if line.startswith(key + ":"):
            return line.split("=", 1)[1]
    return ""


def program_folders():
    """実行ファイル名 → プロジェクトフォルダ（リポジトリからの相対パス）。"""
    return {name: p.relative_to(ROOT).as_posix() for p in all_projects() for name in programs(p)}


def read_junit(path: pathlib.Path):
    """[(テスト名, 成功か)] を ctest の順に返す。"""
    cases = []
    for tc in ET.parse(path).getroot().iter("testcase"):
        ok = tc.get("status", "run") == "run" and tc.find("failure") is None and tc.find("error") is None
        cases.append((tc.get("name"), ok))
    return cases


def link(text, target: pathlib.Path):
    """results/README.md からの相対リンク（ファイルがなければ文字だけ）。"""
    if not target.exists():
        return text
    return f"[{text}]({os.path.relpath(target, RESULTS).replace(os.sep, '/')})"


def report(build: pathlib.Path, cases):
    folders = program_folders()
    groups = {}
    for name, ok in cases:
        group, program, case = name.split("/", 2)
        groups.setdefault(group, []).append((program, case, ok))
    # ctest は終わった順に書くので，回（debugging は最後）とテスト名の順に並べ直す
    groups = {g: sorted(groups[g]) for g in sorted(groups, key=lambda g: (g == "debugging", g))}

    commit = first_line(["git", "-C", str(ROOT), "rev-parse", "HEAD"])
    compiler = f"{cache_value(build, 'CMAKE_C_COMPILER')}"
    lines = [
        "# テストの実行結果",
        "",
        "`ta` ブランチのすべてのテストケースを実行した，実際の出力です（`python3 tools/collect_results.py` が作る。手で直さない）。",
        "",
        "| 項目 | 値 |",
        "| --- | --- |",
        f"| 実行した日時（UTC） | {datetime.datetime.now(datetime.timezone.utc):%Y-%m-%d %H:%M} |",
        f"| `ta` のコミット | `{commit}` |",
        f"| OS | {platform.system()} {platform.machine()}（{platform.platform()}） |",
        f"| コンパイラ | {first_line([compiler, '--version'])}（`-std=c17 -Wall -Wextra -Wpedantic`，Debug） |",
        f"| CMake | {first_line(['cmake', '--version'])} |",
        "",
        "## 見方",
        "",
        "- `results/` は，期待値（各プロジェクトの `tests/`・`variants/tests/`）と同じ形のフォルダです。"
        "`<ケース>.out` が標準出力，`.err` が標準エラー出力（出たときだけ），`.code` が終了コード（0 以外のときだけ），"
        "`<ケース>.files/` が実行で作られた・書き換えられたファイルです。",
        "- 入力（`<ケース>.in`）と引数（`<ケース>.args`）は，期待値と同じフォルダ（`ta` の `weekNN/<プロジェクト>/tests/`）にあります。",
        "- テストは環境で変わる出力（アドレスなど）を含まないので，Windows（MSVC）でも同じ出力になります（`ta` の CI で確かめています）。",
        "- 学生の出力と比べるときは，学生のプログラムに同じ入力・引数を与えて出力をファイルに保存し，`diff`（Windows は `fc`）で比べます。",
        "",
        "```sh",
        "# 例: 第7回 Echo の basic を学生のプログラムで試して比べる",
        "./student < week07/Echo/tests/basic.in > student.out",
        "diff student.out results/week07/Echo/tests/basic.out",
        "# 期待値と実際の出力をまとめて比べる（入力・引数のファイルは除く。Only in は片方にだけあるファイル",
        "# ＝期待値で固定していない標準エラー出力など）",
        "diff -r -x '*.in' -x '*.args' -x '*.setup' week07/Echo/tests results/week07/Echo/tests",
        "```",
        "",
        "## まとめ",
        "",
        "| 回 | テスト数 | 一致 | 不一致 |",
        "| --- | ---: | ---: | ---: |",
    ]
    total = failed = 0
    for group, items in groups.items():
        ng = sum(1 for *_, ok in items if not ok)
        total += len(items)
        failed += ng
        anchor = group
        lines.append(f"| [{group}](#{anchor}) | {len(items)} | {len(items) - ng} | {ng} |")
    lines.append(f"| **合計** | **{total}** | **{total - failed}** | **{failed}** |")

    for group, items in groups.items():
        lines += ["", f"## {group}", "", "| テスト | 結果 | 実際の出力 | 期待値 |", "| --- | --- | --- | --- |"]
        for program, case, ok in items:
            folder = folders.get(program, f"{group}/{program}")
            if case.startswith("variant_"):
                sub, file = "variants/tests", case[len("variant_"):]
            else:
                sub, file = "tests", case
            actual = RESULTS / group / program / sub
            expected = ROOT / folder / sub
            extras = [link(ext, actual / f"{file}{ext}") for ext in (".err", ".code", ".files")
                      if (actual / f"{file}{ext}").exists()]
            lines.append(f"| `{program}/{case}` | {'一致' if ok else '**不一致**'} "
                         f"| {link('.out', actual / f'{file}.out')}{' ' + ' '.join(extras) if extras else ''} "
                         f"| {link('.out', expected / f'{file}.out')} |")
    (RESULTS / "README.md").write_bytes(("\n".join(lines) + "\n").encode("utf-8"))
    return total, failed


def main():
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--build-dir", default=str(ROOT / "out" / "build" / "results"))
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 2)
    args = ap.parse_args()
    build = pathlib.Path(args.build_dir).resolve()

    shutil.rmtree(RESULTS, ignore_errors=True)
    RESULTS.mkdir()
    configure = ["cmake", "-S", ROOT, "-B", build, "-DCMAKE_BUILD_TYPE=Debug", f"-DSOFTPRAC_RESULTS_DIR={RESULTS}",
                 "-DSOFTPRAC_WERROR=OFF", "-DSOFTPRAC_SANITIZE=OFF", "-DSOFTPRAC_WEEKS="]
    if run(configure).returncode != 0 or run(["cmake", "--build", build, "-j", args.jobs]).returncode != 0:
        return 2
    junit = build / "results-junit.xml"
    run(["ctest", "--test-dir", build, "-j", args.jobs, "--timeout", "60", "--output-junit", junit])
    total, failed = report(build, read_junit(junit))
    print(f"results/: テスト {total} 件，一致 {total - failed} 件，不一致 {failed} 件")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
