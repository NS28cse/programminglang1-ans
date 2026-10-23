# 第10回 演習（ファイル）練習用

- 演習ページ: [ex10](https://t-yokoga.github.io/softprac1/ex10.html)（原稿: [docs/ex10.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex10.md)）・講義: [lec10](https://t-yokoga.github.io/softprac1/lec10.html)（例題: [docs/sample/10/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/10/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week10/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1　1 文字ずつ読んで表示 | `ReadText` | [read_text.c](ReadText/read_text.c) | 引数 `input.txt`，[input.txt](ReadText/input.txt) | 9 |
| 課題1　行の長さ | `LineLengths` | [line_lengths.c](LineLengths/line_lengths.c) | 引数 `input.txt`，[input.txt](LineLengths/input.txt) | 13 |
| 課題2　数値引数の検査（講義の `parse_number.c`） | `ParseNumber` | [parse_number.c](ParseNumber/parse_number.c) | 引数 `42` | 16 |
| 課題2　引数を表示して文字列を探す | `Arguments` | [arguments.c](Arguments/arguments.c) | 引数 `nagano` `ishikawa` | 12 |
| 課題3　バイト列を保存（講義の `binary.c`） | `Binary` | [binary.c](Binary/binary.c) | — | 2 |
| 課題3　バイト順を調べる（「別の `main`」） | `ByteOrder` | [byte_order.c](ByteOrder/byte_order.c) | — | 1 |
| 課題4　テキストを書く（モード `w`） | `WriteText` | [write_text.c](WriteText/write_text.c) | — | 3 |
| 発展1　数値をテキスト・バイナリで往復 | `NumberFormats` | [number_formats.c](NumberFormats/number_formats.c) | — | 2 |
| 発展2　二乗の一覧を書く | `WriteSquares` | [write_squares.c](WriteSquares/write_squares.c) | 引数 `4` `squares.txt` | 14 |
| 発展2　一覧を検査して値を探す | `CheckValue` | [check_value.c](CheckValue/check_value.c) | 引数 `squares.txt` `9`，[squares.txt](CheckValue/squares.txt) | 37 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
