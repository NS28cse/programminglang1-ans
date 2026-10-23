# 第4回 演習（制御構造）練習用

- 演習ページ: [ex04](https://t-yokoga.github.io/softprac1/ex04.html)（原稿: [docs/ex04.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex04.md)）・講義: [lec04](https://t-yokoga.github.io/softprac1/lec04.html)（例題: [docs/sample/04/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/04/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week04/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1　`if`・`else if` による料金分類 | `Fee` | [fee.c](Fee/fee.c) | — | 1 |
| 課題2　`for` と `while` による偶数の合計 | `EvenSum` | [even_sum.c](EvenSum/even_sum.c) | — | 1 |
| 課題3　二重ループの掛け算表 | `Table` | [table.c](Table/table.c) | — | 1 |
| 課題4　2 の累乗と `do-while` | `Powers` | [powers.c](Powers/powers.c) | — | 1 |
| 発展　`switch` と `if` の比較 | `YearGroup` | [year_group.c](YearGroup/year_group.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
