#!/usr/bin/env python3
"""IDE の起動構成が実際に動くかを確かめる（CI 用）。

使い方: python3 tools/check_launch.py <ビルド先>   例: out/build/msvc-debug

  1. Visual Studio（フォルダーを開く）: .vs/launch.vs.json の各構成について，
     projectTarget の実行ファイルが <ビルド先>/bin/weekNN/ にあり，currentDir があり，
     その作業ディレクトリと args で起動すると（標準入力は空）正常に終わることを確かめる。
     終了コードは 0 か，同じ引数・空の入力のテストケース（tests/）が期待する値（失敗を示す課題の 1 など）。
  2. VS Code: .vscode/launch.json は「開いている .c のフォルダ名」= 実行ファイル名で起動するので，
     実行ファイルを作る全プロジェクトフォルダ（ライブラリだけのフォルダは除く）について <ビルド先>/bin/weekNN/<フォルダ名>(.exe) があることを確かめる。

実行時にプロジェクトフォルダへ書き出されるファイル（.gitignore 済み）は実行後に消す。
"""
import json
import os
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from gen_launch_vs import programs  # noqa: E402

EXE = ".exe" if os.name == "nt" else ""


def expected_codes(project: pathlib.Path, args):
    """0 と，同じ引数・空の標準入力のテストケースが期待する終了コード。"""
    codes = {0}
    for code in project.glob("tests/*.code"):
        case = code.with_suffix("")
        a = case.with_suffix(".args")
        case_args = []
        if a.exists():
            text = a.read_text(encoding="utf-8").replace("\r", "")
            if text:
                case_args = text[:-1].split("\n") if text.endswith("\n") else text.split("\n")
        i = case.with_suffix(".in")
        if case_args == args and (not i.exists() or i.stat().st_size == 0):
            codes.add(int(code.read_text().strip()))
    return codes


def main():
    if len(sys.argv) != 2 or sys.argv[1] in ("-h", "--help"):
        print(__doc__)
        return 0 if len(sys.argv) == 2 else 2
    build = pathlib.Path(sys.argv[1]).resolve()
    errors = []

    # 1. Visual Studio の起動構成
    configs = json.loads((ROOT / ".vs" / "launch.vs.json").read_text(encoding="utf-8"))["configurations"]
    for c in configs:
        m = re.fullmatch(r"(\w+)\.exe \(bin\\(week\d\d)\\(\w+)\.exe\)", c["projectTarget"])
        if not m or m.group(1) != m.group(3):
            errors.append(f"{c['name']}: projectTarget の形が不正: {c['projectTarget']}")
            continue
        exe = build / "bin" / m.group(2) / (m.group(1) + EXE)
        cwd = ROOT / c["currentDir"].replace("${workspaceRoot}\\", "").replace("\\", "/")
        if not exe.is_file():
            errors.append(f"{c['name']}: 実行ファイルがない: {exe}")
            continue
        if not cwd.is_dir():
            errors.append(f"{c['name']}: 作業ディレクトリがない: {cwd}")
            continue
        before = set(p.name for p in cwd.iterdir())
        try:
            r = subprocess.run([str(exe), *c["args"]], cwd=cwd, stdin=subprocess.DEVNULL,
                               capture_output=True, timeout=20)
            if r.returncode not in expected_codes(cwd, c["args"]):
                errors.append(f"{c['name']}: 終了コード {r.returncode}\n{r.stderr.decode(errors='replace')}")
        except subprocess.TimeoutExpired:
            errors.append(f"{c['name']}: 20 秒で終わらない")
        finally:
            for p in cwd.iterdir():
                if p.name not in before and p.is_file():
                    p.unlink()
    print(f"launch.vs.json: {len(configs)} 構成を起動")

    # 2. VS Code の起動構成（フォルダ名 = 実行ファイル名）
    folders = [p for p in sorted(ROOT.glob("week[0-9][0-9]/*"))
               if p.is_dir() and not p.name.startswith(("_", ".")) and p.name in programs(p)]
    for p in folders:
        exe = build / "bin" / p.parent.name / (p.name + EXE)
        if not exe.is_file():
            errors.append(f"VS Code: {p.relative_to(ROOT)} を開いて F5 を押すと起動する {exe} がない")
    print(f".vscode/launch.json: {len(folders)} フォルダの実行ファイルを確認")

    for e in errors:
        print("[NG]", e)
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
