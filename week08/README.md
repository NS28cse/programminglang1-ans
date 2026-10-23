# 第8回 演習（ポインタ1）練習用

- 演習ページ: [ex08](https://t-yokoga.github.io/softprac1/ex08.html)（原稿: [docs/ex08.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex08.md)）・講義: [lec08](https://t-yokoga.github.io/softprac1/lec08.html)（例題: [docs/sample/08/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/08/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week08/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1　ポインタと`swap` | `Swap` | [pointers.c](Swap/pointers.c) | — | 1 |
| 課題2　最小値・最大値の出力 | `MinMax` | [min_max.c](MinMax/min_max.c) | — | 1 |
| 課題3　文字列のコピー | `CopyText` | [copy_text.c](CopyText/copy_text.c) | — | 1 |
| 課題4　配列・文字列の走査 | `PointerWalk` | [pointer_walk.c](PointerWalk/pointer_walk.c) | — | 1 |
| 発展　数の分解とポインタの戻り値 | `Decompose` | [decompose.c](Decompose/decompose.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
