"""プロジェクトの見つけ方（ルートの CMakeLists.txt と同じ規則）を tools/ の各スクリプトで共有する。

  - 回のフォルダ: weekNN/（番号順）と，デバッグの題材の debugging/（最後）
  - プロジェクトフォルダ: 回のフォルダの直下のフォルダ。名前が _ または . で始まるものは除く
    （_ で始まるフォルダは意図的にエラーを含むコードの置き場所で，ビルドしない）
  - 実行ファイル: フォルダに CMakeLists.txt があればその softprac_add_program(<名前> ...)，
    なければフォルダに .c があるときフォルダ名の 1 つ

ほかのスクリプトからは次のように使う:
    sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
    from projects import ROOT, group_dirs, project_dirs, programs
"""
import pathlib
import re

ROOT = pathlib.Path(__file__).resolve().parent.parent
DEBUGGING = "debugging"


def week_dirs():
    """weekNN/ を番号順に返す。"""
    return sorted(p for p in ROOT.glob("week[0-9][0-9]") if p.is_dir())


def group_dirs():
    """プロジェクトを入れるフォルダ（weekNN/ と debugging/）を，CMake が登録する順に返す。"""
    dirs = week_dirs()
    if (ROOT / DEBUGGING).is_dir():
        dirs.append(ROOT / DEBUGGING)
    return dirs


def project_dirs(group: pathlib.Path):
    """回のフォルダ直下のプロジェクトフォルダ（_ や . で始まるものを除く）を名前順に返す。"""
    return sorted(p for p in group.iterdir() if p.is_dir() and not p.name.startswith(("_", ".")))


def all_projects():
    """すべての回のプロジェクトフォルダを，CMake が登録する順に返す。"""
    return [p for g in group_dirs() for p in project_dirs(g)]


def has_sources(project: pathlib.Path):
    """フォルダに .c があるか（ライブラリだけのプロジェクトも含む）。"""
    return any(project.glob("*.c"))


def strip_cmake_comments(text: str):
    """CMake のコメント（# から行末まで，#[[ ... ]] の括弧コメント）を除く。引用符・[[ ]] の中の # は残す。"""
    out, i, n = [], 0, len(text)
    while i < n:
        c = text[i]
        if text.startswith("#[[", i):
            end = text.find("]]", i + 3)
            i = n if end < 0 else end + 2
        elif c == "#":
            end = text.find("\n", i)
            i = n if end < 0 else end
        elif c == '"':
            j = i + 1
            while j < n and text[j] != '"':
                j += 2 if text[j] == "\\" else 1
            out.append(text[i:j + 1])
            i = j + 1
        elif text.startswith("[[", i):
            end = text.find("]]", i + 2)
            j = n if end < 0 else end + 2
            out.append(text[i:j])
            i = j
        else:
            out.append(c)
            i += 1
    return "".join(out)


def programs(project: pathlib.Path):
    """プロジェクトフォルダが作る実行ファイル名の一覧を返す（ライブラリだけなら空。コメントの中の呼び出しは数えない）。"""
    cmake = project / "CMakeLists.txt"
    if cmake.exists():
        text = strip_cmake_comments(cmake.read_text(encoding="utf-8"))
        return re.findall(r"softprac_add_program\(\s*([A-Za-z0-9_]+)", text)
    if has_sources(project):
        return [project.name]
    return []


def count_tests(project: pathlib.Path):
    """プロジェクトの CTest のテスト数（tests/*.out と，softprac_add_variant の variants/tests/*.out）。"""
    return len(list(project.glob("tests/*.out"))) + len(list(project.glob("variants/tests/*.out")))


def tree_kind(path: pathlib.Path):
    """作業ツリーがどのブランチの形かを返す: "ta"・"practice"・"main"，どれでもなければ None。
    ta は tools/ を持ち，practice は main にない cmake/RunTest.cmake と .vs/launch.vs.json を持つ。"""
    if (path / "tools" / "export_main.py").exists():
        return "ta"
    if (path / "cmake" / "RunTest.cmake").exists() or (path / ".vs" / "launch.vs.json").exists():
        return "practice"
    if (path / "week01").is_dir() and (path / "CMakeLists.txt").exists():
        return "main"
    return None


def read_lines(path: pathlib.Path):
    """1 行 1 要素のファイル（run.args・tests/*.args）を読む。空行は空文字列の要素，空のファイルは要素なし。"""
    text = path.read_text(encoding="utf-8").replace("\r", "")
    if not text:
        return []
    return text[:-1].split("\n") if text.endswith("\n") else text.split("\n")


def write_text(path: pathlib.Path, text: str, check: bool):
    """生成したテキストを書く（改行は OS によらず LF）。check なら書かず，内容が同じかだけを返す。"""
    old = path.read_bytes().decode("utf-8").replace("\r\n", "\n") if path.exists() else None
    if old == text:
        return True
    if not check:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    return False
