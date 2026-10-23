# 第12回 演習（コンパイル：分割コンパイルとライブラリ）練習用

- 演習ページ: [ex12](https://t-yokoga.github.io/softprac1/ex12.html)（原稿: [docs/ex12.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex12.md)）・講義: [lec12](https://t-yokoga.github.io/softprac1/lec12.html)（例題: [docs/sample/12/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/12/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week12/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1　分割ビルド<br>課題2　関数を追加する<br>課題3　リンクエラーを調べる | `SplitCalc` | [calc.c](SplitCalc/calc.c)，[calc.h](SplitCalc/calc.h)，[main.c](SplitCalc/main.c) | — | 1 |
| 課題4　ベクトルと行列を分割する | `VectorCalc` | [matrix.c](VectorCalc/matrix.c)，[matrix.h](VectorCalc/matrix.h)，[vector.c](VectorCalc/vector.c)，[vector.h](VectorCalc/vector.h)，[vector_main.c](VectorCalc/vector_main.c) | — | 1 |
| 発展1（ライブラリ側）　静的ライブラリとして使う | `CalcLib` | [calc.c](CalcLib/calc.c)，[calc.h](CalcLib/calc.h) | — | 0 |
| 発展1（アプリ側）　静的ライブラリとして使う | `CalcApp` | [main.c](CalcApp/main.c) | — | 1 |
| 発展2　並べ替えをモジュールにする | `SortModule` | [intlib.c](SortModule/intlib.c)，[intlib.h](SortModule/intlib.h)，[sort_main.c](SortModule/sort_main.c) | 引数 `5` | 17 |
| 発展3　標準ライブラリの契約を確かめる | `LibraryCheck` | [library_check.c](LibraryCheck/library_check.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
