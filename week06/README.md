# 第6回 演習（文字列）練習用

- 演習ページ: [ex06](https://t-yokoga.github.io/softprac1/ex06.html)（原稿: [docs/ex06.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex06.md)）・講義: [lec06](https://t-yokoga.github.io/softprac1/lec06.html)（例題: [docs/sample/06/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/06/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week06/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| ウォームアップ：文字と数値 | `CharCode` | [char_code.c](CharCode/char_code.c) | — | 1 |
| 課題1 長さを数える | `Length` | [length.c](Length/length.c) | — | 1 |
| 課題2 ASCIIの小文字へ変換 | `Lower` | [lower.c](Lower/lower.c) | — | 1 |
| 課題2 補足：ASCIIの印字可能な範囲 | `AsciiTable` | [ascii_table.c](AsciiTable/ascii_table.c) | — | 1 |
| 課題3 変換する順序 | `Average` | [average.c](Average/average.c) | — | 1 |
| 課題4 比較してから連結する | `CompareJoin` | [compare_join.c](CompareJoin/compare_join.c) | — | 1 |
| 発展 容量の境界 | `CopyCapacity` | [strings.c](CopyCapacity/strings.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
