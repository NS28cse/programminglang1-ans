# CLAUDE.md

プログラミング言語I・ソフトウェア演習I（C 言語）の TA 用解答リポジトリ。

- 規約: [CONTRIBUTING.md](CONTRIBUTING.md)（フォルダ構成，コード規約，テスト形式，README の構成と書き方，実務の手引きとデバッグの題材の規則，仕上げ，CI）
- 評価（解答）: [softprac-grader](.claude/agents/softprac-grader.md)（`weekNN/` を回ごとに採点する）
- 評価（指導資料）: [ta-material-reviewer](.claude/agents/ta-material-reviewer.md)（実務の手引き `ta-guide/` とデバッグの題材 `debugging/` を評価する）
- 授業資料: https://github.com/t-yokoga/softprac1 の `docs/exNN.md`（演習）と `docs/lecNN.md`（講義）

解答を追加・修正したら，その回をビルド・テストし（`-DSOFTPRAC_WEEKS=weekNN`），
デバッグの題材なら `-DSOFTPRAC_WEEKS=debugging` でビルド・テストする。
CONTRIBUTING の[「仕上げ」](CONTRIBUTING.md#仕上げ)を実行してから commit する。
解答は softprac-grader，実務の手引き・デバッグの題材は ta-material-reviewer で評価して指摘を直し，
push 後は CI の全ジョブの成功を確かめる。
