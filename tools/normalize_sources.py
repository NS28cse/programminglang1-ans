#!/usr/bin/env python3
"""weekNN/ 以下の .c/.h を「BOM 付き UTF-8・LF・末尾改行あり」にそろえる。

BOM を付けると，/utf-8 を指定していない Visual Studio のプロジェクトへ
ファイルをコピーしても日本語コメントが正しく読まれる（C4819 や文字化けを防ぐ）。
    python tools/normalize_sources.py          # 修正する
    python tools/normalize_sources.py --check  # 確認だけ（CI 用）
"""
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
BOM = b"\xef\xbb\xbf"


def normalized(data: bytes) -> bytes:
    body = data[len(BOM):] if data.startswith(BOM) else data
    body.decode("utf-8")  # UTF-8 でなければ例外
    body = body.replace(b"\r\n", b"\n")
    if not body.endswith(b"\n"):
        body += b"\n"
    return BOM + body


def main():
    check = "--check" in sys.argv
    bad = []
    for path in sorted(ROOT.glob("week[0-9][0-9]/**/*")):
        if path.suffix not in (".c", ".h") or not path.is_file():
            continue
        data = path.read_bytes()
        fixed = normalized(data)
        if fixed != data:
            bad.append(path.relative_to(ROOT))
            if not check:
                path.write_bytes(fixed)
    for p in bad:
        print(("要修正: " if check else "修正: ") + str(p))
    if check and bad:
        sys.exit(1)


if __name__ == "__main__":
    main()
