# 第1回 課題4 Version
# 本体は手順3 で書き換えた最終版（Version B）。手順1 の最初の版（Version A）も置き換えでビルドしてテストする
softprac_add_program(Version version.c)

softprac_add_variant(Version version.c version_a [[printf("Version B\n")]] [[printf("Version A\n")]])
