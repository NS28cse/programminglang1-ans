# CLAUDE.md

プログラミング言語I・ソフトウェア演習I（C 言語）の TA 用解答リポジトリの `ta` ブランチ（入口は [TA.md](TA.md)）。
保守はこのブランチで行う。`main` は解答と解説だけ，`ta-results` は CI が作るテストの実行結果，`practice` は `tools/make_practice.py` で `main` から作る練習用の生成物（どれも直接編集しない。`main` へは `tools/export_main.py` で反映する）。
`slides` は説明用スライド（実務のテーマごとに 1 つ）だけの別のブランチで，`ta` とは別に保守する（規約は `slides` の README.md）。
TA の仕事は学生に 1 対 1 で教えることだけなので，指導資料とスライドは 1 対 1 で使う形にする（全員への説明・発表を前提にしない）。

- 規約: [CONTRIBUTING.md](CONTRIBUTING.md)（ブランチ，フォルダ構成，コード規約，テスト形式，README の構成と書き方，実務の手引きとデバッグの題材の規則，仕上げ，CI）
- 評価（解答）: [softprac-grader](.claude/agents/softprac-grader.md)（`weekNN/` を回ごとに採点する）
- 評価（指導資料）: [ta-material-reviewer](.claude/agents/ta-material-reviewer.md)（実務の手引き `ta-guide/`，デバッグの題材 `debugging/`，`slides` の説明用スライドを評価する）
- 授業資料: https://github.com/t-yokoga/softprac1 の `docs/exNN.md`（演習）と `docs/lecNN.md`（講義）

解答を追加・修正したら，その回をビルド・テストし（`-DSOFTPRAC_WEEKS=weekNN`），
デバッグの題材なら `-DSOFTPRAC_WEEKS=debugging` でビルド・テストする。
CONTRIBUTING の[「仕上げ」](CONTRIBUTING.md#仕上げ)を実行してから commit する。
解答は softprac-grader，指導資料は ta-material-reviewer で評価して指摘を直し，
push 後は CI の全ジョブの成功を確かめる（作業ブランチの CI は `ta` への PR で動く）。評価エージェントは並行して動くので，worktree を作ったり消したりさせない。
各回の README は `main` と共通なので，テスト名・テスト数・TA 用の資料・IDE の設定ファイルに触れない（CONTRIBUTING の「読者に向けた書き方」）。
解答・解説を変えたら，`ta` へマージする前に CONTRIBUTING の[「ブランチ」](CONTRIBUTING.md#ブランチ)の 1〜4 の順で `main` に反映し，`practice` を作り直し，作業ブランチに `origin/main` をマージする。
