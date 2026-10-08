#!/usr/bin/env python3
"""Visual Studio（フォルダーを開く）用の .vs/launch.vs.json を生成する。

各プロジェクト（weekNN/<名前>/）について，
  - 作業ディレクトリ = プロジェクトフォルダ（授業の $(ProjectDir) と同じ）
  - コマンドライン引数 = プロジェクトフォルダの run.args（1 行 1 引数，任意）
を設定した起動構成を作る。プロジェクトを追加・変更したら再実行する:
    python tools/gen_launch_vs.py
"""
import json
import pathlib
import sys
import re

ROOT = pathlib.Path(__file__).resolve().parent.parent


def programs(project: pathlib.Path):
    """プロジェクトフォルダが作る実行ファイル名の一覧を返す。"""
    cmake = project / "CMakeLists.txt"
    if cmake.exists():
        return re.findall(r"softprac_add_program\(\s*([A-Za-z0-9_]+)", cmake.read_text(encoding="utf-8"))
    if any(project.glob("*.c")):
        return [project.name]
    return []


def main():
    if any(a in ("-h", "--help") for a in sys.argv[1:]):
        print(__doc__)
        return
    configs = []
    for week in sorted(ROOT.glob("week[0-9][0-9]")):
        for project in sorted(p for p in week.iterdir() if p.is_dir() and not p.name.startswith(("_", "."))):
            args = []
            run_args = project / "run.args"
            if run_args.exists():
                text = run_args.read_text(encoding="utf-8").replace("\r", "")
                if text:
                    args = text[:-1].split("\n") if text.endswith("\n") else text.split("\n")
            for name in programs(project):
                target = f"{name}.exe (bin\\{week.name}\\{name}.exe)"
                label = f"{week.name} {name}" + (f"  [{' '.join(args)}]" if args else "")
                configs.append({
                    "type": "default",
                    "project": "CMakeLists.txt",
                    "projectTarget": target,
                    "name": label,
                    "currentDir": "${workspaceRoot}\\" + week.name + "\\" + project.name,
                    "args": args,
                })
    out = ROOT / ".vs" / "launch.vs.json"
    out.parent.mkdir(exist_ok=True)
    out.write_text(json.dumps({"version": "0.2.1", "defaults": {}, "configurations": configs},
                              ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"{out.relative_to(ROOT)}: {len(configs)} 件")


if __name__ == "__main__":
    main()
