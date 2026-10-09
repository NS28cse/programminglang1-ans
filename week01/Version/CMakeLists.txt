# 第1回 課題4 Version
# 本体は手順3 の後の内容（Version B）。手順1 の最初の版（Version A）もビルドしてテストする
# （先頭コメントの 1〜3 行目も「手順1 の最初の版」の説明に置き換える）
softprac_add_program(Version version.c)

softprac_add_variant(Version version.c version_a
  [=[// 第1回 課題4　ソースファイルと実行ファイル（Version / version.c）
// 手順3 の後の内容で，"Version B" を表示する（手順1 では "Version A" を表示する）。
// 保存だけでは Version.exe は変わらず，再ビルド後に Version B と表示される。]=]
  [=[// 第1回 課題4　ソースファイルと実行ファイル（Version / version.c，手順1 の最初の版）
// 手順3 で "Version B" に変更する前の版。"Version A" を表示する。
// 手順2 の最初のビルドで，Version.exe はこの版から作られる。]=]
  [=[    printf("Version B\n");]=]
  [=[    printf("Version A\n");]=])
