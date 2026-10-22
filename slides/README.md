# 説明用スライド（`slides/`）

TA が演習の前に全員へ数分で見せる説明のスライドです。[Slidev](https://sli.dev/) で書いています。
内容の詳細は[実務の手引き](../ta-guide/README.md)にあり，スライドはその一部を全員向けに見せる形にしたものです。

| スライド | 回 | 内容 | 時間 |
| --- | --- | --- | --- |
| [debugger-basics.md](debugger-basics.md) | 第4回（制御構造） | ブレークポイント・ステップオーバー・**Locals** で，ループの流れと変数の変化を確かめる。探し方の型（再現 → 絞り込み → 仮説 → 確かめる → 直す → テスト） | 5〜7 分 |

- 例には演習の課題そのものではなく，同じ形の別のプログラムを使っています（課題の答えを見せないため）。
- 発表者ノート（各スライドの `<!-- -->`）に，TA 向けの補足（時間の目安，よくある質問，見せてもよい未習の操作）を書いています。
- Visual Studio の画面の表記は Visual Studio 2026（英語版）で，日本語版の名前を添えています（[実務の手引きの対応表](../ta-guide/README.md#使い方)）。

## 見る・発表する

CI が作った HTML（操作できるスライド）と PDF は，GitHub の **Actions** タブの `slides` ワークフローの実行結果（**Artifacts** の `slides`）からダウンロードできます。
GitHub Pages を有効にしている場合は，`ta` ブランチへの push で Pages にも公開されます（下の「GitHub Pages」）。

手元で発表するときは，Node.js（20 以上）を入れて次を実行します。

```sh
cd slides
npm ci                 # package-lock.json のとおりに入れる（初回だけ）
npm run dev            # http://localhost:3030 で発表する（P キーで発表者ビュー，ノートが見える）
```

## 書き出す

```sh
npm run build          # dist/debugger-basics/ に HTML（静的なサイト）
npm run export         # dist/debugger-basics.pdf（PDF の書き出しには Chromium が要る: npx playwright install chromium）
```

- PDF は，クリックで順に表示する部分の最後の状態だけを書き出します。1 クリックずつ別のページにするときは `npx slidev export debugger-basics.md --with-clicks` を使います。
- `npx slidev export debugger-basics.md --format pptx` で PowerPoint にも書き出せますが，各スライドは画像になるので，文言は PowerPoint では直せません。

## 追加・修正するとき

- スライドは 1 本 1 ファイル（`<名前>.md`）で，`package.json` の `scripts` と `.github/workflows/slides.yml` の一覧に加えます。
- 前提にする操作・文法は，その回までに授業で扱ったものにし，未習のものは発表者ノートか「（授業では未習）」で断ります（[CONTRIBUTING の「説明用スライド」](../CONTRIBUTING.md#説明用スライドslides)）。
- 依存パッケージは `package-lock.json` で固定しています。更新は授業の前にまとめて `npm update` し，`npm run build` と `npm run export` が通ることを確かめてから commit します。`npm audit` の警告の多くは，書き出しに使う開発用の部品のもので，公開する HTML・PDF には関係しません。

## GitHub Pages

公開リポジトリなら，リポジトリの **Settings > Pages** の **Source** を **GitHub Actions** にすると，`ta` ブランチへの push のたびに `https://<ユーザー名>.github.io/<リポジトリ名>/` にスライドの一覧が公開されます。
**Settings > Environments > github-pages** の **Deployment branches** に `ta` を加えておく必要があります（既定では既定のブランチ `main` からしか公開できません）。公開されたページは誰でも見られます。
