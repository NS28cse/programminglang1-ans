# 第7回 演習（入出力）練習用

- 演習ページ: [ex07](https://t-yokoga.github.io/softprac1/ex07.html)（原稿: [docs/ex07.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex07.md)）・講義: [lec07](https://t-yokoga.github.io/softprac1/lec07.html)（例題: [docs/sample/07/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/07/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week07/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1 複写 | `Echo` | [echo.c](Echo/echo.c) | [input.txt](Echo/input.txt) | 5 |
| 課題1 小文字化フィルタ | `LowerInput` | [lower_input.c](LowerInput/lower_input.c) | [ab.txt](LowerInput/ab.txt)，[input.txt](LowerInput/input.txt) | 9 |
| 課題2 英字数 | `LetterCount` | [letter_count.c](LetterCount/letter_count.c) | [input.txt](LetterCount/input.txt) | 11 |
| 課題2 バイト数 | `ByteCount` | [byte_count.c](ByteCount/byte_count.c) | [input.txt](ByteCount/input.txt) | 8 |
| 課題3 行の容量 | `LineInput` | [line.c](LineInput/line.c) | [input.txt](LineInput/input.txt) | 11 |
| 課題4 書式 | `Formats` | [formats.c](Formats/formats.c) | — | 1 |
| 発展 タイピング | `Typing` | [typing.c](Typing/typing.c) | [input.txt](Typing/input.txt) | 15 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
