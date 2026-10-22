# 説明用スライド（`slides/`）

TA が演習の前に全員へ数分で見せる説明のスライドです。[Slidev](https://sli.dev/) で書いています。
内容の詳細は[実務の手引き](../ta-guide/README.md)にあり，スライドはその一部を全員向けに見せる形にしたものです。
手引きは「巡回中に個別に 1〜3 分で」が原則なので，スライドを全員に見せるのは担当教員の了承を得たときだけにします（授業時間を増やさないため）。

| スライド | 回 | 内容 | 時間 |
| --- | --- | --- | --- |
| [debugger-basics.md](debugger-basics.md) | 第4回（制御構造） | ブレークポイント・ステップオーバー・**Locals** で，ループの流れと変数の変化を確かめる。探し方の型（再現 → 絞り込み → 仮説 → 確かめる → 直す → テスト） | 5〜7 分 |

- 例には演習の課題やデバッグの題材ではなく，別のプログラムを使っています（答えを見せないため）。
- 各スライドの発表者ノート（`<!-- -->`）に，時間の目安・言うこと・出やすい質問と答えを書いています。
- Visual Studio の画面の表記は Visual Studio 2026（英語版）で，日本語版の名前を添えています（[実務の手引きの対応表](../ta-guide/README.md#使い方)）。
- 最後の「付録」のスライドは発表では使わず，質問されたときや配布用に使います。

## 見る・配る

- **PDF**: GitHub の **Actions** タブで `slides` ワークフローの実行結果を開き，**Artifacts** の `slides` をダウンロードすると `debugger-basics.pdf` が入っています。配布や，ネットにつながらない教室ではこれを使います。
- **HTML**（操作できるスライド）: 同じ `slides` の中の `debugger-basics/` です。ブラウザーでファイルを直接開いても動かないので，そのフォルダで `npx serve` などの簡単な Web サーバーを起動して開きます。
- **GitHub Pages**: 有効にしている場合は，`ta` ブランチへの push で公開されます（下の「[GitHub Pages](#github-pages)」）。

## 手元で発表する

Node.js 22.12 以上を入れて，次を実行します。

```sh
cd slides
npm ci                             # package-lock.json のとおりに入れる（初回だけ。PDF 用の Chromium も入る）
npx slidev debugger-basics.md      # http://localhost:3030 で発表する
```

- 発表者ビュー（ノートと次のスライドが見える）は，画面の左下に出るナビゲーションのボタンから開きます。
- フォント（Noto Sans JP・Fira Code）は Google Fonts から読み込むので，ネットにつながらないと別のフォントで表示されます。その場合は PDF を使います。

## 書き出す

```sh
npx slidev build debugger-basics.md --base ./ --out dist/debugger-basics   # HTML（静的なサイト）
npx slidev export debugger-basics.md --output dist/debugger-basics.pdf     # PDF
```

- PDF は，クリックで順に表示する部分の最後の状態を書き出します（コードの強調は最後に全体を表示する指定にしてあります）。1 クリックずつ別のページにするときは `--with-clicks` を付けます。
- `--format pptx` で PowerPoint にも書き出せますが，各スライドは画像になるので，文言は PowerPoint では直せません。

## 追加・修正するとき

規則は [CONTRIBUTING の「説明用スライド」](../CONTRIBUTING.md#説明用スライドslides)にあります。

- スライドは 1 本 1 ファイル（`slides/<名前>.md`）です。CI は `slides/` の `README.md` 以外の `.md` をすべて書き出すので，追加したらこのファイルの一覧に加えるだけです。
- 依存パッケージは `package-lock.json` で固定しています。更新は授業の前にまとめて `npm update` し，HTML と PDF の書き出しが通ることを確かめてから commit します。`npm audit` の警告の多くは書き出しに使う開発用の部品のもので，公開する HTML・PDF には関係しません。

## GitHub Pages

公開リポジトリなら，次の 3 つを設定すると，`ta` ブランチへの push のたびに `https://<ユーザー名>.github.io/<リポジトリ名>/` にスライドの一覧（HTML と PDF）が公開されます。公開されたページは誰でも見られます。

1. **Settings > Pages** の **Source** を **GitHub Actions** にする。
2. **Settings > Environments > github-pages** の **Deployment branches** に `ta` を加える（既定では既定のブランチからしか公開できない）。
3. **Settings > Secrets and variables > Actions** の **Variables** に `SLIDES_PAGES` = `true` を加える（これがないと公開の手順は動かない）。
