# 第9回 演習（ポインタ2）練習用

- 演習ページ: [ex09](https://t-yokoga.github.io/softprac1/ex09.html)（原稿: [docs/ex09.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex09.md)）・講義: [lec09](https://t-yokoga.github.io/softprac1/lec09.html)（例題: [docs/sample/09/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/09/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week09/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1（見つからない場合・同点・失敗時・二重ポインタの代入） | `FindMax` | [double_pointer.c](FindMax/double_pointer.c) | — | 1 |
| 課題1（値を返す版と場所を返す版） | `ReturnMaximum` | [return_maximum.c](ReturnMaximum/return_maximum.c) | — | 1 |
| 課題2 表示順を変更する | `Names` | [names.c](Names/names.c) | — | 1 |
| 課題3 行ごとの平均 | `MatrixMean` | [matrix.c](MatrixMean/matrix.c) | — | 1 |
| 課題4 二次元配列の行を交換する | `SwapRows` | [swap_rows.c](SwapRows/swap_rows.c) | — | 1 |
| 発展1 長さが異なる行を扱う | `RaggedRows` | [ragged_rows.c](RaggedRows/ragged_rows.c) | — | 1 |
| 発展2　型の説明 | `ArrayTypes` | [array_types.c](ArrayTypes/array_types.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
