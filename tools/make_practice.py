#!/usr/bin/env python3
"""practice ブランチ（解答を雛形に置き換え，テストで自己採点しながら課題を解く練習用）の中身を作る。

    git worktree add ../practice-work main             # main の作業ツリーを用意する（practice は main から作る）
    python3 tools/make_practice.py ../practice-work    # 作業ツリーを practice の中身に書き換える

作業ツリー（main の内容）を次のように書き換える:
  - weekNN/<プロジェクト>/ の .c・.h を雛形にする（main を持つ .c は空の main だけ，ほかは課題名のコメントだけ）。
    ファイル名・データファイル（input.txt など）・フォルダの構成はそのまま残す
  - versions/（比較用の解答）と，名前が _ で始まるフォルダ（エラーを含む版。演習ページにある）を除く
  - ta の tests/（入力と期待する出力）を写す。書き換えた版（variants/）は，雛形では置換の対象がないので写さない
  - 各回の README.md を，課題とプロジェクト・作るファイル・引数・テスト数の表だけにする（解答と解説は除く）
  - ルートの README.md を練習の手順にし（main の README の「使い方」「よくあるトラブル」を含める），
    CMakeLists.txt に tests/ のテストの登録を加え，cmake/RunTest.cmake と .gitattributes を写す
"""
import pathlib
import re
import shutil
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from projects import ROOT, count_tests, project_dirs, read_lines, week_dirs  # noqa: E402

BOM = "﻿"
EXCLUDE_TOP = {".git"}


def title_of(src: pathlib.Path):
    """ソースの 1 行目のコメントから「第N回 課題X　題名（Project / file.c）」を取り出す。"""
    first = src.read_text(encoding="utf-8-sig").splitlines()[0] if src.stat().st_size else ""
    m = re.search(r"第\d+回.*?（[^）]*）", first)
    return m.group(0) if m else f"{src.parent.name} / {src.name}"


def has_main(src: pathlib.Path):
    return re.search(r"^\s*int\s+main\s*\(", src.read_text(encoding="utf-8-sig"), re.M) is not None


def stub(src: pathlib.Path, week_no: int):
    lines = [f"// {title_of(src)}",
             f"// 演習ページ: https://t-yokoga.github.io/softprac1/ex{week_no:02d}.html"]
    if src.suffix == ".c" and has_main(src):
        lines += ["", "int main(void)", "{", "    return 0;", "}"]
    elif src.suffix == ".c":
        lines += ["// 関数の定義をここに書く（空のままだと -Wpedantic で空の翻訳単位の警告が出る）"]
    else:
        lines += ["// 宣言をここに書く"]
    return BOM + "\n".join(lines) + "\n"


def tasks(week: pathlib.Path):
    """プロジェクト名 → [課題の名前]。README の「プロジェクト一覧」の表（課題・内容・プロジェクトの列）から作り，
    表にないものは見出し「## 課題N　題名（`Project` / …）」から補う。"""
    names = {p.name for p in project_dirs(week)}
    result = {}
    lines = (week / "README.md").read_text(encoding="utf-8").splitlines()
    start = next((i for i, l in enumerate(lines) if l.startswith("## プロジェクト一覧")), None)
    header = None
    for line in lines[start + 1:] if start is not None else []:
        if line.startswith("## "):
            break
        if not line.startswith("|"):
            continue
        cells = [c.strip() for c in line.strip().strip("|").split("|")]
        if header is None:
            header = cells
            continue
        if set(cells[0]) <= set("-: "):
            continue
        row = dict(zip(header, cells))
        m = re.fullmatch(r"`([A-Za-z0-9_]+)`", row.get("プロジェクト", ""))
        if m and m.group(1) in names:
            task = row.get("課題", "")
            task = f"課題{task}" if re.fullmatch(r"[0-9]+", task) else task
            result.setdefault(m.group(1), []).append(f"{task}　{row['内容']}" if row.get("内容") else task)
    from_table = set(result)
    for line in lines:
        m = re.match(r"^## ((?:課題|発展)\S*)　(.+?)（(.*)）\s*$", line)
        if not m:
            continue
        for p in re.findall(r"`([A-Za-z0-9_]+)`", m.group(3)):
            if p in names and p not in from_table:
                result.setdefault(p, []).append(f"{m.group(1)}　{m.group(2)}")
    return result


