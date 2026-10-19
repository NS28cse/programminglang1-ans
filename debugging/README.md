# デバッグの題材（TA 用）

学生が実際にしそうな誤りを 1 つずつ入れた，短いプログラムの集まりです。第4回〜第14回の各回に 1〜2 題あり，それぞれの回までに講義で扱った文法・関数だけで書いています。
どの誤りもコンパイラの警告では見つかりません（MSVC `/W4`，GCC・Clang `-Wall -Wextra -Wpedantic` で警告 0）。演習を早く終えた学生や，デバッガの使い方を練習させたい場面で，「動くのに結果が違う」プログラムの原因を探す題材として渡します。

> [!WARNING]
> 各題材の README.md は原因と直し方（答え）を含みます。学生に渡すのはソース（`.c`・`.h`）と入力ファイルだけにしてください。

## 使い方

### TA が症状を確かめる（Visual Studio）

1. リポジトリを **File > Open > Folder** で開き，構成を `Windows / MSVC (x64 Debug)` にする（[ルートの README](../README.md) の「Visual Studio で使う」）。
2. ツールバーの **Startup Item** で `debugging BugEvenSum` のような項目を選ぶ。作業ディレクトリは題材のフォルダ，引数は `run.args` になる（`debugging BugCharCount  [input.txt]` のように引数が項目名に出る）。
3. Ctrl+F5（**Debug > Start Without Debugging**）で実行し，題材の README の「症状」と同じになることを確かめる。F5（**Debug > Start Debugging**）でデバッガの手順を事前に試しておく。

症状は **Debug 構成**で確かめる。実行時チェック（`/RTC1`）や Debug の C ランタイムの検査で見える症状は，Release 構成では出ない。
VS Code では，題材の `.c` を開いた状態で「開いている課題を実行」を選ぶ（作業ディレクトリは題材のフォルダ。引数が要る題材は「引数つきで実行」）。

### 学生への渡し方

- 渡すもの: 題材フォルダの `.c`・`.h` と，`input.txt` などの入力ファイル。`README.md`・`CMakeLists.txt`・`tests/`・`variants/` は渡さない（答えと，直した版の期待値を含む）。
- 学生は授業と同じく **Create a new project > Empty Project** で空のプロジェクトを作り，**Add > Existing Item** でソースを入れる。入力ファイルはプロジェクトフォルダに置き，引数が要る題材は **Configuration Properties > Debugging > Command Arguments** に設定する（第10回の手順）。
- 最初に言うのは 3 つだけ: **プログラムがするはずのこと（期待する出力）**，**実際の症状**，**再現の手順**。各題材の README の「学生への渡し方」に，そのまま読み上げられる文を載せている。バグの場所・種類は言わない。
- 目安は 10〜15 分。手が止まったら，README の「ヒントの段階」を 1 段ずつ出す（1 段出したら 3〜5 分待つ）。
- 直す前に，原因を 1 文で言わせる（「〜なので〜になっていた」）。直したら，同じ再現の手順でもう一度実行させる。

### TA が答えを先に見せない

- 学生の画面を一緒に見るときも，マウスとキーボードは学生が持つ。TA は「どこで止める？」「その変数は今いくつ？」と問いで進める。
- 原因の行を指さしたり，直したコードを見せたりしない。ヒントは「どこを見るか」「何と何を比べるか」までにする。
- 未定義動作の題材（下の表）は，「表示が正しいから問題ない」と結論させないことがねらいの 1 つ。Linux や Release 構成で症状が出なくても，Debug 構成の MSVC のダイアログか AddressSanitizer の報告で誤りを確かめる。

## デバッグの進め方の型

