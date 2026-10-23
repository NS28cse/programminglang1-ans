# 説明用スライド（`slides` ブランチ）

「プログラミング言語I・ソフトウェア演習I」（C 言語）の演習の前に，TA が全員へ数分で見せる説明のスライド。[Slidev](https://sli.dev/) で書いている。
このブランチはスライドだけを置き，ビルドした HTML と PDF を GitHub Pages で公開する。解答・テスト・TA 用の資料は `ta` ブランチ（入口は [TA.md](https://github.com/NS28cse/programminglang1-ans/blob/ta/TA.md)）にある。

**公開ページ**: <https://ns28cse.github.io/programminglang1-ans/>（スライドの一覧。各スライドの HTML と PDF）

| スライド | 回 | 内容 | 時間 |
| --- | --- | --- | --- |
| デバッガで流れを追う（[HTML](https://ns28cse.github.io/programminglang1-ans/debugger-basics/)・[PDF](https://ns28cse.github.io/programminglang1-ans/debugger-basics.pdf)・[ソース](debugger-basics.md)） | 第4回（制御構造） | ブレークポイント・ステップオーバー・**Locals** で，ループの流れと変数の変化を確かめる。探し方の型（再現 → 絞り込み → 仮説 → 確かめる → 直す → テスト） | 5〜7 分 |

- 内容の詳細は `ta` ブランチの[実務の手引き](https://github.com/NS28cse/programminglang1-ans/blob/ta/ta-guide/README.md)にあり，スライドはその一部を全員向けに見せる形にしたもの。手引きは「巡回中に個別に 1〜3 分で」が原則なので，スライドを全員に見せるのは担当教員の了承を得たときだけにする（授業時間を増やさないため）。
- 例には演習の課題やデバッグの題材ではなく，別のプログラムを使っている（答えを見せないため）。
- 各スライドの発表者ノート（`<!-- -->`）に，時間の目安・言うこと・出やすい質問と答えを書いている。
- Visual Studio の画面の表記は Visual Studio 2026（英語版）で，日本語版の名前を添えている（[実務の手引きの対応表](https://github.com/NS28cse/programminglang1-ans/blob/ta/ta-guide/README.md#使い方)）。
- 最後の「付録」のスライドは発表では使わず，質問されたときや配布用に使う。

## 見る・配る・発表する

- **公開ページ**から，スライド（ブラウザーで操作できる HTML）か PDF を開く。発表は HTML で，配布やネットにつながらない教室では PDF を使う。
- HTML は矢印キーで進み，途中のスライドで再読み込みしても同じスライドに戻る。
- 発表者ビュー（ノートと次のスライドが見える）は，スライドの左下に出るナビゲーションのボタンを押すか，URL の末尾を `#/presenter/1` にして開く。
  プロジェクターに映すスライドは，同じブラウザーの別のウィンドウで開く（ページは同じブラウザーの中でだけ連動する）。
- 問いの答えは発表者ノートにだけある。PDF にはノートが入らないので，ネットにつながらない教室ではノートを印刷しておく（下の `npx slidev export-notes`）。

## 手元で発表する・書き出す

Node.js 22.12 以上を入れて，次を実行する。

```sh
npm ci                             # package-lock.json のとおりに入れる（初回だけ。PDF 用の Chromium も入る）
npx slidev debugger-basics.md      # http://localhost:3030 で発表する
npx slidev build debugger-basics.md --base ./ --out dist/debugger-basics   # HTML（静的なサイト）
npx slidev export debugger-basics.md --output dist/debugger-basics.pdf     # PDF
npx slidev export-notes debugger-basics.md                                 # 発表者ノートの PDF（印刷用）
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

1. `<名前>.md` を作り，先頭の frontmatter に `title:`（一覧のページの見出しになる）・`routerMode: hash`・`lineNumbers: true` を書く（`debugger-basics.md` を写すとよい）。CI は `README.md` 以外の `.md` をすべて書き出す。
2. この README の表に足す（公開の URL は `https://ns28cse.github.io/programminglang1-ans/<名前>/` と `<名前>.pdf`）。
3. `ta` ブランチで，実務の手引きのその回の節の「関連」と，TA.md の説明用スライドの行に公開ページの URL を足す。
4. HTML と PDF を書き出し，PDF の各ページを画像にして文字がはみ出していないか・切れていないかを確かめる。

内容の決まり:

- 内容は実務の手引きの該当する回の節に合わせ，詳しい説明は手引きに置く（スライドに手引きと違う内容を書かない）。
- 例には，演習の課題やデバッグの題材と**同じ形・同じ種類の誤り**を使わない（答えを見せないため）。
- その回までに授業で扱った文法・操作だけを前提にし，未習のものは「（授業では未習）」か発表者ノートで断る。Visual Studio の表記は英語版の太字で，日本語版の名前を添える（実務の手引きの対応表と同じ名前）。
- 各スライド（付録を含む）の発表者ノートに，時間の目安・言うこと・出やすい質問と答えを書く。問いのスライドの答えはノートに書く。
- 例のコード・追跡表・期待値は実際にコンパイル・実行して確かめる。ステップ実行の順序を見せるときは，どこから F10 を押すかを書く。
- コードは合字にしない（`style.css`）。コードの強調の指定は最後を `all` にする（PDF は最後のクリックの状態を書き出すため）。
- HTML は `routerMode: hash` と `--base ./` で書き出す（どの URL に置いても，途中で再読み込みしても動くように）。
- 評価は `ta` ブランチの評価エージェント（`.claude/agents/ta-material-reviewer.md`）の観点で行う。
- 依存パッケージは `package-lock.json` で固定している。更新は授業の前にまとめて `npm update` し，HTML と PDF の書き出しが通ることを確かめてから commit する。`npm audit` の警告の多くは書き出しに使う開発用の部品のもので，公開する HTML・PDF には関係しない。
