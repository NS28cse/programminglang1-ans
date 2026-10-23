# 第3回 演習（演算子）練習用

- 演習ページ: [ex03](https://t-yokoga.github.io/softprac1/ex03.html)（原稿: [docs/ex03.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex03.md)）・講義: [lec03](https://t-yokoga.github.io/softprac1/lec03.html)（例題: [docs/sample/03/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/03/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week03/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1　秒を分と秒へ分解する | `TimeParts` | [time_parts.c](TimeParts/time_parts.c) | — | 1 |
| 課題2　前置・後置と複合代入 | `Update` | [update.c](Update/update.c) | — | 1 |
| 課題3　範囲の判定と短絡評価 | `Conditions` | [conditions.c](Conditions/conditions.c) | — | 1 |
| 課題4　うるう年の条件式 | `Leap` | [leap.c](Leap/leap.c) | — | 1 |
| 課題5　発展：権限フラグ | `Flags` | [flags.c](Flags/flags.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
