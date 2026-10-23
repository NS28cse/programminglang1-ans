# 第13回 演習（メモリ管理）練習用

- 演習ページ: [ex13](https://t-yokoga.github.io/softprac1/ex13.html)（原稿: [docs/ex13.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex13.md)）・講義: [lec13](https://t-yokoga.github.io/softprac1/lec13.html)（例題: [docs/sample/13/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/13/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week13/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1・課題2 | `Dynamic` | [dynamic.c](Dynamic/dynamic.c) | 引数 `5` | 16 |
| 課題2「追加：独立したコピー」 | `DynamicCopy` | [dynamic.c](DynamicCopy/dynamic.c) | 引数 `5` | 15 |
| 課題3　構造体を確保する関数 | `NewPoint` | [new_point.c](NewPoint/new_point.c) | — | 1 |
| 課題3「失敗を模擬する」 | `NewPointFail` | [new_point.c](NewPointFail/new_point.c) | — | 1 |
| 発展1　`calloc`と`realloc`で配列を拡張する | `GrowArray` | [grow_array.c](GrowArray/grow_array.c) | — | 1 |
| 発展1「`realloc`の失敗を模擬する」 | `GrowArrayFail` | [grow_array.c](GrowArrayFail/grow_array.c) | — | 1 |
| 発展2　`static`変数の寿命を確かめる | `StorageCount` | [count.c](StorageCount/count.c) | — | 1 |
| 発展2「共有変数の宣言」　`static`変数の寿命を確かめる | `SharedCount` | [counter.c](SharedCount/counter.c)，[counter.h](SharedCount/counter.h)，[main.c](SharedCount/main.c) | — | 1 |
| 発展3　不透明な`Vector`の生成と解放 | `DynamicVector` | [vector.c](DynamicVector/vector.c)，[vector.h](DynamicVector/vector.h)，[vector_main.c](DynamicVector/vector_main.c) | — | 1 |
| 発展3「途中で失敗した場合」 | `DynamicVectorFail` | [vector.c](DynamicVectorFail/vector.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
