# 第1回 演習（プログラミングの基礎）練習用

- 演習ページ: [ex01](https://t-yokoga.github.io/softprac1/ex01.html)（原稿: [docs/ex01.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex01.md)）・講義: [lec01](https://t-yokoga.github.io/softprac1/lec01.html)（例題: [docs/sample/01/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/01/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week01/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1　最初のプログラム | `Welcome` | [welcome.c](Welcome/welcome.c) | — | 1 |
| 課題2　改行と特殊な文字 | `Message` | [message.c](Message/message.c) | — | 1 |
| 課題3　エラーの修正（修正後） | `Broken` | [broken.c](Broken/broken.c) | — | 1 |
| 課題4　ソースと実行ファイルの区別（本体は Version B） | `Version` | [version.c](Version/version.c) | — | 1 |
| 課題5　発展：文字で図を描く | `House` | [house.c](House/house.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