どの題材も，次の順で進めさせる（[practice/README.md](../practice/README.md#デバッグの進め方) の「デバッグの進め方」と同じ）。

1. **再現する**: 毎回同じ症状が出る手順（入力・引数・操作）を書く。期待した出力と実際の出力を並べる。
2. **範囲を絞る**: 「ここまでは正しい」と言える場所を探す。ブレークポイントで途中の値を見る，入力を小さくする（`n` を 10 から 4 へ，ファイルを空に など）。
3. **仮説を立てる**: 原因と，それが正しければ何が見えるはずかを 1 文で言う（「`sum` を行ごとに 0 にしていないので，2 行目を足し始めるときの `sum` は 0 ではなく 6 のはず」）。
4. **確かめる**: デバッガで予想した値と実際の値を比べる。外れたら 2 に戻る。
5. **直す**: 1 か所だけ直し，再現の手順でもう一度確かめる。
6. **テストを足す**: 同じ誤りを捕まえる入力と期待する出力を書き残す（各題材の「学生への問い」に，誤りを見つけられる入力の例がある）。

## 題材の一覧

操作の「（未習）」は授業では扱っていない操作で，その題材では使わなくても探せる（使うなら TA が初めて見せる）。

| 回 | 題材 | プログラムがすること | バグの種類 | 使う操作 | 未定義動作 |
| --- | --- | --- | --- | --- | --- |
| 第4回 | [BugEvenSum](BugEvenSum/README.md) | 1〜n の偶数の合計 | 境界（ループの条件の差 1） | F9・F5・F10・**Locals** | いいえ |
| 第4回 | [BugSkipCount](BugSkipCount/README.md) | 3 の倍数を飛ばして表示 | 無限ループ（`continue` で更新を飛ばす） | **Break All**（未習）・F10・**Locals** | いいえ |
| 第5回 | [BugRowSum](BugRowSum/README.md) | 二次元配列の行ごとの合計 | 初期化の位置（累積変数をループの外で 1 回だけ 0 に） | F9・F5（**Continue**）・**Locals** | いいえ |
| 第5回 | [BugGrade](BugGrade/README.md) | 点数から A〜D を返す関数 | 条件の順序（`else if` の並び） | 関数の中の F9・F10・**Locals** | いいえ |
| 第6回 | [BugDigitSum](BugDigitSum/README.md) | 数字の文字列の各桁の和 | 文字と数の取り違え（`- '0'` の忘れ） | F9・F10・**Locals**（文字コードの表示） | いいえ |
| 第6回 | [BugAverage](BugAverage/README.md) | 合計と平均 | 整数除算（代入先が `double` でも割り算は `int`） | F9・**Locals**（**Watch 1** は未習） | いいえ |
| 第7回 | [BugUpper](BugUpper/README.md) | 入力を大文字にして写す | 入力の読み方（1 回の繰り返しで `getchar` を 2 回） | F9・F10・**Locals**，コンソールへの入力と `EOF` | いいえ |
| 第7回 | [BugReverseWord](BugReverseWord/README.md) | 8 文字までの単語を逆順に表示 | 配列の範囲外（終端 `'\0'` の分の要素がない） | 実行時チェックのダイアログ・F9・**Locals**（**Memory 1** は未習） | **はい** |
| 第8回 | [BugCopyText](BugCopyText/README.md) | 文字列をコピーする関数 | 文字列の終端のコピー忘れ | F9・**Locals**（F11・**Watch 1** は未習） | いいえ |
| 第9回 | [BugFindMax](BugFindMax/README.md) | 最大の要素の場所を返す関数 | ポインタの指す先（ポインタの値渡しで呼び出し元を書き換えられない） | F9・F10・**Locals**（**Watch 1** は未習） | いいえ |
| 第10回 | [BugCharCount](BugCharCount/README.md) | ファイルの文字数と行数 | ファイルの読み方（`while (!feof(fp))` で `EOF` も数える） | **Command Arguments**・F9・F5（**Continue**）・**Locals** | いいえ |
| 第11回 | [BugStudentNames](BugStudentNames/README.md) | 名簿を読んで表示 | 構造体のポインタメンバの共有（全員が同じ配列を指す） | F9・F5（**Continue**）・**Locals**（構造体の配列を展開） | いいえ |
| 第12回 | [BugSharedCounter](BugSharedCounter/README.md) | 呼び出し回数を数える（3 ファイル） | リンケージ（ヘッダの `static` 変数がファイルごとに別物） | 2 つのファイルで F9・データヒント（未習） | いいえ |
| 第13回 | [BugMallocSize](BugMallocSize/README.md) | `n` 個の `int` を動的に確保 | `malloc` のサイズの誤り（要素数をバイト数として渡す） | ヒープ破壊のダイアログ・**Command Arguments**・**Watch 1**（`values,5`） | **はい** |
| 第13回 | [BugBackupScores](BugBackupScores/README.md) | 点数の控えを作ってから元を解放 | 解放後の使用・二重解放（構造体の代入で配列を共有） | F9・F10・**Locals**・**Watch 1** | **はい** |
| 第14回 | [BugFactorial](BugFactorial/README.md) | 0!〜5! の表 | 再帰の基底条件（0 で止まらない） | 例外で止まる・**Call Stack**・**Locals**・F11 | 異常終了（スタックオーバーフロー） |

## テスト

- 結果が決まる題材は，`tests/` に**バグ入りの版の症状**（間違った出力）を，`variants/tests/` に**直した版**の正しい出力を置いている。直した版は，各題材の `CMakeLists.txt` に書いた置き換え（README の「直し方」と同じ差分）でソースを書き換えてビルドする。
- 未定義動作・異常終了・無限ループの題材（`BugReverseWord`・`BugMallocSize`・`BugBackupScores`・`BugFactorial`・`BugSkipCount`）は，バグ入りの版をテストで実行せず，直した版だけをテストする。
- テスト名は `debugging/<題材>/<ケース>`（症状）と `debugging/<題材>/variant_fixed…`（直した版）。`-DSOFTPRAC_WEEKS=debugging` を付けて構成すると，この題材だけをビルド・テストできる。

題材を足すときの規則は [CONTRIBUTING.md](../CONTRIBUTING.md) の「フォルダ構成」にある。
