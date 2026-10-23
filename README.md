# 説明用スライド（`slides` ブランチ）

「プログラミング言語I・ソフトウェア演習I」（C 言語）の TA が，演習中に学生へ**1 対 1 で**説明するときに使うスライド。実務のテーマごとに 1 つずつ作り，[Slidev](https://sli.dev/) で書いている。
このブランチはスライドだけを置き，ビルドした HTML と PDF を GitHub Pages で公開する。解答・テスト・TA 用の資料は `ta` ブランチ（入口は [TA.md](https://github.com/NS28cse/programminglang1-ans/blob/ta/TA.md)）にある。

**公開ページ**: <https://ns28cse.github.io/programminglang1-ans/>（スライドの一覧。各スライドの HTML と PDF）

| スライド | テーマ | 関係する回 |
| --- | --- | --- |
| エラーメッセージを読む（[HTML](https://ns28cse.github.io/programminglang1-ans/error-messages/)・[PDF](https://ns28cse.github.io/programminglang1-ans/error-messages.pdf)・[ソース](error-messages.md)） | 1 件目から読む，指された行と前の行，コンパイルとリンクのエラーの区別 | 第1回〜（リンクは第12回） |
| 動いたら commit，試したら差分（[HTML](https://ns28cse.github.io/programminglang1-ans/version-control/)・[PDF](https://ns28cse.github.io/programminglang1-ans/version-control.pdf)・[ソース](version-control.md)） | Visual Studio の Git で commit・差分・元に戻す | 第2回〜 |
| テストの値を選ぶ（[HTML](https://ns28cse.github.io/programminglang1-ans/test-cases/)・[PDF](https://ns28cse.github.io/programminglang1-ans/test-cases.pdf)・[ソース](test-cases.md)） | 期待値を先に書く，境界の両側，0 回・1 回・複数回，異常な入力 | 第3回〜 |
| デバッガで流れを追う（[HTML](https://ns28cse.github.io/programminglang1-ans/debugger-basics/)・[PDF](https://ns28cse.github.io/programminglang1-ans/debugger-basics.pdf)・[ソース](debugger-basics.md)） | ブレークポイント・ステップオーバー・**Locals** で流れと値を確かめる，探し方の型 | 第4回〜 |
| 読みやすいコードと関数の契約（[HTML](https://ns28cse.github.io/programminglang1-ans/readable-code/)・[PDF](https://ns28cse.github.io/programminglang1-ans/readable-code.pdf)・[ソース](readable-code.md)） | 名前・1 つの関数に 1 つの仕事・数値に名前・受け付ける範囲（契約）をコメントに書く | 第5回〜 |
| 書き込む前に容量を確かめる（[HTML](https://ns28cse.github.io/programminglang1-ans/buffer-capacity/)・[PDF](https://ns28cse.github.io/programminglang1-ans/buffer-capacity.pdf)・[ソース](buffer-capacity.md)） | 配列の範囲，文字列の終端の分の容量，範囲外書き込みは「動いた」でも誤り | 第5回〜（文字列は第6回） |
| 再現できる質問（[HTML](https://ns28cse.github.io/programminglang1-ans/bug-report/)・[PDF](https://ns28cse.github.io/programminglang1-ans/bug-report.pdf)・[ソース](bug-report.md)） | 何を入力し，何を期待し，何が出たか。最小の再現 | 第1回〜（入力は第7回） |

## 使い方（1 対 1 で）

- TA の仕事は学生に 1 対 1 で教えることなので，スライドも**1 人の学生に見せる**ために作っている。全員に向けて発表するものではない。
- 学生のつまずき（実務の手引きの各回の「声かけ」の場面）に出会ったら，その場で公開ページのスライドを学生の画面（またはタブレット・ノート PC）で開き，1〜3 分で一緒に見る。全部を見せなくてよく，要る 1〜2 枚だけでよい。
- 時間がないときは URL を伝え，後で読んでもらう。スライドの本文だけで分かるように書いている（TA がいなくても読める）。
- 発表者ノート（`<!-- -->`）は TA が事前に読むためのもの。そのスライドを使う場面，学生に聞く問いと期待する答え，よくある反応を書いている。ノートは公開ページの発表者ビュー（左下のナビゲーションのボタン，または URL の末尾を `#/presenter/1`）で見られる。
- 内容の詳細は `ta` ブランチの[実務の手引き](https://github.com/NS28cse/programminglang1-ans/blob/ta/ta-guide/README.md)にある。スライドはそのテーマの要点を，学生が見て分かる形にしたもの。
- 例には演習の課題やデバッグの題材ではなく，別のプログラムを使っている（答えを見せないため）。
- Visual Studio の画面の表記は Visual Studio 2026（英語版）で，日本語版の名前を添えている（[実務の手引きの対応表](https://github.com/NS28cse/programminglang1-ans/blob/ta/ta-guide/README.md#使い方)）。
- HTML は矢印キーで進み，途中のスライドで再読み込みしても同じスライドに戻る。ネットにつながらないときは PDF を使う（PDF にはノートが入らない）。

## 手元で見る・書き出す

Node.js 22.12 以上を入れて，次を実行する。

```sh
npm ci                             # package-lock.json のとおりに入れる（初回だけ。PDF 用の Chromium も入る）
npx slidev debugger-basics.md      # http://localhost:3030 で見る（書きながら確かめる）
npx slidev build debugger-basics.md --base ./ --out dist/debugger-basics   # HTML（静的なサイト）
npx slidev export debugger-basics.md --output dist/debugger-basics.pdf     # PDF
npx slidev export-notes debugger-basics.md                                 # 発表者ノートの PDF（TA の準備用）
```

- Linux で PDF に書き出すときは，Chromium が使う OS のライブラリも要る（`npx playwright install --with-deps chromium`）。
- フォント（Noto Sans JP・Fira Code）は Google Fonts から読み込むので，ネットにつながらないと別のフォントで表示される。その場合は PDF を使う。
- PDF は，クリックで順に表示する部分の最後の状態を書き出す。1 クリックずつ別のページにするときは `--with-clicks` を付ける。`--format pptx` で PowerPoint にも書き出せるが，各スライドは画像になる。

## 公開のしくみ

`.github/workflows/slides.yml` が，このブランチへの push のたびに，`README.md` 以外の `.md` をすべて HTML（`--base ./`，各スライドの `routerMode: hash`）と PDF に書き出し，一覧のページと一緒に GitHub Pages に公開する。
このブランチへの PR では書き出しだけを行い，成果物（**Actions** の実行結果の **Artifacts** の `slides`）にする。

公開には，リポジトリの設定が 2 つ要る（最初の 1 回だけ）。

1. **Settings > Pages** の **Source** を **GitHub Actions** にする。
2. **Settings > Environments > github-pages** の **Deployment branches and tags** に `slides` を加える（既定では既定のブランチからしか公開できない）。

公開されたページは誰でも見られる。**発表者ノートも公開される**（HTML の中に入る）ので，学生に見せたくない内容（演習の答えなど）はノートにも書かない。

## 追加・修正するとき

スライドを足す手順:

1. `<名前>.md`（テーマを表す英語の名前）を作り，先頭の frontmatter に `title:`（一覧のページの見出しになる）・`info:`（1 行目に関係する回）・`routerMode: hash`・`lineNumbers: true` を書く（`debugger-basics.md` を写すとよい）。CI は `README.md` 以外の `.md` をすべて書き出す。
2. この README の表に足す（公開の URL は `https://ns28cse.github.io/programminglang1-ans/<名前>/` と `<名前>.pdf`）。
3. `ta` ブランチで，実務の手引きの「説明用スライド」の表と，関係する回の節の「関連」に公開ページの URL を足す。
4. HTML と PDF を書き出し，PDF の各ページを画像にして文字がはみ出していないか・切れていないかを確かめる。

内容の決まり:

- **テーマごとに 1 つ**作る（回ごとには作らない）。frontmatter の `info:` の 1 行目に「関係する回: 第N回〜（…）」と書き，一覧のページにも出す。
- **1 対 1 で 1〜3 分**で使える長さにする（表紙・付録を除いて 3〜6 枚）。1 枚ずつ独立して使えるようにし，学生がスライドだけを読んでも分かる文にする（言うことをノートだけに置かない）。
- 全員への発表を前提にした書き方（「今日は」「近くの人と相談」「時間の目安」など）をしない。
- 内容は実務の手引きのそのテーマの節（主に「どの回でも使う型」と，関係する回の節）に合わせ，詳しい説明は手引きに置く（スライドに手引きと違う内容を書かない）。
- 例には，演習の課題やデバッグの題材と**同じ形・同じ種類の誤り**を使わない（答えを見せないため）。
- 関係する回のうち最初の回までに授業で扱った文法・操作だけを前提にし，それより後の回の内容や未習のものは「（第N回から）」「（授業では未習）」と断る。Visual Studio の表記は英語版の太字で，日本語版の名前を添える（実務の手引きの対応表と同じ名前）。
- 各スライド（付録を含む）の発表者ノートに，使う場面・学生に聞く問いと期待する答え・よくある反応を書く。
- 例のコード・追跡表・期待値・診断の文面は実際にコンパイル・実行して確かめる。ステップ実行の順序を見せるときは，どこから F10 を押すかを書く。
- コードは合字にしない（`style.css`）。コードの強調の指定は最後を `all` にする（PDF は最後のクリックの状態を書き出すため）。
- HTML は `routerMode: hash` と `--base ./` で書き出す（どの URL に置いても，途中で再読み込みしても動くように）。
- 評価は `ta` ブランチの評価エージェント（`.claude/agents/ta-material-reviewer.md`）の観点で行う。
- 依存パッケージは `package-lock.json` で固定している。更新は授業の前にまとめて `npm update` し，HTML と PDF の書き出しが通ることを確かめてから commit する。`npm audit` の警告の多くは書き出しに使う開発用の部品のもので，公開する HTML・PDF には関係しない。
