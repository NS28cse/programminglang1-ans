# CLAUDE.md

プログラミング言語I・ソフトウェア演習I（C 言語）の TA 用解答リポジトリ。

- 規約: [CONTRIBUTING.md](CONTRIBUTING.md)（フォルダ構成，コード規約，テスト形式，README の構成と書き方，CI）
- 評価: [.claude/agents/softprac-grader.md](.claude/agents/softprac-grader.md)（回ごとの採点エージェント）
- 授業資料: https://github.com/t-yokoga/softprac1 の `docs/exNN.md`（演習）と `docs/lecNN.md`（講義）

解答を追加・修正したら，その回をビルド・テストし，`python3 tools/normalize_sources.py`・
`python3 tools/gen_launch_vs.py`・`python3 tools/gen_readme_index.py` を実行してから commit する。
softprac-grader で採点して指摘を直し，push 後は CI の全ジョブの成功を確かめる。
