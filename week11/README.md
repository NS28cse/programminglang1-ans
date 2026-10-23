# 第11回 演習（構造体）練習用

- 演習ページ: [ex11](https://t-yokoga.github.io/softprac1/ex11.html)（原稿: [docs/ex11.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex11.md)）・講義: [lec11](https://t-yokoga.github.io/softprac1/lec11.html)（例題: [docs/sample/11/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/11/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week11/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1 値とポインタの違い | `PointMove` | [structs.c](PointMove/structs.c) | — | 1 |
| 課題2 点数の平均 | `Students` | [students.c](Students/students.c) | — | 1 |
| 課題3 長方形を表す | `Rect` | [rect.c](Rect/rect.c) | — | 1 |
| 課題4 配列メンバとポインタメンバ | `CopyMembers` | [copy_members.c](CopyMembers/copy_members.c) | — | 1 |
| 発展1 初期化と構造体を返す関数 | `PointInit` | [point_init.c](PointInit/point_init.c) | — | 1 |
| 発展2 長方形の正規化と包含判定 | `RectContains` | [rect_contains.c](RectContains/rect_contains.c) | — | 1 |
| 発展3 構造体のサイズ | `StructLayout` | [struct_layout.c](StructLayout/struct_layout.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
