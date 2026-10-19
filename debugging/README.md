# デバッグの題材（TA 用）

学生が実際にしそうな誤りを 1 つずつ入れた，短いプログラムの集まりである。第4回〜第14回の各回に 1〜2 題あり，それぞれの回までに講義で扱った文法・関数だけで書いている。
どの誤りもコンパイラの警告では見つからない（MSVC `/W4`，GCC・Clang `-Wall -Wextra -Wpedantic` で警告 0）。演習を早く終えた学生や，デバッガの使い方を練習させたい場面で，「動くのに結果が違う」プログラムの原因を探す題材として渡す。

> [!WARNING]
> 各題材の README.md は原因と直し方（答え）を含む。学生に渡すのはソース（`.c`・`.h`）と入力ファイルだけにする。

## 使い方

- 各回の解答 README の冒頭の「TA 用の資料」から，その回の題材と[実務の手引き](../ta-guide/README.md)の節へ移れる。リポジトリ全体の案内は[ルートの README](../README.md)にある。
- 題材の README の Visual Studio の表記は英語版である。授業資料（日本語の表記）・日本語版の画面との対応は，実務の手引きの「使い方」の[表記の対応表](../ta-guide/README.md#使い方)を見る。

### TA が症状を確かめる（Visual Studio）

1. リポジトリを **File > Open > Folder** で開き，構成を **`Windows / MSVC (x64 Debug)`** にする（ルートの README の [Visual Studio で使う](../README.md#visual-studio-で使うwindows)）。
2. ツールバーの **Startup Item** で `debugging BugEvenSum` のような項目を選ぶ。作業ディレクトリは題材のフォルダ，引数は `run.args` になる（`debugging BugCharCount  [input.txt]` のように引数が項目名に出る）。
3. Ctrl+F5（**Debug > Start Without Debugging**）で実行し，題材の README の「症状」と同じになることを確かめる。F5（**Debug > Start Debugging**）でデバッガの手順を事前に試しておく。

症状は **Debug 構成**で確かめる。実行時チェック（`/RTC1`）や Debug の C ランタイムの検査で見える症状は，Release 構成では出ない。
VS Code では，題材の `.c` を開いた状態で **Run and Debug** ビュー（Ctrl+Shift+D）の構成から「開いている課題を実行」を選ぶ（作業ディレクトリは題材のフォルダ）。引数が要る題材は「開いている課題を引数つきで実行」を選ぶ。この構成の `args` は `["input.txt"]` なので，`BugCharCount` はそのまま使え，`BugMallocSize` は `.vscode/launch.json` の `args` を `["5"]` に書き換える。

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

どの題材も，実務の手引きの「[デバッグの進め方](../ta-guide/README.md#デバッグの進め方)」の型で進めさせる。題材では次のように使う。

1. **再現する**: 題材の README の「症状」の手順で実行し，期待した出力と実際の出力を並べる。
2. **範囲を絞る**: 入力を小さくして（`n` を 10 から 4 へ，ファイルを空に など）ブレークポイントで途中の値を見る。
3. **仮説を立てる**: 「`sum` を行ごとに 0 にしていないので，2 行目を足し始めるときの `sum` は 0 ではなく 6 のはず」のように 1 文で言わせる。
4. **確かめる**: デバッガで予想した値と実際の値を比べる。外れたら 2 に戻る。
5. **直す**: 1 か所だけ直し，同じ手順でもう一度実行する。
6. **テストを足す**: 各題材の「学生への問い」にある，誤りを捕まえる入力と期待する出力を書き残させる。

## 題材の一覧

操作の「（未習）」は授業では扱っていない操作で，その題材では使わなくても探せる（使うなら TA が初めて見せる）。

| 回 | 題材 | プログラムがすること | バグの種類 | 使う操作 | 未定義動作 |
| --- | --- | --- | --- | --- | --- |
| 第4回 | [BugEvenSum](BugEvenSum/README.md) | 1〜n の偶数の合計 | 境界（ループの条件の差 1） | F9・F5・F10・**Locals** | いいえ |
| 第4回 | [BugSkipCount](BugSkipCount/README.md) | 3 の倍数を飛ばして表示 | 無限ループ（`continue` で更新を飛ばす） | **Break All**（未習）・F10・**Locals** | いいえ |
| 第5回 | [BugRowSum](BugRowSum/README.md) | 二次元配列の行ごとの合計 | 初期化の位置（累積変数をループの外で 1 回だけ 0 に） | F9・F5（**Continue**）・**Locals** | いいえ |
| 第5回 | [BugGrade](BugGrade/README.md) | 点数から A〜D を返す関数 | 条件の順序（`else if` の並び） | 関数の中の F9・F10・**Locals** | いいえ |
| 第6回 | [BugDigitSum](BugDigitSum/README.md) | 数字の文字列の各桁の和 | 文字と数の取り違え（`- '0'` の忘れ） | F9・F10・**Locals**（文字コードの表示） | いいえ |
| 第6回 | [BugAnswerCheck](BugAnswerCheck/README.md) | 答えと解答を `strcmp` で比べる | 戻り値の読み違い（`if (strcmp(a, b))` を「等しい」と読む） | 関数の中の F9・F10・**Locals**（**Autos**・**Watch 1** は未習） | いいえ |
| 第7回 | [BugUpper](BugUpper/README.md) | 入力を大文字にして写す | 入力の読み方（1 回の繰り返しで `getchar` を 2 回） | F9・F10・**Locals**，コンソールへの入力と `EOF` | いいえ |
| 第7回 | [BugReverseWord](BugReverseWord/README.md) | 8 文字までの単語を逆順に表示 | 配列の範囲外（終端 `'\0'` の分の要素がない） | 実行時チェックのダイアログ・F9・**Locals**（**Memory 1** は未習） | **はい** |
| 第8回 | [BugCopyText](BugCopyText/README.md) | 文字列をコピーする関数 | 文字列の終端のコピー忘れ | F9・**Locals**（F11・**Watch 1** は未習） | いいえ |
| 第9回 | [BugFindMax](BugFindMax/README.md) | 最大の要素の場所を返す関数 | ポインタの指す先（ポインタの値渡しで呼び出し元を書き換えられない） | F9・F10・**Locals**（**Watch 1** は未習） | いいえ |
| 第10回 | [BugCharCount](BugCharCount/README.md) | ファイルの文字数と行数 | ファイルの読み方（`while (!feof(fp))` で `EOF` も数える） | **Command Arguments**・F9・F5（**Continue**）・**Locals** | いいえ |
| 第11回 | [BugStudentNames](BugStudentNames/README.md) | 名簿を読んで表示 | 構造体のポインタメンバの共有（全員が同じ配列を指す） | F9・F5（**Continue**）・**Locals**（構造体の配列を展開） | いいえ |
| 第12回 | [BugSharedCounter](BugSharedCounter/README.md) | 呼び出し回数を数える（3 ファイル） | リンケージ（ヘッダの `static` 変数がファイルごとに別物） | 2 つのファイルで F9・データヒント（DataTip。未習） | いいえ |
| 第13回 | [BugMallocSize](BugMallocSize/README.md) | `n` 個の `int` を動的に確保 | `malloc` のサイズの誤り（要素数をバイト数として渡す） | ヒープ破壊のダイアログ・**Command Arguments**・**Watch 1**（`values,5`） | **はい** |
| 第13回 | [BugBackupScores](BugBackupScores/README.md) | 点数の控えを作ってから元を解放 | 解放後の使用・二重解放（構造体の代入で配列を共有） | F9・F10・**Locals**・**Watch 1** | **はい** |
| 第14回 | [BugFactorial](BugFactorial/README.md) | 0!〜5! の表 | 再帰の基底条件（0 で止まらない） | 例外で止まる・**Call Stack**・**Locals**・F11 | 異常終了（スタックオーバーフロー） |
| 第14回 | [BugFactorialOverflow](BugFactorialOverflow/README.md) | 0!〜15! の表 | `int` の桁あふれ（型の上限を確かめていない） | F9・F11・**Locals**（**Autos** の戻り値は未習） | **はい** |

## テスト

- 結果が決まる題材は，`tests/` に**バグ入りの版の症状**（間違った出力）を，`variants/tests/` に**直した版**の正しい出力を置いている。直した版は，各題材の `CMakeLists.txt` に書いた置き換え（README の「直し方」と同じ差分）でソースを書き換えてビルドする。
- 未定義動作・異常終了・無限ループの題材（`BugReverseWord`・`BugMallocSize`・`BugBackupScores`・`BugFactorialOverflow`・`BugFactorial`・`BugSkipCount`）は，バグ入りの版をテストで実行せず，直した版だけをテストする。
- テスト名は `debugging/<題材>/<ケース>`（症状）と `debugging/<題材>/variant_fixed…`（直した版）。`-DSOFTPRAC_WEEKS=debugging` を付けて構成すると，この題材だけをビルド・テストできる。

題材を足すときの規則は [CONTRIBUTING.md](../CONTRIBUTING.md#デバッグの題材debugging) にある。
