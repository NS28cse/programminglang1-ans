#!/usr/bin/env python3
"""Visual Studio（File > Open > Folder）用の .vs/launch.vs.json を生成する。

各プロジェクト（weekNN/<名前>/ と，デバッグの題材 debugging/<名前>/）について，
  - 作業ディレクトリ = プロジェクトフォルダ（授業の $(ProjectDir) と同じ）
  - コマンドライン引数 = プロジェクトフォルダの run.args（1 行 1 引数，任意）
を設定した起動構成を作る。ふだんは tools/update_generated.py から実行する。
    python3 tools/gen_launch_vs.py          # 作り直す
    python3 tools/gen_launch_vs.py --check  # 書き換えずに，最新でなければ失敗する
"""
import json
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from projects import ROOT, group_dirs, programs, project_dirs, read_lines, write_text  # noqa: E402

OUT = ROOT / ".vs" / "launch.vs.json"


def generate():
    configs = []
    for week in group_dirs():
        for project in project_dirs(week):
            run_args = project / "run.args"
            args = read_lines(run_args) if run_args.exists() else []
            for name in programs(project):
                target = f"{name}.exe (bin\\{week.name}\\{name}\\{name}.exe)"
                label = f"{week.name} {name}" + (f"  [{' '.join(args)}]" if args else "")
                configs.append({
                    "type": "default",
                    "project": "CMakeLists.txt",
                    "projectTarget": target,
                    "name": label,
                    "currentDir": "${workspaceRoot}\\" + week.name + "\\" + project.name,
                    "args": args,
                })
    text = json.dumps({"version": "0.2.1", "defaults": {}, "configurations": configs},
                      ensure_ascii=False, indent=2) + "\n"
    return text, len(configs)


def run(check=False):
    """生成する。check なら書き換えずに確かめる。最新（または書き換えた）なら True。"""
    text, n = generate()
    rel = OUT.relative_to(ROOT).as_posix()
    if write_text(OUT, text, check):
        print(f"{rel}: 最新（{n} 件）")
        return True
    if check:
        print(f"[NG] {rel} が最新ではない（python3 tools/update_generated.py で作り直す）")
        return False
    print(f"{rel}: 作り直した（{n} 件）")
    return True


def main():
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    if any(a in ("-h", "--help") for a in sys.argv[1:]):
        print(__doc__)
        return 0
    return 0 if run("--check" in sys.argv[1:]) else 1


if __name__ == "__main__":
    sys.exit(main())