def week_readme(week: pathlib.Path):
    n = int(week.name[4:])
    head = (week / "README.md").read_text(encoding="utf-8").splitlines()
    theme = re.search(r"（(.*)）", head[0]).group(1)
    links = next((l for l in head[1:6] if l.startswith("- 演習ページ")), "")
    by_project = tasks(week)
    rows = ["| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |", "| --- | --- | --- | --- | ---: |"]
    # 演習ページの課題の順（README の見出しに最初に出る順）に並べる。見出しにないものは最後
    order = list(dict.fromkeys(by_project))
    for p in sorted(project_dirs(week), key=lambda p: (order.index(p.name) if p.name in order else len(order), p.name)):
        sources = sorted(f.name for f in p.iterdir() if f.suffix in (".c", ".h"))
        if not sources:
            continue
        data = sorted(f.name for f in p.iterdir() if f.is_file() and f.suffix not in (".c", ".h")
                      and f.name not in ("CMakeLists.txt", "run.args"))
        uses = []
        if (p / "run.args").exists():
            uses.append("引数 " + " ".join(f"`{a}`" for a in read_lines(p / "run.args")))
        uses += [f"[{d}]({p.name}/{d})" for d in data]
        label = "<br>".join(by_project.get(p.name, ["（README の見出しにない）"]))
        rows.append(f"| {label} | `{p.name}` | {'，'.join(f'[{s}]({p.name}/{s})' for s in sources)} "
                    f"| {'，'.join(uses) or '—'} | {count_tests(p)} |")
    return "\n".join([
        f"# 第{n}回 演習（{theme}）練習用",
        "",
        links,
        "",
        "演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。"
        "書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。",
        "説明・表の記入・確認問題は演習ページを見て自分で答え，`main` ブランチのこの回の README で答え合わせをします。",
        "",
        *rows,
        "",
        "- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。",
        "- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。",
        "",
    ])


ROOT_README = """# programminglang1-ans（practice ブランチ）

「プログラミング言語I・ソフトウェア演習I」（C 言語）の課題を，**解答を見ずに自分で書いて**，学生と同じ手順と難しさを体験するためのブランチです。
各プロジェクトのソースは雛形（空の `main`）になっていて，入力ファイルと自動テスト（期待する出力）だけが入っています。

- 授業サイト: <https://t-yokoga.github.io/softprac1/>
- 解答と解説は `main` ブランチ，テストの実際の出力は `ta-results` ブランチにあります（このブランチは `ta` の `tools/make_practice.py` で作っています）。

## 進め方

1. 自分用のブランチを作ります（`practice` は雛形のまま残しておくと，やり直しや他の人の練習に使えます）。

   ```sh
   git switch -c practice-<名前> origin/practice
   ```

2. その回の README（[各回の課題](#各回の課題)）で，課題とプロジェクト・作るファイルを確かめます。
3. 演習ページを読み，プロジェクトフォルダの雛形に解答を書きます。ファイルの名前と分け方は演習ページの指定どおりにしてあります。
4. ビルドして実行し，[テストで確かめます](#テストで確かめる)。
5. 終わったら commit し，`main` の解答と比べます。

   ```sh
   git diff origin/main -- week05/Functions/   # 自分の解答と main の解答の違い
   ```

## 各回の課題

<!-- WEEK-TABLE:BEGIN -->
{week_table}
<!-- WEEK-TABLE:END -->

## テストで確かめる

テストは各プロジェクトの `tests/` にあり，`<ケース>.in`（標準入力）・`<ケース>.args`（引数）でプログラムを実行して，標準出力が `<ケース>.out` と一致するかを確かめます（終了コードは `.code`，作られるファイルは `.files/`）。
テストを動かすには CMake を使います（[使い方](#使い方)の 3・4）。

| 方法 | テストの実行 |
| --- | --- |
| コマンド | `cmake -S . -B build && cmake --build build` の後，`ctest --test-dir build -R week05/Functions --output-on-failure`（`-R` で回やプロジェクトを絞る。`-R week05` なら第5回すべて） |
| Visual Studio でフォルダーを開く | **Test > Run CTests for softprac1_answers**，または **Test Explorer** |
| VS Code | **Testing** ビュー，または **Command Palette** の **CMake: Run Tests** |

- 失敗したテストは，期待する出力と実際の出力を並べて表示します（`--output-on-failure`）。
- 雛形のままでは，そのプロジェクトのテストはすべて失敗します。全部が通れば，演習ページの表示例どおりに書けています。
- 空のプロジェクトやコマンドで作った実行ファイルは，入力を与えて出力をファイルに保存し，`diff`（Windows は `fc`）で `tests/<ケース>.out` と比べます。

  ```sh
  cd week07/Echo
  gcc -std=c17 -Wall -Wextra -Wpedantic *.c -o a.out -lm
  ./a.out < tests/basic.in | diff - tests/basic.out   # 何も表示されなければ一致
  ```

"""


def run_git(*args, cwd):
    return subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True, check=True).stdout


