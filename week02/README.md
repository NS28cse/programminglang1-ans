# 第2回 演習（変数）練習用

- 演習ページ: [ex02](https://t-yokoga.github.io/softprac1/ex02.html)（原稿: [docs/ex02.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex02.md)）・講義: [lec02](https://t-yokoga.github.io/softprac1/lec02.html)（例題: [docs/sample/02/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/02/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week02/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1　長方形の面積と再計算 | `Rectangle` | [rectangle.c](Rectangle/rectangle.c) | — | 1 |
| 課題2　型と表示の対応 | `Profile` | [profile.c](Profile/profile.c) | — | 1 |
| 課題3　値のコピーと交換 | `Exchange` | [exchange.c](Exchange/exchange.c) | — | 1 |
| 課題4　値・サイズ・場所の観察 | `Observe` | [observe.c](Observe/observe.c) | — | 0 |
| 課題5　発展：小数を使った計算 | `Temperature` | [temperature.c](Temperature/temperature.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
