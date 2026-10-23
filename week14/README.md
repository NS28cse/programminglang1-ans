# 第14回 演習（再帰）練習用

- 演習ページ: [ex14](https://t-yokoga.github.io/softprac1/ex14.html)（原稿: [docs/ex14.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex14.md)）・講義: [lec14](https://t-yokoga.github.io/softprac1/lec14.html)（例題: [docs/sample/14/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/14/)）

演習ページを読んで，各プロジェクトの雛形（空の `main`）に解答を書きます。書いたらビルドしてテストを実行し，期待する出力と一致するか確かめます（手順は[ルートの README](../README.md#テストで確かめる)）。
説明・表の記入・確認問題は演習ページを見て自分で答え，[`main` ブランチのこの回の README](https://github.com/NS28cse/programminglang1-ans/blob/main/week14/README.md) で答え合わせをします。

| 課題 | プロジェクト | 作るファイル | 実行に使うもの | テスト数 |
| --- | --- | --- | --- | ---: |
| 課題1 階乗の境界 | `Factorial` | [recursion.c](Factorial/recursion.c) | — | 1 |
| 課題2 再帰の復帰順 | `Trace` | [trace.c](Trace/trace.c) | — | 1 |
| 課題3 互除法を反復へ書き換える | `GcdLoop` | [gcd_loop.c](GcdLoop/gcd_loop.c) | — | 1 |
| 課題4 再帰の入口を安全にする | `CheckedFactorial` | [checked_factorial.c](CheckedFactorial/checked_factorial.c) | — | 1 |
| 発展1 再帰の呼び出し数 | `Fibonacci` | [fibonacci.c](Fibonacci/fibonacci.c) | — | 1 |
| 発展2 二分木の3つの走査 | `TreeTraversal` | [tree.c](TreeTraversal/tree.c) | — | 1 |

- テスト数は `tests/` の期待する出力の数です。演習ページの「値を変えて試す」小問のテストはありません（自分で書き換えて，`main` の README の結果と比べる）。
- 入力と引数は `tests/<ケース>.in`・`tests/<ケース>.args`，期待する出力は `tests/<ケース>.out` にあります。
