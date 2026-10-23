# 第5回 演習（配列と関数）練習用

- 演習ページ: [ex05](https://t-yokoga.github.io/softprac1/ex05.html)（原稿: [docs/ex05.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex05.md)）・講義: [lec05](https://t-yokoga.github.io/softprac1/lec05.html)（例題: [docs/sample/05/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/05/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week05/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| ウォームアップ　初期化を読む | `Warmup05` | [warmup.c](Warmup05/warmup.c) | — | 1 |
| 課題1　最大の点数 | `Maximum` | [maximum.c](Maximum/maximum.c) | — | 1 |
| 課題2　列ごとの合計 | `ColumnSum` | [arrays.c](ColumnSum/arrays.c) | — | 1 |
| 課題2 補足　三次元配列の添字 | `Array3D` | [array3d.c](Array3D/array3d.c) | — | 1 |
| 課題3　値渡し（本体 = 演習ページのプログラム） | `ValueCopy` | [valuecopy.c](ValueCopy/valuecopy.c) | — | 1 |
| 課題4　平均と累乗の関数 | `Functions` | [functions.c](Functions/functions.c) | — | 1 |
| 発展　合計と平均の役割分担 | `SumMean` | [summean.c](SumMean/summean.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