def main():
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    if len(sys.argv) != 2 or sys.argv[1] in ("-h", "--help"):
        print(__doc__)
        return 0 if len(sys.argv) == 2 else 2
    dest = pathlib.Path(sys.argv[1]).resolve()
    if dest == ROOT or not (dest / ".git").exists() or not (dest / "week01").is_dir():
        print(f"[NG] {dest} は main の作業ツリーではない")
        return 2

    readmes, week_rows = {}, ["| 回 | テーマ | プロジェクト | テスト数 |", "| --- | --- | --- | ---: |"]
    for week in week_dirs():
        n = int(week.name[4:])
        readmes[week.name] = week_readme(week)
        projects = [p for p in project_dirs(week) if any(p.glob("*.c"))]
        theme = re.search(r"（(.*)）", (week / "README.md").read_text(encoding="utf-8").splitlines()[0]).group(1)
        week_rows.append(f"| [第{n}回]({week.name}/README.md) | {theme} | {'，'.join(p.name for p in projects)} "
                         f"| {sum(count_tests(p) for p in projects)} |")

        dweek = dest / week.name
        for d in list(dweek.iterdir()):
            if d.is_dir() and d.name.startswith("_"):
                shutil.rmtree(d)
        for p in project_dirs(week):
            dp = dweek / p.name
            shutil.rmtree(dp / "versions", ignore_errors=True)
            for src in p.iterdir():
                if src.suffix in (".c", ".h"):
                    (dp / src.name).write_bytes(stub(src, n).encode("utf-8"))
            shutil.rmtree(dp / "tests", ignore_errors=True)
            if (p / "tests").is_dir():
                shutil.copytree(p / "tests", dp / "tests")
        (dweek / "README.md").write_bytes(readmes[week.name].encode("utf-8"))

    # ルートの README: 練習の手順 + main の README の「使い方」「よくあるトラブル」
    main_readme = (dest / "README.md").read_text(encoding="utf-8")
    usage = main_readme[main_readme.index("## 使い方"):]
    usage = usage.replace("それぞれの回の README のコマンドでビルドします。",
                          "`main` ブランチのそれぞれの回の README のコマンドでビルドします（CMake を使う方法 3・4 ならそのままビルドできます）。")
    text = ROOT_README.replace("{week_table}", "\n".join(week_rows)) + usage
    (dest / "README.md").write_bytes(text.encode("utf-8"))

    # CMakeLists.txt: tests/ を CTest に登録する（ta の RunTest.cmake を使う）
    cmake = (dest / "CMakeLists.txt").read_text(encoding="utf-8")
    if "softprac_add_tests" not in cmake:
        cmake = cmake.replace("project(softprac1_answers LANGUAGES C)\n", """project(softprac1_answers LANGUAGES C)
enable_testing()
set(SOFTPRAC_RUN_TEST "${CMAKE_SOURCE_DIR}/cmake/RunTest.cmake")

# <プロジェクト>/tests/<ケース>.out があれば CTest に登録する（practice ブランチ。テスト名は weekNN/<名前>/<ケース>）
function(softprac_add_tests name project_dir)
  file(GLOB outs CONFIGURE_DEPENDS "${project_dir}/tests/*.out")
  foreach(out IN LISTS outs)
    get_filename_component(case "${out}" NAME_WE)
    add_test(NAME "${SOFTPRAC_WEEK}/${name}/${case}"
      COMMAND "${CMAKE_COMMAND}" "-DPROGRAM=$<TARGET_FILE:${name}>" "-DPROJECT_DIR=${project_dir}" "-DCASE=${case}"
        "-DWORK_DIR=${CMAKE_BINARY_DIR}/testwork/${SOFTPRAC_WEEK}/${name}/${case}" -P "${SOFTPRAC_RUN_TEST}")
  endforeach()
endfunction()
""", 1)
        cmake = cmake.replace("""      configure_file("${f}" "${out_dir}/${fname}" COPYONLY)
    endif()
  endforeach()
endfunction()""", """      configure_file("${f}" "${out_dir}/${fname}" COPYONLY)
    endif()
  endforeach()
  softprac_add_tests(${name} "${SOFTPRAC_PROJECT_DIR}")
endfunction()""", 1)
        assert "softprac_add_tests(${name}" in cmake, "CMakeLists.txt の形が想定と違う"
        (dest / "CMakeLists.txt").write_bytes(cmake.encode("utf-8"))
    (dest / "cmake").mkdir(exist_ok=True)
    shutil.copyfile(ROOT / "cmake" / "RunTest.cmake", dest / "cmake" / "RunTest.cmake")
    shutil.copyfile(ROOT / ".gitattributes", dest / ".gitattributes")

    print(run_git("status", "--short", cwd=dest).count("\n"), "件のファイルが変わった。git add -A して commit する")
    return 0


if __name__ == "__main__":
    sys.exit(main())
