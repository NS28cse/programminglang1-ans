# テストの実行結果

`ta` ブランチのすべてのテストケースを実行した，実際の出力です（`python3 tools/collect_results.py` が作る。手で直さない）。

| 項目 | 値 |
| --- | --- |
| 実行した日時（UTC） | 2026-10-23 13:37 |
| `ta` のコミット | `172e3dde459bbf4ba9d189803ae98e8a83d12a30` |
| OS | Linux x86_64（Linux-6.17.0-1022-azure-x86_64-with-glibc2.39） |
| コンパイラ | GNU 13.3.0（`-std=c17 -Wall -Wextra -Wpedantic`，Debug） |
| CMake | cmake version 3.31.6 |

## 見方

- `results/` は，期待値（各プロジェクトの `tests/`・`variants/tests/`）と同じ形のフォルダです。`<ケース>.out` が標準出力，`.err` が標準エラー出力（出たときだけ），`.code` が終了コード（0 以外のときだけ），`<ケース>.files/` が実行で作られた・書き換えられたファイルです。
- 入力（`<ケース>.in`）と引数（`<ケース>.args`）は，期待値と同じフォルダ（`ta` の `weekNN/<プロジェクト>/tests/`）にあります。
- テストは環境で変わる出力（アドレスなど）を含まないので，Windows（MSVC）でも同じ出力になります（`ta` の CI で確かめています）。
- 学生の出力と比べるときは，学生のプログラムに同じ入力・引数を与えて出力をファイルに保存し，`diff`（Windows は `fc`）で比べます。

```sh
# 例: 第7回 Echo の two_lines を学生のプログラムで試して比べる（リポジトリのルートで実行する）
./student < week07/Echo/tests/two_lines.in > student.out
diff student.out results/week07/Echo/tests/two_lines.out
# 期待値と実際の出力をまとめて比べる（入力・引数のファイルは除く。Only in は片方にだけあるファイル
# ＝期待値で固定していない標準エラー出力など）
diff -r -x '*.in' -x '*.args' -x '*.setup' week07/Echo/tests results/week07/Echo/tests
```

## まとめ

| 回 | テスト数 | 一致 | 不一致 |
| --- | ---: | ---: | ---: |
| [week01](#week01) | 11 | 11 | 0 |
| [week02](#week02) | 24 | 24 | 0 |
| [week03](#week03) | 43 | 43 | 0 |
| [week04](#week04) | 141 | 141 | 0 |
| [week05](#week05) | 50 | 50 | 0 |
| [week06](#week06) | 40 | 40 | 0 |
| [week07](#week07) | 119 | 119 | 0 |
| [week08](#week08) | 50 | 50 | 0 |
| [week09](#week09) | 50 | 50 | 0 |
| [week10](#week10) | 191 | 191 | 0 |
| [week11](#week11) | 49 | 49 | 0 |
| [week12](#week12) | 52 | 52 | 0 |
| [week13](#week13) | 75 | 75 | 0 |
| [week14](#week14) | 65 | 65 | 0 |
| [debugging](#debugging) | 47 | 47 | 0 |
| **合計** | **1007** | **1007** | **0** |

## week01

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `Broken/basic` | 一致 | [.out](week01/Broken/tests/basic.out) | [.out](../week01/Broken/tests/basic.out) |
| `House/basic` | 一致 | [.out](week01/House/tests/basic.out) | [.out](../week01/House/tests/basic.out) |
| `House/variant_single_backslash` | 一致 | [.out](week01/House/variants/tests/single_backslash.out) | [.out](../week01/House/variants/tests/single_backslash.out) |
| `Message/basic` | 一致 | [.out](week01/Message/tests/basic.out) | [.out](../week01/Message/tests/basic.out) |
| `Message/variant_backslash_n_only` | 一致 | [.out](week01/Message/variants/tests/backslash_n_only.out) | [.out](../week01/Message/variants/tests/backslash_n_only.out) |
| `Message/variant_blank_line_in_first` | 一致 | [.out](week01/Message/variants/tests/blank_line_in_first.out) | [.out](../week01/Message/variants/tests/blank_line_in_first.out) |
| `Version/basic` | 一致 | [.out](week01/Version/tests/basic.out) | [.out](../week01/Version/tests/basic.out) |
| `Version/variant_version_a` | 一致 | [.out](week01/Version/variants/tests/version_a.out) | [.out](../week01/Version/variants/tests/version_a.out) |
| `Welcome/basic` | 一致 | [.out](week01/Welcome/tests/basic.out) | [.out](../week01/Welcome/tests/basic.out) |
| `Welcome/variant_missing_newline` | 一致 | [.out](week01/Welcome/variants/tests/missing_newline.out) | [.out](../week01/Welcome/variants/tests/missing_newline.out) |
| `Welcome/variant_one_printf` | 一致 | [.out](week01/Welcome/variants/tests/one_printf.out) | [.out](../week01/Welcome/variants/tests/one_printf.out) |

## week02

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `Exchange/basic` | 一致 | [.out](week02/Exchange/tests/basic.out) | [.out](../week02/Exchange/tests/basic.out) |
| `Exchange/variant_a_5_b_5` | 一致 | [.out](week02/Exchange/variants/tests/a_5_b_5.out) | [.out](../week02/Exchange/variants/tests/a_5_b_5.out) |
| `Exchange/variant_a_m3_b_8` | 一致 | [.out](week02/Exchange/variants/tests/a_m3_b_8.out) | [.out](../week02/Exchange/variants/tests/a_m3_b_8.out) |
| `Exchange/variant_sum_swap` | 一致 | [.out](week02/Exchange/variants/tests/sum_swap.out) | [.out](../week02/Exchange/variants/tests/sum_swap.out) |
| `Exchange/variant_sum_swap_a_5_b_5` | 一致 | [.out](week02/Exchange/variants/tests/sum_swap_a_5_b_5.out) | [.out](../week02/Exchange/variants/tests/sum_swap_a_5_b_5.out) |
| `Exchange/variant_sum_swap_a_m3_b_8` | 一致 | [.out](week02/Exchange/variants/tests/sum_swap_a_m3_b_8.out) | [.out](../week02/Exchange/variants/tests/sum_swap_a_m3_b_8.out) |
| `Exchange/variant_two_statements` | 一致 | [.out](week02/Exchange/variants/tests/two_statements.out) | [.out](../week02/Exchange/variants/tests/two_statements.out) |
| `Exchange/variant_two_statements_a_5_b_5` | 一致 | [.out](week02/Exchange/variants/tests/two_statements_a_5_b_5.out) | [.out](../week02/Exchange/variants/tests/two_statements_a_5_b_5.out) |
| `Exchange/variant_two_statements_a_m3_b_8` | 一致 | [.out](week02/Exchange/variants/tests/two_statements_a_m3_b_8.out) | [.out](../week02/Exchange/variants/tests/two_statements_a_m3_b_8.out) |
| `Exchange/variant_wrong_order` | 一致 | [.out](week02/Exchange/variants/tests/wrong_order.out) | [.out](../week02/Exchange/variants/tests/wrong_order.out) |
| `Profile/basic` | 一致 | [.out](week02/Profile/tests/basic.out) | [.out](../week02/Profile/tests/basic.out) |
| `Profile/variant_count_0` | 一致 | [.out](week02/Profile/variants/tests/count_0.out) | [.out](../week02/Profile/variants/tests/count_0.out) |
| `Profile/variant_int_total` | 一致 | [.out](week02/Profile/variants/tests/int_total.out) | [.out](../week02/Profile/variants/tests/int_total.out) |
| `Profile/variant_price_f` | 一致 | [.out](week02/Profile/variants/tests/price_f.out) | [.out](../week02/Profile/variants/tests/price_f.out) |
| `Profile/variant_price_f_count_0` | 一致 | [.out](week02/Profile/variants/tests/price_f_count_0.out) | [.out](../week02/Profile/variants/tests/price_f_count_0.out) |
| `Rectangle/basic` | 一致 | [.out](week02/Rectangle/tests/basic.out) | [.out](../week02/Rectangle/tests/basic.out) |
| `Rectangle/variant_width_0` | 一致 | [.out](week02/Rectangle/variants/tests/width_0.out) | [.out](../week02/Rectangle/variants/tests/width_0.out) |
| `Rectangle/variant_width_1` | 一致 | [.out](week02/Rectangle/variants/tests/width_1.out) | [.out](../week02/Rectangle/variants/tests/width_1.out) |
| `Temperature/basic` | 一致 | [.out](week02/Temperature/tests/basic.out) | [.out](../week02/Temperature/tests/basic.out) |
| `Temperature/variant_celsius_0` | 一致 | [.out](week02/Temperature/variants/tests/celsius_0.out) | [.out](../week02/Temperature/variants/tests/celsius_0.out) |
| `Temperature/variant_celsius_100` | 一致 | [.out](week02/Temperature/variants/tests/celsius_100.out) | [.out](../week02/Temperature/variants/tests/celsius_100.out) |
| `Temperature/variant_celsius_m40` | 一致 | [.out](week02/Temperature/variants/tests/celsius_m40.out) | [.out](../week02/Temperature/variants/tests/celsius_m40.out) |
| `Temperature/variant_change_after` | 一致 | [.out](week02/Temperature/variants/tests/change_after.out) | [.out](../week02/Temperature/variants/tests/change_after.out) |
| `Temperature/variant_int_division` | 一致 | [.out](week02/Temperature/variants/tests/int_division.out) | [.out](../week02/Temperature/variants/tests/int_division.out) |

## week03

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `Conditions/basic` | 一致 | [.out](week03/Conditions/tests/basic.out) | [.out](../week03/Conditions/tests/basic.out) |
| `Conditions/variant_chained_101` | 一致 | [.out](week03/Conditions/variants/tests/chained_101.out) | [.out](../week03/Conditions/variants/tests/chained_101.out) |
| `Conditions/variant_chained_75` | 一致 | [.out](week03/Conditions/variants/tests/chained_75.out) | [.out](../week03/Conditions/variants/tests/chained_75.out) |
| `Conditions/variant_chained_minus1` | 一致 | [.out](week03/Conditions/variants/tests/chained_minus1.out) | [.out](../week03/Conditions/variants/tests/chained_minus1.out) |
| `Conditions/variant_d_3` | 一致 | [.out](week03/Conditions/variants/tests/d_3.out) | [.out](../week03/Conditions/variants/tests/d_3.out) |
| `Conditions/variant_d_6` | 一致 | [.out](week03/Conditions/variants/tests/d_6.out) | [.out](../week03/Conditions/variants/tests/d_6.out) |
| `Conditions/variant_score_0` | 一致 | [.out](week03/Conditions/variants/tests/score_0.out) | [.out](../week03/Conditions/variants/tests/score_0.out) |
| `Conditions/variant_score_100` | 一致 | [.out](week03/Conditions/variants/tests/score_100.out) | [.out](../week03/Conditions/variants/tests/score_100.out) |
| `Conditions/variant_score_101` | 一致 | [.out](week03/Conditions/variants/tests/score_101.out) | [.out](../week03/Conditions/variants/tests/score_101.out) |
| `Conditions/variant_score_minus1` | 一致 | [.out](week03/Conditions/variants/tests/score_minus1.out) | [.out](../week03/Conditions/variants/tests/score_minus1.out) |
| `Flags/basic` | 一致 | [.out](week03/Flags/tests/basic.out) | [.out](../week03/Flags/tests/basic.out) |
| `Flags/variant_and_vs_logical_and` | 一致 | [.out](week03/Flags/variants/tests/and_vs_logical_and.out) | [.out](../week03/Flags/variants/tests/and_vs_logical_and.out) |
| `Flags/variant_or_vs_add` | 一致 | [.out](week03/Flags/variants/tests/or_vs_add.out) | [.out](../week03/Flags/variants/tests/or_vs_add.out) |
| `Flags/variant_set_twice_add` | 一致 | [.out](week03/Flags/variants/tests/set_twice_add.out) | [.out](../week03/Flags/variants/tests/set_twice_add.out) |
| `Flags/variant_set_twice_or` | 一致 | [.out](week03/Flags/variants/tests/set_twice_or.out) | [.out](../week03/Flags/variants/tests/set_twice_or.out) |
| `Flags/variant_start_0` | 一致 | [.out](week03/Flags/variants/tests/start_0.out) | [.out](../week03/Flags/variants/tests/start_0.out) |
| `Flags/variant_start_7` | 一致 | [.out](week03/Flags/variants/tests/start_7.out) | [.out](../week03/Flags/variants/tests/start_7.out) |
| `Flags/variant_wrong_clear_not` | 一致 | [.out](week03/Flags/variants/tests/wrong_clear_not.out) | [.out](../week03/Flags/variants/tests/wrong_clear_not.out) |
| `Flags/variant_wrong_clear_xor_start_0` | 一致 | [.out](week03/Flags/variants/tests/wrong_clear_xor_start_0.out) | [.out](../week03/Flags/variants/tests/wrong_clear_xor_start_0.out) |
| `Leap/basic` | 一致 | [.out](week03/Leap/tests/basic.out) | [.out](../week03/Leap/tests/basic.out) |
| `Leap/variant_one_expr_1900` | 一致 | [.out](week03/Leap/variants/tests/one_expr_1900.out) | [.out](../week03/Leap/variants/tests/one_expr_1900.out) |
| `Leap/variant_one_expr_2000` | 一致 | [.out](week03/Leap/variants/tests/one_expr_2000.out) | [.out](../week03/Leap/variants/tests/one_expr_2000.out) |
| `Leap/variant_one_expr_2024` | 一致 | [.out](week03/Leap/variants/tests/one_expr_2024.out) | [.out](../week03/Leap/variants/tests/one_expr_2024.out) |
| `Leap/variant_one_expr_2025` | 一致 | [.out](week03/Leap/variants/tests/one_expr_2025.out) | [.out](../week03/Leap/variants/tests/one_expr_2025.out) |
| `Leap/variant_wrong_no_100_rule_1900` | 一致 | [.out](week03/Leap/variants/tests/wrong_no_100_rule_1900.out) | [.out](../week03/Leap/variants/tests/wrong_no_100_rule_1900.out) |
| `Leap/variant_year_1900` | 一致 | [.out](week03/Leap/variants/tests/year_1900.out) | [.out](../week03/Leap/variants/tests/year_1900.out) |
| `Leap/variant_year_2024` | 一致 | [.out](week03/Leap/variants/tests/year_2024.out) | [.out](../week03/Leap/variants/tests/year_2024.out) |
| `Leap/variant_year_2025` | 一致 | [.out](week03/Leap/variants/tests/year_2025.out) | [.out](../week03/Leap/variants/tests/year_2025.out) |
| `TimeParts/basic` | 一致 | [.out](week03/TimeParts/tests/basic.out) | [.out](../week03/TimeParts/tests/basic.out) |
| `TimeParts/variant_division_types` | 一致 | [.out](week03/TimeParts/variants/tests/division_types.out) | [.out](../week03/TimeParts/variants/tests/division_types.out) |
| `TimeParts/variant_int_division_3671` | 一致 | [.out](week03/TimeParts/variants/tests/int_division_3671.out) | [.out](../week03/TimeParts/variants/tests/int_division_3671.out) |
| `TimeParts/variant_int_division_61` | 一致 | [.out](week03/TimeParts/variants/tests/int_division_61.out) | [.out](../week03/TimeParts/variants/tests/int_division_61.out) |
| `TimeParts/variant_seconds_0` | 一致 | [.out](week03/TimeParts/variants/tests/seconds_0.out) | [.out](../week03/TimeParts/variants/tests/seconds_0.out) |
| `TimeParts/variant_seconds_10000` | 一致 | [.out](week03/TimeParts/variants/tests/seconds_10000.out) | [.out](../week03/TimeParts/variants/tests/seconds_10000.out) |
| `TimeParts/variant_seconds_59` | 一致 | [.out](week03/TimeParts/variants/tests/seconds_59.out) | [.out](../week03/TimeParts/variants/tests/seconds_59.out) |
| `TimeParts/variant_seconds_60` | 一致 | [.out](week03/TimeParts/variants/tests/seconds_60.out) | [.out](../week03/TimeParts/variants/tests/seconds_60.out) |
| `TimeParts/variant_seconds_61` | 一致 | [.out](week03/TimeParts/variants/tests/seconds_61.out) | [.out](../week03/TimeParts/variants/tests/seconds_61.out) |
| `Update/basic` | 一致 | [.out](week03/Update/tests/basic.out) | [.out](../week03/Update/tests/basic.out) |
| `Update/variant_plain_assignment` | 一致 | [.out](week03/Update/variants/tests/plain_assignment.out) | [.out](../week03/Update/variants/tests/plain_assignment.out) |
| `Update/variant_swapped_order` | 一致 | [.out](week03/Update/variants/tests/swapped_order.out) | [.out](../week03/Update/variants/tests/swapped_order.out) |
| `Update/variant_wrong_one_line` | 一致 | [.out](week03/Update/variants/tests/wrong_one_line.out) | [.out](../week03/Update/variants/tests/wrong_one_line.out) |
| `Update/variant_x_0` | 一致 | [.out](week03/Update/variants/tests/x_0.out) | [.out](../week03/Update/variants/tests/x_0.out) |
| `Update/variant_x_minus2` | 一致 | [.out](week03/Update/variants/tests/x_minus2.out) | [.out](../week03/Update/variants/tests/x_minus2.out) |

## week04

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `EvenSum/n_10` | 一致 | [.out](week04/EvenSum/tests/n_10.out) | [.out](../week04/EvenSum/tests/n_10.out) |
| `EvenSum/variant_count_n_0` | 一致 | [.out](week04/EvenSum/variants/tests/count_n_0.out) | [.out](../week04/EvenSum/variants/tests/count_n_0.out) |
| `EvenSum/variant_count_n_1` | 一致 | [.out](week04/EvenSum/variants/tests/count_n_1.out) | [.out](../week04/EvenSum/variants/tests/count_n_1.out) |
| `EvenSum/variant_count_n_10` | 一致 | [.out](week04/EvenSum/variants/tests/count_n_10.out) | [.out](../week04/EvenSum/variants/tests/count_n_10.out) |
| `EvenSum/variant_count_n_100` | 一致 | [.out](week04/EvenSum/variants/tests/count_n_100.out) | [.out](../week04/EvenSum/variants/tests/count_n_100.out) |
| `EvenSum/variant_count_n_2` | 一致 | [.out](week04/EvenSum/variants/tests/count_n_2.out) | [.out](../week04/EvenSum/variants/tests/count_n_2.out) |
| `EvenSum/variant_count_n_4` | 一致 | [.out](week04/EvenSum/variants/tests/count_n_4.out) | [.out](../week04/EvenSum/variants/tests/count_n_4.out) |
| `EvenSum/variant_count_step2_n_0` | 一致 | [.out](week04/EvenSum/variants/tests/count_step2_n_0.out) | [.out](../week04/EvenSum/variants/tests/count_step2_n_0.out) |
| `EvenSum/variant_count_step2_n_1` | 一致 | [.out](week04/EvenSum/variants/tests/count_step2_n_1.out) | [.out](../week04/EvenSum/variants/tests/count_step2_n_1.out) |
| `EvenSum/variant_count_step2_n_10` | 一致 | [.out](week04/EvenSum/variants/tests/count_step2_n_10.out) | [.out](../week04/EvenSum/variants/tests/count_step2_n_10.out) |
| `EvenSum/variant_count_step2_n_100` | 一致 | [.out](week04/EvenSum/variants/tests/count_step2_n_100.out) | [.out](../week04/EvenSum/variants/tests/count_step2_n_100.out) |
| `EvenSum/variant_count_step2_n_2` | 一致 | [.out](week04/EvenSum/variants/tests/count_step2_n_2.out) | [.out](../week04/EvenSum/variants/tests/count_step2_n_2.out) |
| `EvenSum/variant_count_step2_n_4` | 一致 | [.out](week04/EvenSum/variants/tests/count_step2_n_4.out) | [.out](../week04/EvenSum/variants/tests/count_step2_n_4.out) |
| `EvenSum/variant_count_three_times` | 一致 | [.out](week04/EvenSum/variants/tests/count_three_times.out) | [.out](../week04/EvenSum/variants/tests/count_three_times.out) |
| `EvenSum/variant_early_increment_n_1` | 一致 | [.out](week04/EvenSum/variants/tests/early_increment_n_1.out) | [.out](../week04/EvenSum/variants/tests/early_increment_n_1.out) |
| `EvenSum/variant_early_increment_n_10` | 一致 | [.out](week04/EvenSum/variants/tests/early_increment_n_10.out) | [.out](../week04/EvenSum/variants/tests/early_increment_n_10.out) |
| `EvenSum/variant_early_increment_n_9` | 一致 | [.out](week04/EvenSum/variants/tests/early_increment_n_9.out) | [.out](../week04/EvenSum/variants/tests/early_increment_n_9.out) |
| `EvenSum/variant_for_n_0` | 一致 | [.out](week04/EvenSum/variants/tests/for_n_0.out) | [.out](../week04/EvenSum/variants/tests/for_n_0.out) |
| `EvenSum/variant_for_n_1` | 一致 | [.out](week04/EvenSum/variants/tests/for_n_1.out) | [.out](../week04/EvenSum/variants/tests/for_n_1.out) |
| `EvenSum/variant_for_n_100` | 一致 | [.out](week04/EvenSum/variants/tests/for_n_100.out) | [.out](../week04/EvenSum/variants/tests/for_n_100.out) |
| `EvenSum/variant_for_n_2` | 一致 | [.out](week04/EvenSum/variants/tests/for_n_2.out) | [.out](../week04/EvenSum/variants/tests/for_n_2.out) |
| `EvenSum/variant_for_n_4` | 一致 | [.out](week04/EvenSum/variants/tests/for_n_4.out) | [.out](../week04/EvenSum/variants/tests/for_n_4.out) |
| `EvenSum/variant_formula_n_0` | 一致 | [.out](week04/EvenSum/variants/tests/formula_n_0.out) | [.out](../week04/EvenSum/variants/tests/formula_n_0.out) |
| `EvenSum/variant_formula_n_1` | 一致 | [.out](week04/EvenSum/variants/tests/formula_n_1.out) | [.out](../week04/EvenSum/variants/tests/formula_n_1.out) |
| `EvenSum/variant_formula_n_10` | 一致 | [.out](week04/EvenSum/variants/tests/formula_n_10.out) | [.out](../week04/EvenSum/variants/tests/formula_n_10.out) |
| `EvenSum/variant_formula_n_100` | 一致 | [.out](week04/EvenSum/variants/tests/formula_n_100.out) | [.out](../week04/EvenSum/variants/tests/formula_n_100.out) |
| `EvenSum/variant_formula_n_2` | 一致 | [.out](week04/EvenSum/variants/tests/formula_n_2.out) | [.out](../week04/EvenSum/variants/tests/formula_n_2.out) |
| `EvenSum/variant_formula_n_4` | 一致 | [.out](week04/EvenSum/variants/tests/formula_n_4.out) | [.out](../week04/EvenSum/variants/tests/formula_n_4.out) |
| `EvenSum/variant_lt_n_10` | 一致 | [.out](week04/EvenSum/variants/tests/lt_n_10.out) | [.out](../week04/EvenSum/variants/tests/lt_n_10.out) |
| `EvenSum/variant_lt_n_2` | 一致 | [.out](week04/EvenSum/variants/tests/lt_n_2.out) | [.out](../week04/EvenSum/variants/tests/lt_n_2.out) |
| `EvenSum/variant_reset_in_body_n_10` | 一致 | [.out](week04/EvenSum/variants/tests/reset_in_body_n_10.out) | [.out](../week04/EvenSum/variants/tests/reset_in_body_n_10.out) |
| `EvenSum/variant_reset_in_body_n_4` | 一致 | [.out](week04/EvenSum/variants/tests/reset_in_body_n_4.out) | [.out](../week04/EvenSum/variants/tests/reset_in_body_n_4.out) |
| `EvenSum/variant_reset_in_body_n_9` | 一致 | [.out](week04/EvenSum/variants/tests/reset_in_body_n_9.out) | [.out](../week04/EvenSum/variants/tests/reset_in_body_n_9.out) |
| `EvenSum/variant_step2_n_0` | 一致 | [.out](week04/EvenSum/variants/tests/step2_n_0.out) | [.out](../week04/EvenSum/variants/tests/step2_n_0.out) |
| `EvenSum/variant_step2_n_1` | 一致 | [.out](week04/EvenSum/variants/tests/step2_n_1.out) | [.out](../week04/EvenSum/variants/tests/step2_n_1.out) |
| `EvenSum/variant_step2_n_10` | 一致 | [.out](week04/EvenSum/variants/tests/step2_n_10.out) | [.out](../week04/EvenSum/variants/tests/step2_n_10.out) |
| `EvenSum/variant_step2_n_100` | 一致 | [.out](week04/EvenSum/variants/tests/step2_n_100.out) | [.out](../week04/EvenSum/variants/tests/step2_n_100.out) |
| `EvenSum/variant_step2_n_2` | 一致 | [.out](week04/EvenSum/variants/tests/step2_n_2.out) | [.out](../week04/EvenSum/variants/tests/step2_n_2.out) |
| `EvenSum/variant_three_times` | 一致 | [.out](week04/EvenSum/variants/tests/three_times.out) | [.out](../week04/EvenSum/variants/tests/three_times.out) |
| `EvenSum/variant_while_i_after_n_0` | 一致 | [.out](week04/EvenSum/variants/tests/while_i_after_n_0.out) | [.out](../week04/EvenSum/variants/tests/while_i_after_n_0.out) |
| `EvenSum/variant_while_i_after_n_10` | 一致 | [.out](week04/EvenSum/variants/tests/while_i_after_n_10.out) | [.out](../week04/EvenSum/variants/tests/while_i_after_n_10.out) |
| `EvenSum/variant_while_n_0` | 一致 | [.out](week04/EvenSum/variants/tests/while_n_0.out) | [.out](../week04/EvenSum/variants/tests/while_n_0.out) |
| `EvenSum/variant_while_n_1` | 一致 | [.out](week04/EvenSum/variants/tests/while_n_1.out) | [.out](../week04/EvenSum/variants/tests/while_n_1.out) |
| `EvenSum/variant_while_n_10` | 一致 | [.out](week04/EvenSum/variants/tests/while_n_10.out) | [.out](../week04/EvenSum/variants/tests/while_n_10.out) |
| `EvenSum/variant_while_n_100` | 一致 | [.out](week04/EvenSum/variants/tests/while_n_100.out) | [.out](../week04/EvenSum/variants/tests/while_n_100.out) |
| `EvenSum/variant_while_n_2` | 一致 | [.out](week04/EvenSum/variants/tests/while_n_2.out) | [.out](../week04/EvenSum/variants/tests/while_n_2.out) |
| `Fee/age_17` | 一致 | [.out](week04/Fee/tests/age_17.out) | [.out](../week04/Fee/tests/age_17.out) |
| `Fee/variant_age_0` | 一致 | [.out](week04/Fee/variants/tests/age_0.out) | [.out](../week04/Fee/variants/tests/age_0.out) |
| `Fee/variant_age_18` | 一致 | [.out](week04/Fee/variants/tests/age_18.out) | [.out](../week04/Fee/variants/tests/age_18.out) |
| `Fee/variant_age_5` | 一致 | [.out](week04/Fee/variants/tests/age_5.out) | [.out](../week04/Fee/variants/tests/age_5.out) |
| `Fee/variant_age_6` | 一致 | [.out](week04/Fee/variants/tests/age_6.out) | [.out](../week04/Fee/variants/tests/age_6.out) |
| `Fee/variant_age_m1` | 一致 | [.out](week04/Fee/variants/tests/age_m1.out) | [.out](../week04/Fee/variants/tests/age_m1.out) |
| `Fee/variant_flag_minus1` | 一致 | [.out](week04/Fee/variants/tests/flag_minus1.out) | [.out](../week04/Fee/variants/tests/flag_minus1.out) |
| `Fee/variant_if_three` | 一致 | [.out](week04/Fee/variants/tests/if_three.out) | [.out](../week04/Fee/variants/tests/if_three.out) |
| `Fee/variant_lt_17_age_17` | 一致 | [.out](week04/Fee/variants/tests/lt_17_age_17.out) | [.out](../week04/Fee/variants/tests/lt_17_age_17.out) |
| `Fee/variant_lt_5_age_5` | 一致 | [.out](week04/Fee/variants/tests/lt_5_age_5.out) | [.out](../week04/Fee/variants/tests/lt_5_age_5.out) |
| `Fee/variant_no_check_age_m1` | 一致 | [.out](week04/Fee/variants/tests/no_check_age_m1.out) | [.out](../week04/Fee/variants/tests/no_check_age_m1.out) |
| `Fee/variant_ranges_age_0` | 一致 | [.out](week04/Fee/variants/tests/ranges_age_0.out) | [.out](../week04/Fee/variants/tests/ranges_age_0.out) |
| `Fee/variant_ranges_age_17` | 一致 | [.out](week04/Fee/variants/tests/ranges_age_17.out) | [.out](../week04/Fee/variants/tests/ranges_age_17.out) |
| `Fee/variant_ranges_age_18` | 一致 | [.out](week04/Fee/variants/tests/ranges_age_18.out) | [.out](../week04/Fee/variants/tests/ranges_age_18.out) |
| `Fee/variant_ranges_age_5` | 一致 | [.out](week04/Fee/variants/tests/ranges_age_5.out) | [.out](../week04/Fee/variants/tests/ranges_age_5.out) |
| `Fee/variant_ranges_age_6` | 一致 | [.out](week04/Fee/variants/tests/ranges_age_6.out) | [.out](../week04/Fee/variants/tests/ranges_age_6.out) |
| `Fee/variant_ranges_age_m1` | 一致 | [.out](week04/Fee/variants/tests/ranges_age_m1.out) | [.out](../week04/Fee/variants/tests/ranges_age_m1.out) |
| `Fee/variant_separate_if_age_0` | 一致 | [.out](week04/Fee/variants/tests/separate_if_age_0.out) | [.out](../week04/Fee/variants/tests/separate_if_age_0.out) |
| `Fee/variant_separate_if_age_17` | 一致 | [.out](week04/Fee/variants/tests/separate_if_age_17.out) | [.out](../week04/Fee/variants/tests/separate_if_age_17.out) |
| `Fee/variant_separate_if_age_18` | 一致 | [.out](week04/Fee/variants/tests/separate_if_age_18.out) | [.out](../week04/Fee/variants/tests/separate_if_age_18.out) |
| `Fee/variant_separate_if_age_5` | 一致 | [.out](week04/Fee/variants/tests/separate_if_age_5.out) | [.out](../week04/Fee/variants/tests/separate_if_age_5.out) |
| `Fee/variant_separate_if_age_6` | 一致 | [.out](week04/Fee/variants/tests/separate_if_age_6.out) | [.out](../week04/Fee/variants/tests/separate_if_age_6.out) |
| `Fee/variant_separate_if_age_m1` | 一致 | [.out](week04/Fee/variants/tests/separate_if_age_m1.out) | [.out](../week04/Fee/variants/tests/separate_if_age_m1.out) |
| `Fee/variant_swapped_age_0` | 一致 | [.out](week04/Fee/variants/tests/swapped_age_0.out) | [.out](../week04/Fee/variants/tests/swapped_age_0.out) |
| `Fee/variant_swapped_age_17` | 一致 | [.out](week04/Fee/variants/tests/swapped_age_17.out) | [.out](../week04/Fee/variants/tests/swapped_age_17.out) |
| `Fee/variant_swapped_age_18` | 一致 | [.out](week04/Fee/variants/tests/swapped_age_18.out) | [.out](../week04/Fee/variants/tests/swapped_age_18.out) |
| `Fee/variant_swapped_age_5` | 一致 | [.out](week04/Fee/variants/tests/swapped_age_5.out) | [.out](../week04/Fee/variants/tests/swapped_age_5.out) |
| `Fee/variant_swapped_age_6` | 一致 | [.out](week04/Fee/variants/tests/swapped_age_6.out) | [.out](../week04/Fee/variants/tests/swapped_age_6.out) |
| `Fee/variant_swapped_age_m1` | 一致 | [.out](week04/Fee/variants/tests/swapped_age_m1.out) | [.out](../week04/Fee/variants/tests/swapped_age_m1.out) |
| `Powers/limit_100` | 一致 | [.out](week04/Powers/tests/limit_100.out) | [.out](../week04/Powers/tests/limit_100.out) |
| `Powers/variant_count_do_while_limit_1` | 一致 | [.out](week04/Powers/variants/tests/count_do_while_limit_1.out) | [.out](../week04/Powers/variants/tests/count_do_while_limit_1.out) |
| `Powers/variant_count_do_while_limit_100` | 一致 | [.out](week04/Powers/variants/tests/count_do_while_limit_100.out) | [.out](../week04/Powers/variants/tests/count_do_while_limit_100.out) |
| `Powers/variant_count_do_while_limit_2` | 一致 | [.out](week04/Powers/variants/tests/count_do_while_limit_2.out) | [.out](../week04/Powers/variants/tests/count_do_while_limit_2.out) |
| `Powers/variant_count_do_while_limit_64` | 一致 | [.out](week04/Powers/variants/tests/count_do_while_limit_64.out) | [.out](../week04/Powers/variants/tests/count_do_while_limit_64.out) |
| `Powers/variant_count_do_while_limit_65` | 一致 | [.out](week04/Powers/variants/tests/count_do_while_limit_65.out) | [.out](../week04/Powers/variants/tests/count_do_while_limit_65.out) |
| `Powers/variant_count_for_limit_1` | 一致 | [.out](week04/Powers/variants/tests/count_for_limit_1.out) | [.out](../week04/Powers/variants/tests/count_for_limit_1.out) |
| `Powers/variant_count_for_limit_100` | 一致 | [.out](week04/Powers/variants/tests/count_for_limit_100.out) | [.out](../week04/Powers/variants/tests/count_for_limit_100.out) |
| `Powers/variant_count_for_limit_2` | 一致 | [.out](week04/Powers/variants/tests/count_for_limit_2.out) | [.out](../week04/Powers/variants/tests/count_for_limit_2.out) |
| `Powers/variant_count_for_limit_64` | 一致 | [.out](week04/Powers/variants/tests/count_for_limit_64.out) | [.out](../week04/Powers/variants/tests/count_for_limit_64.out) |
| `Powers/variant_count_for_limit_65` | 一致 | [.out](week04/Powers/variants/tests/count_for_limit_65.out) | [.out](../week04/Powers/variants/tests/count_for_limit_65.out) |
| `Powers/variant_count_while_limit_1` | 一致 | [.out](week04/Powers/variants/tests/count_while_limit_1.out) | [.out](../week04/Powers/variants/tests/count_while_limit_1.out) |
| `Powers/variant_count_while_limit_100` | 一致 | [.out](week04/Powers/variants/tests/count_while_limit_100.out) | [.out](../week04/Powers/variants/tests/count_while_limit_100.out) |
| `Powers/variant_count_while_limit_2` | 一致 | [.out](week04/Powers/variants/tests/count_while_limit_2.out) | [.out](../week04/Powers/variants/tests/count_while_limit_2.out) |
| `Powers/variant_count_while_limit_64` | 一致 | [.out](week04/Powers/variants/tests/count_while_limit_64.out) | [.out](../week04/Powers/variants/tests/count_while_limit_64.out) |
| `Powers/variant_count_while_limit_65` | 一致 | [.out](week04/Powers/variants/tests/count_while_limit_65.out) | [.out](../week04/Powers/variants/tests/count_while_limit_65.out) |
| `Powers/variant_do_while_limit_1` | 一致 | [.out](week04/Powers/variants/tests/do_while_limit_1.out) | [.out](../week04/Powers/variants/tests/do_while_limit_1.out) |
| `Powers/variant_do_while_limit_100` | 一致 | [.out](week04/Powers/variants/tests/do_while_limit_100.out) | [.out](../week04/Powers/variants/tests/do_while_limit_100.out) |
| `Powers/variant_do_while_limit_2` | 一致 | [.out](week04/Powers/variants/tests/do_while_limit_2.out) | [.out](../week04/Powers/variants/tests/do_while_limit_2.out) |
| `Powers/variant_do_while_limit_64` | 一致 | [.out](week04/Powers/variants/tests/do_while_limit_64.out) | [.out](../week04/Powers/variants/tests/do_while_limit_64.out) |
| `Powers/variant_do_while_limit_65` | 一致 | [.out](week04/Powers/variants/tests/do_while_limit_65.out) | [.out](../week04/Powers/variants/tests/do_while_limit_65.out) |
| `Powers/variant_for_limit_1` | 一致 | [.out](week04/Powers/variants/tests/for_limit_1.out) | [.out](../week04/Powers/variants/tests/for_limit_1.out) |
| `Powers/variant_for_limit_2` | 一致 | [.out](week04/Powers/variants/tests/for_limit_2.out) | [.out](../week04/Powers/variants/tests/for_limit_2.out) |
| `Powers/variant_for_limit_64` | 一致 | [.out](week04/Powers/variants/tests/for_limit_64.out) | [.out](../week04/Powers/variants/tests/for_limit_64.out) |
| `Powers/variant_for_limit_65` | 一致 | [.out](week04/Powers/variants/tests/for_limit_65.out) | [.out](../week04/Powers/variants/tests/for_limit_65.out) |
| `Powers/variant_le_limit_64` | 一致 | [.out](week04/Powers/variants/tests/le_limit_64.out) | [.out](../week04/Powers/variants/tests/le_limit_64.out) |
| `Powers/variant_while_limit_1` | 一致 | [.out](week04/Powers/variants/tests/while_limit_1.out) | [.out](../week04/Powers/variants/tests/while_limit_1.out) |
| `Powers/variant_while_limit_100` | 一致 | [.out](week04/Powers/variants/tests/while_limit_100.out) | [.out](../week04/Powers/variants/tests/while_limit_100.out) |
| `Powers/variant_while_limit_2` | 一致 | [.out](week04/Powers/variants/tests/while_limit_2.out) | [.out](../week04/Powers/variants/tests/while_limit_2.out) |
| `Powers/variant_while_limit_64` | 一致 | [.out](week04/Powers/variants/tests/while_limit_64.out) | [.out](../week04/Powers/variants/tests/while_limit_64.out) |
| `Powers/variant_while_limit_65` | 一致 | [.out](week04/Powers/variants/tests/while_limit_65.out) | [.out](../week04/Powers/variants/tests/while_limit_65.out) |
| `Table/basic` | 一致 | [.out](week04/Table/tests/basic.out) | [.out](../week04/Table/tests/basic.out) |
| `Table/variant_break_first_cols_4` | 一致 | [.out](week04/Table/variants/tests/break_first_cols_4.out) | [.out](../week04/Table/variants/tests/break_first_cols_4.out) |
| `Table/variant_col_not_reset` | 一致 | [.out](week04/Table/variants/tests/col_not_reset.out) | [.out](../week04/Table/variants/tests/col_not_reset.out) |
| `Table/variant_cols_4` | 一致 | [.out](week04/Table/variants/tests/cols_4.out) | [.out](../week04/Table/variants/tests/cols_4.out) |
| `Table/variant_cols_4_bound_only` | 一致 | [.out](week04/Table/variants/tests/cols_4_bound_only.out) | [.out](../week04/Table/variants/tests/cols_4_bound_only.out) |
| `Table/variant_count_cols_3` | 一致 | [.out](week04/Table/variants/tests/count_cols_3.out) | [.out](../week04/Table/variants/tests/count_cols_3.out) |
| `Table/variant_count_cols_4` | 一致 | [.out](week04/Table/variants/tests/count_cols_4.out) | [.out](../week04/Table/variants/tests/count_cols_4.out) |
| `Table/variant_first_col` | 一致 | [.out](week04/Table/variants/tests/first_col.out) | [.out](../week04/Table/variants/tests/first_col.out) |
| `Table/variant_first_col_cols_4` | 一致 | [.out](week04/Table/variants/tests/first_col_cols_4.out) | [.out](../week04/Table/variants/tests/first_col_cols_4.out) |
| `Table/variant_newline_after` | 一致 | [.out](week04/Table/variants/tests/newline_after.out) | [.out](../week04/Table/variants/tests/newline_after.out) |
| `Table/variant_newline_inner` | 一致 | [.out](week04/Table/variants/tests/newline_inner.out) | [.out](../week04/Table/variants/tests/newline_inner.out) |
| `Table/variant_pairs` | 一致 | [.out](week04/Table/variants/tests/pairs.out) | [.out](../week04/Table/variants/tests/pairs.out) |
| `YearGroup/variant_goto_done` | 一致 | [.out](week04/YearGroup/variants/tests/goto_done.out) | [.out](../week04/YearGroup/variants/tests/goto_done.out) |
| `YearGroup/variant_goto_to_break` | 一致 | [.out](week04/YearGroup/variants/tests/goto_to_break.out) | [.out](../week04/YearGroup/variants/tests/goto_to_break.out) |
| `YearGroup/variant_if_year_0` | 一致 | [.out](week04/YearGroup/variants/tests/if_year_0.out) | [.out](../week04/YearGroup/variants/tests/if_year_0.out) |
| `YearGroup/variant_if_year_1` | 一致 | [.out](week04/YearGroup/variants/tests/if_year_1.out) | [.out](../week04/YearGroup/variants/tests/if_year_1.out) |
| `YearGroup/variant_if_year_2` | 一致 | [.out](week04/YearGroup/variants/tests/if_year_2.out) | [.out](../week04/YearGroup/variants/tests/if_year_2.out) |
| `YearGroup/variant_if_year_3` | 一致 | [.out](week04/YearGroup/variants/tests/if_year_3.out) | [.out](../week04/YearGroup/variants/tests/if_year_3.out) |
| `YearGroup/variant_if_year_4` | 一致 | [.out](week04/YearGroup/variants/tests/if_year_4.out) | [.out](../week04/YearGroup/variants/tests/if_year_4.out) |
| `YearGroup/variant_if_year_5` | 一致 | [.out](week04/YearGroup/variants/tests/if_year_5.out) | [.out](../week04/YearGroup/variants/tests/if_year_5.out) |
| `YearGroup/variant_no_default_year_5` | 一致 | [.out](week04/YearGroup/variants/tests/no_default_year_5.out) | [.out](../week04/YearGroup/variants/tests/no_default_year_5.out) |
| `YearGroup/variant_no_first_break_year_0` | 一致 | [.out](week04/YearGroup/variants/tests/no_first_break_year_0.out) | [.out](../week04/YearGroup/variants/tests/no_first_break_year_0.out) |
| `YearGroup/variant_no_first_break_year_1` | 一致 | [.out](week04/YearGroup/variants/tests/no_first_break_year_1.out) | [.out](../week04/YearGroup/variants/tests/no_first_break_year_1.out) |
| `YearGroup/variant_no_first_break_year_2` | 一致 | [.out](week04/YearGroup/variants/tests/no_first_break_year_2.out) | [.out](../week04/YearGroup/variants/tests/no_first_break_year_2.out) |
| `YearGroup/variant_no_first_break_year_3` | 一致 | [.out](week04/YearGroup/variants/tests/no_first_break_year_3.out) | [.out](../week04/YearGroup/variants/tests/no_first_break_year_3.out) |
| `YearGroup/variant_no_first_break_year_4` | 一致 | [.out](week04/YearGroup/variants/tests/no_first_break_year_4.out) | [.out](../week04/YearGroup/variants/tests/no_first_break_year_4.out) |
| `YearGroup/variant_no_first_break_year_5` | 一致 | [.out](week04/YearGroup/variants/tests/no_first_break_year_5.out) | [.out](../week04/YearGroup/variants/tests/no_first_break_year_5.out) |
| `YearGroup/variant_skip_break` | 一致 | [.out](week04/YearGroup/variants/tests/skip_break.out) | [.out](../week04/YearGroup/variants/tests/skip_break.out) |
| `YearGroup/variant_skip_continue` | 一致 | [.out](week04/YearGroup/variants/tests/skip_continue.out) | [.out](../week04/YearGroup/variants/tests/skip_continue.out) |
| `YearGroup/variant_switch_year_0` | 一致 | [.out](week04/YearGroup/variants/tests/switch_year_0.out) | [.out](../week04/YearGroup/variants/tests/switch_year_0.out) |
| `YearGroup/variant_switch_year_2` | 一致 | [.out](week04/YearGroup/variants/tests/switch_year_2.out) | [.out](../week04/YearGroup/variants/tests/switch_year_2.out) |
| `YearGroup/variant_switch_year_3` | 一致 | [.out](week04/YearGroup/variants/tests/switch_year_3.out) | [.out](../week04/YearGroup/variants/tests/switch_year_3.out) |
| `YearGroup/variant_switch_year_4` | 一致 | [.out](week04/YearGroup/variants/tests/switch_year_4.out) | [.out](../week04/YearGroup/variants/tests/switch_year_4.out) |
| `YearGroup/variant_switch_year_5` | 一致 | [.out](week04/YearGroup/variants/tests/switch_year_5.out) | [.out](../week04/YearGroup/variants/tests/switch_year_5.out) |
| `YearGroup/year_1` | 一致 | [.out](week04/YearGroup/tests/year_1.out) | [.out](../week04/YearGroup/tests/year_1.out) |

## week05

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `Array3D/basic` | 一致 | [.out](week05/Array3D/tests/basic.out) | [.out](../week05/Array3D/tests/basic.out) |
| `ColumnSum/basic` | 一致 | [.out](week05/ColumnSum/tests/basic.out) | [.out](../week05/ColumnSum/tests/basic.out) |
| `ColumnSum/variant_ones` | 一致 | [.out](week05/ColumnSum/variants/tests/ones.out) | [.out](../week05/ColumnSum/variants/tests/ones.out) |
| `ColumnSum/variant_row_major` | 一致 | [.out](week05/ColumnSum/variants/tests/row_major.out) | [.out](../week05/ColumnSum/variants/tests/row_major.out) |
| `ColumnSum/variant_sum_outside` | 一致 | [.out](week05/ColumnSum/variants/tests/sum_outside.out) | [.out](../week05/ColumnSum/variants/tests/sum_outside.out) |
| `ColumnSum/variant_zero` | 一致 | [.out](week05/ColumnSum/variants/tests/zero.out) | [.out](../week05/ColumnSum/variants/tests/zero.out) |
| `Functions/basic` | 一致 | [.out](week05/Functions/tests/basic.out) | [.out](../week05/Functions/tests/basic.out) |
| `Functions/variant_a_0_0_p_2_0` | 一致 | [.out](week05/Functions/variants/tests/a_0_0_p_2_0.out) | [.out](../week05/Functions/variants/tests/a_0_0_p_2_0.out) |
| `Functions/variant_a_100_100` | 一致 | [.out](week05/Functions/variants/tests/a_100_100.out) | [.out](../week05/Functions/variants/tests/a_100_100.out) |
| `Functions/variant_a_1_2_p_5_5` | 一致 | [.out](week05/Functions/variants/tests/a_1_2_p_5_5.out) | [.out](../week05/Functions/variants/tests/a_1_2_p_5_5.out) |
| `Functions/variant_a_m100_100_p_1_5` | 一致 | [.out](week05/Functions/variants/tests/a_m100_100_p_1_5.out) | [.out](../week05/Functions/variants/tests/a_m100_100_p_1_5.out) |
| `Functions/variant_a_m100_m100_p_1_0` | 一致 | [.out](week05/Functions/variants/tests/a_m100_m100_p_1_0.out) | [.out](../week05/Functions/variants/tests/a_m100_m100_p_1_0.out) |
| `Functions/variant_a_m4_2_p_5_1` | 一致 | [.out](week05/Functions/variants/tests/a_m4_2_p_5_1.out) | [.out](../week05/Functions/variants/tests/a_m4_2_p_5_1.out) |
| `Functions/variant_before_result` | 一致 | [.out](week05/Functions/variants/tests/before_result.out) | [.out](../week05/Functions/variants/tests/before_result.out) |
| `Functions/variant_power_squaring` | 一致 | [.out](week05/Functions/variants/tests/power_squaring.out) | [.out](../week05/Functions/variants/tests/power_squaring.out) |
| `Functions/variant_power_squaring_a_0_0_p_2_0` | 一致 | [.out](week05/Functions/variants/tests/power_squaring_a_0_0_p_2_0.out) | [.out](../week05/Functions/variants/tests/power_squaring_a_0_0_p_2_0.out) |
| `Functions/variant_power_squaring_a_1_2_p_5_5` | 一致 | [.out](week05/Functions/variants/tests/power_squaring_a_1_2_p_5_5.out) | [.out](../week05/Functions/variants/tests/power_squaring_a_1_2_p_5_5.out) |
| `Functions/variant_power_squaring_a_m100_100_p_1_5` | 一致 | [.out](week05/Functions/variants/tests/power_squaring_a_m100_100_p_1_5.out) | [.out](../week05/Functions/variants/tests/power_squaring_a_m100_100_p_1_5.out) |
| `Functions/variant_power_squaring_a_m100_m100_p_1_0` | 一致 | [.out](week05/Functions/variants/tests/power_squaring_a_m100_m100_p_1_0.out) | [.out](../week05/Functions/variants/tests/power_squaring_a_m100_m100_p_1_0.out) |
| `Functions/variant_power_squaring_a_m4_2_p_5_1` | 一致 | [.out](week05/Functions/variants/tests/power_squaring_a_m4_2_p_5_1.out) | [.out](../week05/Functions/variants/tests/power_squaring_a_m4_2_p_5_1.out) |
| `Functions/variant_result_0` | 一致 | [.out](week05/Functions/variants/tests/result_0.out) | [.out](../week05/Functions/variants/tests/result_0.out) |
| `Maximum/basic` | 一致 | [.out](week05/Maximum/tests/basic.out) | [.out](../week05/Maximum/tests/basic.out) |
| `Maximum/variant_first` | 一致 | [.out](week05/Maximum/variants/tests/first.out) | [.out](../week05/Maximum/variants/tests/first.out) |
| `Maximum/variant_last` | 一致 | [.out](week05/Maximum/variants/tests/last.out) | [.out](../week05/Maximum/variants/tests/last.out) |
| `Maximum/variant_max_index` | 一致 | [.out](week05/Maximum/variants/tests/max_index.out) | [.out](../week05/Maximum/variants/tests/max_index.out) |
| `Maximum/variant_max_index_first` | 一致 | [.out](week05/Maximum/variants/tests/max_index_first.out) | [.out](../week05/Maximum/variants/tests/max_index_first.out) |
| `Maximum/variant_max_index_last` | 一致 | [.out](week05/Maximum/variants/tests/max_index_last.out) | [.out](../week05/Maximum/variants/tests/max_index_last.out) |
| `Maximum/variant_max_index_same` | 一致 | [.out](week05/Maximum/variants/tests/max_index_same.out) | [.out](../week05/Maximum/variants/tests/max_index_same.out) |
| `Maximum/variant_max_index_tie` | 一致 | [.out](week05/Maximum/variants/tests/max_index_tie.out) | [.out](../week05/Maximum/variants/tests/max_index_tie.out) |
| `Maximum/variant_max_index_zero` | 一致 | [.out](week05/Maximum/variants/tests/max_index_zero.out) | [.out](../week05/Maximum/variants/tests/max_index_zero.out) |
| `Maximum/variant_return_in_loop` | 一致 | [.out](week05/Maximum/variants/tests/return_in_loop.out) | [.out](../week05/Maximum/variants/tests/return_in_loop.out) |
| `Maximum/variant_same` | 一致 | [.out](week05/Maximum/variants/tests/same.out) | [.out](../week05/Maximum/variants/tests/same.out) |
| `Maximum/variant_zero` | 一致 | [.out](week05/Maximum/variants/tests/zero.out) | [.out](../week05/Maximum/variants/tests/zero.out) |
| `SumMean/basic` | 一致 | [.out](week05/SumMean/tests/basic.out) | [.out](../week05/SumMean/tests/basic.out) |
| `SumMean/variant_full_100` | 一致 | [.out](week05/SumMean/variants/tests/full_100.out) | [.out](../week05/SumMean/variants/tests/full_100.out) |
| `SumMean/variant_hundred_n_3` | 一致 | [.out](week05/SumMean/variants/tests/hundred_n_3.out) | [.out](../week05/SumMean/variants/tests/hundred_n_3.out) |
| `SumMean/variant_hundred_n_5_wrong` | 一致 | [.out](week05/SumMean/variants/tests/hundred_n_5_wrong.out) | [.out](../week05/SumMean/variants/tests/hundred_n_5_wrong.out) |
| `SumMean/variant_sum_only_n_0` | 一致 | [.out](week05/SumMean/variants/tests/sum_only_n_0.out) | [.out](../week05/SumMean/variants/tests/sum_only_n_0.out) |
| `SumMean/variant_zero_n_1` | 一致 | [.out](week05/SumMean/variants/tests/zero_n_1.out) | [.out](../week05/SumMean/variants/tests/zero_n_1.out) |
| `ValueCopy/basic` | 一致 | [.out](week05/ValueCopy/tests/basic.out) | [.out](../week05/ValueCopy/tests/basic.out) |
| `ValueCopy/variant_add_z` | 一致 | [.out](week05/ValueCopy/variants/tests/add_z.out) | [.out](../week05/ValueCopy/variants/tests/add_z.out) |
| `ValueCopy/variant_assign_twice` | 一致 | [.out](week05/ValueCopy/variants/tests/assign_twice.out) | [.out](../week05/ValueCopy/variants/tests/assign_twice.out) |
| `ValueCopy/variant_call_assign` | 一致 | [.out](week05/ValueCopy/variants/tests/call_assign.out) | [.out](../week05/ValueCopy/variants/tests/call_assign.out) |
| `ValueCopy/variant_call_discard` | 一致 | [.out](week05/ValueCopy/variants/tests/call_discard.out) | [.out](../week05/ValueCopy/variants/tests/call_discard.out) |
| `ValueCopy/variant_plus_one` | 一致 | [.out](week05/ValueCopy/variants/tests/plus_one.out) | [.out](../week05/ValueCopy/variants/tests/plus_one.out) |
| `ValueCopy/variant_scope_blocks` | 一致 | [.out](week05/ValueCopy/variants/tests/scope_blocks.out) | [.out](../week05/ValueCopy/variants/tests/scope_blocks.out) |
| `ValueCopy/variant_shadow_count` | 一致 | [.out](week05/ValueCopy/variants/tests/shadow_count.out) | [.out](../week05/ValueCopy/variants/tests/shadow_count.out) |
| `ValueCopy/variant_x_0` | 一致 | [.out](week05/ValueCopy/variants/tests/x_0.out) | [.out](../week05/ValueCopy/variants/tests/x_0.out) |
| `ValueCopy/variant_x_m1` | 一致 | [.out](week05/ValueCopy/variants/tests/x_m1.out) | [.out](../week05/ValueCopy/variants/tests/x_m1.out) |
| `Warmup05/basic` | 一致 | [.out](week05/Warmup05/tests/basic.out) | [.out](../week05/Warmup05/tests/basic.out) |

## week06

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `AsciiTable/basic` | 一致 | [.out](week06/AsciiTable/tests/basic.out) | [.out](../week06/AsciiTable/tests/basic.out) |
| `Average/basic` | 一致 | [.out](week06/Average/tests/basic.out) | [.out](../week06/Average/tests/basic.out) |
| `Average/variant_first` | 一致 | [.out](week06/Average/variants/tests/first.out) | [.out](../week06/Average/variants/tests/first.out) |
| `Average/variant_first_total_minus7` | 一致 | [.out](week06/Average/variants/tests/first_total_minus7.out) | [.out](../week06/Average/variants/tests/first_total_minus7.out) |
| `Average/variant_i_100` | 一致 | [.out](week06/Average/variants/tests/i_100.out) | [.out](../week06/Average/variants/tests/i_100.out) |
| `Average/variant_i_100_late_cast` | 一致 | [.out](week06/Average/variants/tests/i_100_late_cast.out) | [.out](../week06/Average/variants/tests/i_100_late_cast.out) |
| `Average/variant_i_100_no_cast` | 一致 | [.out](week06/Average/variants/tests/i_100_no_cast.out) | [.out](../week06/Average/variants/tests/i_100_no_cast.out) |
| `Average/variant_page_literal` | 一致 | [.out](week06/Average/variants/tests/page_literal.out) | [.out](../week06/Average/variants/tests/page_literal.out) |
| `Average/variant_sign_compare` | 一致 | [.out](week06/Average/variants/tests/sign_compare.out) | [.out](../week06/Average/variants/tests/sign_compare.out) |
| `CharCode/basic` | 一致 | [.out](week06/CharCode/tests/basic.out) | [.out](../week06/CharCode/tests/basic.out) |
| `CharCode/variant_c_0` | 一致 | [.out](week06/CharCode/variants/tests/c_0.out) | [.out](../week06/CharCode/variants/tests/c_0.out) |
| `CharCode/variant_c_9` | 一致 | [.out](week06/CharCode/variants/tests/c_9.out) | [.out](../week06/CharCode/variants/tests/c_9.out) |
| `CharCode/variant_c_A` | 一致 | [.out](week06/CharCode/variants/tests/c_A.out) | [.out](../week06/CharCode/variants/tests/c_A.out) |
| `CompareJoin/basic` | 一致 | [.out](week06/CompareJoin/tests/basic.out) | [.out](../week06/CompareJoin/tests/basic.out) |
| `CompareJoin/variant_capacity_5` | 一致 | [.out](week06/CompareJoin/variants/tests/capacity_5.out) | [.out](../week06/CompareJoin/variants/tests/capacity_5.out) |
| `CompareJoin/variant_capacity_5_suffix_empty` | 一致 | [.out](week06/CompareJoin/variants/tests/capacity_5_suffix_empty.out) | [.out](../week06/CompareJoin/variants/tests/capacity_5_suffix_empty.out) |
| `CompareJoin/variant_capacity_8` | 一致 | [.out](week06/CompareJoin/variants/tests/capacity_8.out) | [.out](../week06/CompareJoin/variants/tests/capacity_8.out) |
| `CompareJoin/variant_capacity_9` | 一致 | [.out](week06/CompareJoin/variants/tests/capacity_9.out) | [.out](../week06/CompareJoin/variants/tests/capacity_9.out) |
| `CompareJoin/variant_loop_lt` | 一致 | [.out](week06/CompareJoin/variants/tests/loop_lt.out) | [.out](../week06/CompareJoin/variants/tests/loop_lt.out) |
| `CompareJoin/variant_strcat` | 一致 | [.out](week06/CompareJoin/variants/tests/strcat.out) | [.out](../week06/CompareJoin/variants/tests/strcat.out) |
| `CompareJoin/variant_strcat_capacity_8` | 一致 | [.out](week06/CompareJoin/variants/tests/strcat_capacity_8.out) | [.out](../week06/CompareJoin/variants/tests/strcat_capacity_8.out) |
| `CompareJoin/variant_suffix_empty` | 一致 | [.out](week06/CompareJoin/variants/tests/suffix_empty.out) | [.out](../week06/CompareJoin/variants/tests/suffix_empty.out) |
| `CompareJoin/variant_suffix_hoge` | 一致 | [.out](week06/CompareJoin/variants/tests/suffix_hoge.out) | [.out](../week06/CompareJoin/variants/tests/suffix_hoge.out) |
| `CompareJoin/variant_suffix_z` | 一致 | [.out](week06/CompareJoin/variants/tests/suffix_z.out) | [.out](../week06/CompareJoin/variants/tests/suffix_z.out) |
| `CopyCapacity/basic` | 一致 | [.out](week06/CopyCapacity/tests/basic.out) | [.out](../week06/CopyCapacity/tests/basic.out) |
| `CopyCapacity/variant_capacity_3` | 一致 | [.out](week06/CopyCapacity/variants/tests/capacity_3.out) | [.out](../week06/CopyCapacity/variants/tests/capacity_3.out) |
| `CopyCapacity/variant_capacity_4` | 一致 | [.out](week06/CopyCapacity/variants/tests/capacity_4.out) | [.out](../week06/CopyCapacity/variants/tests/capacity_4.out) |
| `Length/basic` | 一致 | [.out](week06/Length/tests/basic.out) | [.out](../week06/Length/tests/basic.out) |
| `Length/variant_mixed` | 一致 | [.out](week06/Length/variants/tests/mixed.out) | [.out](../week06/Length/variants/tests/mixed.out) |
| `Lower/basic` | 一致 | [.out](week06/Lower/tests/basic.out) | [.out](../week06/Lower/tests/basic.out) |
| `Lower/variant_AZaz09` | 一致 | [.out](week06/Lower/variants/tests/AZaz09.out) | [.out](../week06/Lower/variants/tests/AZaz09.out) |
| `Lower/variant_A_space_B` | 一致 | [.out](week06/Lower/variants/tests/A_space_B.out) | [.out](../week06/Lower/variants/tests/A_space_B.out) |
| `Lower/variant_at_AZ_bracket` | 一致 | [.out](week06/Lower/variants/tests/at_AZ_bracket.out) | [.out](../week06/Lower/variants/tests/at_AZ_bracket.out) |
| `Lower/variant_empty` | 一致 | [.out](week06/Lower/variants/tests/empty.out) | [.out](../week06/Lower/variants/tests/empty.out) |
| `Lower/variant_inline_if` | 一致 | [.out](week06/Lower/variants/tests/inline_if.out) | [.out](../week06/Lower/variants/tests/inline_if.out) |
| `Lower/variant_inline_if_AZaz09` | 一致 | [.out](week06/Lower/variants/tests/inline_if_AZaz09.out) | [.out](../week06/Lower/variants/tests/inline_if_AZaz09.out) |
| `Lower/variant_inline_if_A_space_B` | 一致 | [.out](week06/Lower/variants/tests/inline_if_A_space_B.out) | [.out](../week06/Lower/variants/tests/inline_if_A_space_B.out) |
| `Lower/variant_inline_if_at_AZ_bracket` | 一致 | [.out](week06/Lower/variants/tests/inline_if_at_AZ_bracket.out) | [.out](../week06/Lower/variants/tests/inline_if_at_AZ_bracket.out) |
| `Lower/variant_inline_if_empty` | 一致 | [.out](week06/Lower/variants/tests/inline_if_empty.out) | [.out](../week06/Lower/variants/tests/inline_if_empty.out) |
| `Lower/variant_no_assign` | 一致 | [.out](week06/Lower/variants/tests/no_assign.out) | [.out](../week06/Lower/variants/tests/no_assign.out) |

## week07

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `ByteCount/abcd` | 一致 | [.out](week07/ByteCount/tests/abcd.out) | [.out](../week07/ByteCount/tests/abcd.out) |
| `ByteCount/empty` | 一致 | [.out](week07/ByteCount/tests/empty.out) | [.out](../week07/ByteCount/tests/empty.out) |
| `ByteCount/max_1000` | 一致 | [.out](week07/ByteCount/tests/max_1000.out) | [.out](../week07/ByteCount/tests/max_1000.out) |
| `ByteCount/newline_only` | 一致 | [.out](week07/ByteCount/tests/newline_only.out) | [.out](../week07/ByteCount/tests/newline_only.out) |
| `ByteCount/no_final_newline` | 一致 | [.out](week07/ByteCount/tests/no_final_newline.out) | [.out](../week07/ByteCount/tests/no_final_newline.out) |
| `ByteCount/pipe_ab` | 一致 | [.out](week07/ByteCount/tests/pipe_ab.out) | [.out](../week07/ByteCount/tests/pipe_ab.out) |
| `ByteCount/pipe_ready` | 一致 | [.out](week07/ByteCount/tests/pipe_ready.out) | [.out](../week07/ByteCount/tests/pipe_ready.out) |
| `ByteCount/two_lines` | 一致 | [.out](week07/ByteCount/tests/two_lines.out) | [.out](../week07/ByteCount/tests/two_lines.out) |
| `Echo/empty` | 一致 | [.out](week07/Echo/tests/empty.out) | [.out](../week07/Echo/tests/empty.out) |
| `Echo/newline_only` | 一致 | [.out](week07/Echo/tests/newline_only.out) | [.out](../week07/Echo/tests/newline_only.out) |
| `Echo/no_final_newline` | 一致 | [.out](week07/Echo/tests/no_final_newline.out) | [.out](../week07/Echo/tests/no_final_newline.out) |
| `Echo/spaces_line` | 一致 | [.out](week07/Echo/tests/spaces_line.out) | [.out](../week07/Echo/tests/spaces_line.out) |
| `Echo/two_lines` | 一致 | [.out](week07/Echo/tests/two_lines.out) | [.out](../week07/Echo/tests/two_lines.out) |
| `Echo/variant_char_ch--ab_ff_cd` | 一致 | [.out](week07/Echo/variants/tests/char_ch--ab_ff_cd.out) | [.out](../week07/Echo/variants/tests/char_ch--ab_ff_cd.out) |
| `Echo/variant_no_parens--ab` | 一致 | [.out](week07/Echo/variants/tests/no_parens--ab.out) | [.out](../week07/Echo/variants/tests/no_parens--ab.out) |
| `Echo/variant_slash--ab` | 一致 | [.out](week07/Echo/variants/tests/slash--ab.out) | [.out](../week07/Echo/variants/tests/slash--ab.out) |
| `Echo/variant_slash--empty` | 一致 | [.out](week07/Echo/variants/tests/slash--empty.out) | [.out](../week07/Echo/variants/tests/slash--empty.out) |
| `Echo/variant_slash--newline_only` | 一致 | [.out](week07/Echo/variants/tests/slash--newline_only.out) | [.out](../week07/Echo/variants/tests/slash--newline_only.out) |
| `Echo/variant_slash--two_lines` | 一致 | [.out](week07/Echo/variants/tests/slash--two_lines.out) | [.out](../week07/Echo/variants/tests/slash--two_lines.out) |
| `Echo/variant_visible--ab` | 一致 | [.out](week07/Echo/variants/tests/visible--ab.out) | [.out](../week07/Echo/variants/tests/visible--ab.out) |
| `Echo/variant_visible--empty` | 一致 | [.out](week07/Echo/variants/tests/visible--empty.out) | [.out](../week07/Echo/variants/tests/visible--empty.out) |
| `Echo/variant_visible--newline_only` | 一致 | [.out](week07/Echo/variants/tests/visible--newline_only.out) | [.out](../week07/Echo/variants/tests/visible--newline_only.out) |
| `Echo/variant_visible--two_lines` | 一致 | [.out](week07/Echo/variants/tests/visible--two_lines.out) | [.out](../week07/Echo/variants/tests/visible--two_lines.out) |
| `Formats/basic` | 一致 | [.out](week07/Formats/tests/basic.out) | [.out](../week07/Formats/tests/basic.out) |
| `Formats/variant_base_hex` | 一致 | [.out](week07/Formats/variants/tests/base_hex.out) | [.out](../week07/Formats/variants/tests/base_hex.out) |
| `Formats/variant_base_octal` | 一致 | [.out](week07/Formats/variants/tests/base_octal.out) | [.out](../week07/Formats/variants/tests/base_octal.out) |
| `Formats/variant_n_123456` | 一致 | [.out](week07/Formats/variants/tests/n_123456.out) | [.out](../week07/Formats/variants/tests/n_123456.out) |
| `LetterCount/abc_12` | 一致 | [.out](week07/LetterCount/tests/abc_12.out) | [.out](../week07/LetterCount/tests/abc_12.out) |
| `LetterCount/azaz` | 一致 | [.out](week07/LetterCount/tests/azaz.out) | [.out](../week07/LetterCount/tests/azaz.out) |
| `LetterCount/crlf` | 一致 | [.out](week07/LetterCount/tests/crlf.out) | [.out](../week07/LetterCount/tests/crlf.out) |
| `LetterCount/empty_line` | 一致 | [.out](week07/LetterCount/tests/empty_line.out) | [.out](../week07/LetterCount/tests/empty_line.out) |
| `LetterCount/eof_only` | 一致 | [.out](week07/LetterCount/tests/eof_only.out) | [.out](../week07/LetterCount/tests/eof_only.out) |
| `LetterCount/first_line_only` | 一致 | [.out](week07/LetterCount/tests/first_line_only.out) | [.out](../week07/LetterCount/tests/first_line_only.out) |
| `LetterCount/lower_boundary` | 一致 | [.out](week07/LetterCount/tests/lower_boundary.out) | [.out](../week07/LetterCount/tests/lower_boundary.out) |
| `LetterCount/max_1000` | 一致 | [.out](week07/LetterCount/tests/max_1000.out) | [.out](../week07/LetterCount/tests/max_1000.out) |
| `LetterCount/no_final_newline` | 一致 | [.out](week07/LetterCount/tests/no_final_newline.out) | [.out](../week07/LetterCount/tests/no_final_newline.out) |
| `LetterCount/no_letters` | 一致 | [.out](week07/LetterCount/tests/no_letters.out) | [.out](../week07/LetterCount/tests/no_letters.out) |
| `LetterCount/outside_az` | 一致 | [.out](week07/LetterCount/tests/outside_az.out) | [.out](../week07/LetterCount/tests/outside_az.out) |
| `LetterCount/variant_line_array--abc_12` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--abc_12.out) | [.out](../week07/LetterCount/variants/tests/line_array--abc_12.out) |
| `LetterCount/variant_line_array--azaz` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--azaz.out) | [.out](../week07/LetterCount/variants/tests/line_array--azaz.out) |
| `LetterCount/variant_line_array--crlf` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--crlf.out) | [.out](../week07/LetterCount/variants/tests/line_array--crlf.out) |
| `LetterCount/variant_line_array--empty_line` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--empty_line.out) | [.out](../week07/LetterCount/variants/tests/line_array--empty_line.out) |
| `LetterCount/variant_line_array--eof_only` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--eof_only.out) | [.out](../week07/LetterCount/variants/tests/line_array--eof_only.out) |
| `LetterCount/variant_line_array--first_line_only` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--first_line_only.out) | [.out](../week07/LetterCount/variants/tests/line_array--first_line_only.out) |
| `LetterCount/variant_line_array--lower_boundary` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--lower_boundary.out) | [.out](../week07/LetterCount/variants/tests/line_array--lower_boundary.out) |
| `LetterCount/variant_line_array--max_1000` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--max_1000.out) | [.out](../week07/LetterCount/variants/tests/line_array--max_1000.out) |
| `LetterCount/variant_line_array--no_final_newline` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--no_final_newline.out) | [.out](../week07/LetterCount/variants/tests/line_array--no_final_newline.out) |
| `LetterCount/variant_line_array--no_letters` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--no_letters.out) | [.out](../week07/LetterCount/variants/tests/line_array--no_letters.out) |
| `LetterCount/variant_line_array--outside_az` | 一致 | [.out](week07/LetterCount/variants/tests/line_array--outside_az.out) | [.out](../week07/LetterCount/variants/tests/line_array--outside_az.out) |
| `LetterCount/variant_line_array_100--max_1000` | 一致 | [.out](week07/LetterCount/variants/tests/line_array_100--max_1000.out) | [.out](../week07/LetterCount/variants/tests/line_array_100--max_1000.out) |
| `LetterCount/variant_one_range--lower_boundary` | 一致 | [.out](week07/LetterCount/variants/tests/one_range--lower_boundary.out) | [.out](../week07/LetterCount/variants/tests/one_range--lower_boundary.out) |
| `LetterCount/variant_one_range--outside_az` | 一致 | [.out](week07/LetterCount/variants/tests/one_range--outside_az.out) | [.out](../week07/LetterCount/variants/tests/one_range--outside_az.out) |
| `LineInput/a30` | 一致 | [.out](week07/LineInput/tests/a30.out) | [.out](../week07/LineInput/tests/a30.out) |
| `LineInput/a31` | 一致 | [.out](week07/LineInput/tests/a31.out) | [.out](../week07/LineInput/tests/a31.out) |
| `LineInput/a31_no_newline` | 一致 | [.out](week07/LineInput/tests/a31_no_newline.out) | [.out](../week07/LineInput/tests/a31_no_newline.out) |
| `LineInput/a32_no_newline` | 一致 | [.out](week07/LineInput/tests/a32_no_newline.out) [.err](week07/LineInput/tests/a32_no_newline.err) [.code](week07/LineInput/tests/a32_no_newline.code) | [.out](../week07/LineInput/tests/a32_no_newline.out) |
| `LineInput/a32_too_long` | 一致 | [.out](week07/LineInput/tests/a32_too_long.out) [.err](week07/LineInput/tests/a32_too_long.err) [.code](week07/LineInput/tests/a32_too_long.code) | [.out](../week07/LineInput/tests/a32_too_long.out) |
| `LineInput/empty_line` | 一致 | [.out](week07/LineInput/tests/empty_line.out) | [.out](../week07/LineInput/tests/empty_line.out) |
| `LineInput/eof_only` | 一致 | [.out](week07/LineInput/tests/eof_only.out) [.err](week07/LineInput/tests/eof_only.err) [.code](week07/LineInput/tests/eof_only.code) | [.out](../week07/LineInput/tests/eof_only.out) |
| `LineInput/first_line_only` | 一致 | [.out](week07/LineInput/tests/first_line_only.out) | [.out](../week07/LineInput/tests/first_line_only.out) |
| `LineInput/hello` | 一致 | [.out](week07/LineInput/tests/hello.out) | [.out](../week07/LineInput/tests/hello.out) |
| `LineInput/hello_no_newline` | 一致 | [.out](week07/LineInput/tests/hello_no_newline.out) | [.out](../week07/LineInput/tests/hello_no_newline.out) |
| `LineInput/spaces` | 一致 | [.out](week07/LineInput/tests/spaces.out) | [.out](../week07/LineInput/tests/spaces.out) |
| `LineInput/variant_line8--abcdef` | 一致 | [.out](week07/LineInput/variants/tests/line8--abcdef.out) | [.out](../week07/LineInput/variants/tests/line8--abcdef.out) |
| `LineInput/variant_line8--abcdefg` | 一致 | [.out](week07/LineInput/variants/tests/line8--abcdefg.out) | [.out](../week07/LineInput/variants/tests/line8--abcdefg.out) |
| `LineInput/variant_line8--abcdefg_no_newline` | 一致 | [.out](week07/LineInput/variants/tests/line8--abcdefg_no_newline.out) | [.out](../week07/LineInput/variants/tests/line8--abcdefg_no_newline.out) |
| `LineInput/variant_line8--abcdefgh` | 一致 | [.out](week07/LineInput/variants/tests/line8--abcdefgh.out) [.err](week07/LineInput/variants/tests/line8--abcdefgh.err) [.code](week07/LineInput/variants/tests/line8--abcdefgh.code) | [.out](../week07/LineInput/variants/tests/line8--abcdefgh.out) |
| `LineInput/variant_line8--empty_line` | 一致 | [.out](week07/LineInput/variants/tests/line8--empty_line.out) | [.out](../week07/LineInput/variants/tests/line8--empty_line.out) |
| `LineInput/variant_line8--eof_only` | 一致 | [.out](week07/LineInput/variants/tests/line8--eof_only.out) [.err](week07/LineInput/variants/tests/line8--eof_only.err) [.code](week07/LineInput/variants/tests/line8--eof_only.code) | [.out](../week07/LineInput/variants/tests/line8--eof_only.out) |
| `LowerInput/ab` | 一致 | [.out](week07/LowerInput/tests/ab.out) | [.out](../week07/LowerInput/tests/ab.out) |
| `LowerInput/azaz09` | 一致 | [.out](week07/LowerInput/tests/azaz09.out) | [.out](../week07/LowerInput/tests/azaz09.out) |
| `LowerInput/boundary` | 一致 | [.out](week07/LowerInput/tests/boundary.out) | [.out](../week07/LowerInput/tests/boundary.out) |
| `LowerInput/crlf` | 一致 | [.out](week07/LowerInput/tests/crlf.out) | [.out](../week07/LowerInput/tests/crlf.out) |
| `LowerInput/empty` | 一致 | [.out](week07/LowerInput/tests/empty.out) | [.out](../week07/LowerInput/tests/empty.out) |
| `LowerInput/hello` | 一致 | [.out](week07/LowerInput/tests/hello.out) | [.out](../week07/LowerInput/tests/hello.out) |
| `LowerInput/multi_lines` | 一致 | [.out](week07/LowerInput/tests/multi_lines.out) | [.out](../week07/LowerInput/tests/multi_lines.out) |
| `LowerInput/newline_only` | 一致 | [.out](week07/LowerInput/tests/newline_only.out) | [.out](../week07/LowerInput/tests/newline_only.out) |
| `LowerInput/no_final_newline` | 一致 | [.out](week07/LowerInput/tests/no_final_newline.out) | [.out](../week07/LowerInput/tests/no_final_newline.out) |
| `LowerInput/variant_ready--ab` | 一致 | [.out](week07/LowerInput/variants/tests/ready--ab.out) [.err](week07/LowerInput/variants/tests/ready--ab.err) | [.out](../week07/LowerInput/variants/tests/ready--ab.out) |
| `LowerInput/variant_status--ab` | 一致 | [.out](week07/LowerInput/variants/tests/status--ab.out) [.err](week07/LowerInput/variants/tests/status--ab.err) | [.out](../week07/LowerInput/variants/tests/status--ab.out) |
| `LowerInput/variant_strict--azaz09` | 一致 | [.out](week07/LowerInput/variants/tests/strict--azaz09.out) | [.out](../week07/LowerInput/variants/tests/strict--azaz09.out) |
| `Typing/a_empty_line` | 一致 | [.out](week07/Typing/tests/a_empty_line.out) | [.out](../week07/Typing/tests/a_empty_line.out) |
| `Typing/a_exact` | 一致 | [.out](week07/Typing/tests/a_exact.out) | [.out](../week07/Typing/tests/a_exact.out) |
| `Typing/all_wrong` | 一致 | [.out](week07/Typing/tests/all_wrong.out) | [.out](../week07/Typing/tests/all_wrong.out) |
| `Typing/b_partial` | 一致 | [.out](week07/Typing/tests/b_partial.out) | [.out](../week07/Typing/tests/b_partial.out) |
| `Typing/c_same_position` | 一致 | [.out](week07/Typing/tests/c_same_position.out) | [.out](../week07/Typing/tests/c_same_position.out) |
| `Typing/crlf` | 一致 | [.out](week07/Typing/tests/crlf.out) | [.out](../week07/Typing/tests/crlf.out) |
| `Typing/d_ignore_case` | 一致 | [.out](week07/Typing/tests/d_ignore_case.out) | [.out](../week07/Typing/tests/d_ignore_case.out) |
| `Typing/eof_only` | 一致 | [.out](week07/Typing/tests/eof_only.out) | [.out](../week07/Typing/tests/eof_only.out) |
| `Typing/extra_char` | 一致 | [.out](week07/Typing/tests/extra_char.out) | [.out](../week07/Typing/tests/extra_char.out) |
| `Typing/first_line_only` | 一致 | [.out](week07/Typing/tests/first_line_only.out) | [.out](../week07/Typing/tests/first_line_only.out) |
| `Typing/max_1000` | 一致 | [.out](week07/Typing/tests/max_1000.out) | [.out](../week07/Typing/tests/max_1000.out) |
| `Typing/missing_char` | 一致 | [.out](week07/Typing/tests/missing_char.out) | [.out](../week07/Typing/tests/missing_char.out) |
| `Typing/no_final_newline` | 一致 | [.out](week07/Typing/tests/no_final_newline.out) | [.out](../week07/Typing/tests/no_final_newline.out) |
| `Typing/twice` | 一致 | [.out](week07/Typing/tests/twice.out) | [.out](../week07/Typing/tests/twice.out) |
| `Typing/upper_all` | 一致 | [.out](week07/Typing/tests/upper_all.out) | [.out](../week07/Typing/tests/upper_all.out) |
| `Typing/variant_advance_on_match--exact` | 一致 | [.out](week07/Typing/variants/tests/advance_on_match--exact.out) | [.out](../week07/Typing/variants/tests/advance_on_match--exact.out) |
| `Typing/variant_advance_on_match--missing_char` | 一致 | [.out](week07/Typing/variants/tests/advance_on_match--missing_char.out) | [.out](../week07/Typing/variants/tests/advance_on_match--missing_char.out) |
| `Typing/variant_advance_on_match--same_position` | 一致 | [.out](week07/Typing/variants/tests/advance_on_match--same_position.out) | [.out](../week07/Typing/variants/tests/advance_on_match--same_position.out) |
| `Typing/variant_bounded--a_empty_line` | 一致 | [.out](week07/Typing/variants/tests/bounded--a_empty_line.out) | [.out](../week07/Typing/variants/tests/bounded--a_empty_line.out) |
| `Typing/variant_bounded--a_exact` | 一致 | [.out](week07/Typing/variants/tests/bounded--a_exact.out) | [.out](../week07/Typing/variants/tests/bounded--a_exact.out) |
| `Typing/variant_bounded--all_wrong` | 一致 | [.out](week07/Typing/variants/tests/bounded--all_wrong.out) | [.out](../week07/Typing/variants/tests/bounded--all_wrong.out) |
| `Typing/variant_bounded--b_partial` | 一致 | [.out](week07/Typing/variants/tests/bounded--b_partial.out) | [.out](../week07/Typing/variants/tests/bounded--b_partial.out) |
| `Typing/variant_bounded--c_same_position` | 一致 | [.out](week07/Typing/variants/tests/bounded--c_same_position.out) | [.out](../week07/Typing/variants/tests/bounded--c_same_position.out) |
| `Typing/variant_bounded--crlf` | 一致 | [.out](week07/Typing/variants/tests/bounded--crlf.out) | [.out](../week07/Typing/variants/tests/bounded--crlf.out) |
| `Typing/variant_bounded--d_ignore_case` | 一致 | [.out](week07/Typing/variants/tests/bounded--d_ignore_case.out) | [.out](../week07/Typing/variants/tests/bounded--d_ignore_case.out) |
| `Typing/variant_bounded--eof_only` | 一致 | [.out](week07/Typing/variants/tests/bounded--eof_only.out) | [.out](../week07/Typing/variants/tests/bounded--eof_only.out) |
| `Typing/variant_bounded--extra_char` | 一致 | [.out](week07/Typing/variants/tests/bounded--extra_char.out) | [.out](../week07/Typing/variants/tests/bounded--extra_char.out) |
| `Typing/variant_bounded--first_line_only` | 一致 | [.out](week07/Typing/variants/tests/bounded--first_line_only.out) | [.out](../week07/Typing/variants/tests/bounded--first_line_only.out) |
| `Typing/variant_bounded--max_1000` | 一致 | [.out](week07/Typing/variants/tests/bounded--max_1000.out) | [.out](../week07/Typing/variants/tests/bounded--max_1000.out) |
| `Typing/variant_bounded--missing_char` | 一致 | [.out](week07/Typing/variants/tests/bounded--missing_char.out) | [.out](../week07/Typing/variants/tests/bounded--missing_char.out) |
| `Typing/variant_bounded--no_final_newline` | 一致 | [.out](week07/Typing/variants/tests/bounded--no_final_newline.out) | [.out](../week07/Typing/variants/tests/bounded--no_final_newline.out) |
| `Typing/variant_bounded--twice` | 一致 | [.out](week07/Typing/variants/tests/bounded--twice.out) | [.out](../week07/Typing/variants/tests/bounded--twice.out) |
| `Typing/variant_bounded--upper_all` | 一致 | [.out](week07/Typing/variants/tests/bounded--upper_all.out) | [.out](../week07/Typing/variants/tests/bounded--upper_all.out) |
| `Typing/variant_case_sensitive--exact` | 一致 | [.out](week07/Typing/variants/tests/case_sensitive--exact.out) | [.out](../week07/Typing/variants/tests/case_sensitive--exact.out) |
| `Typing/variant_case_sensitive--mixed` | 一致 | [.out](week07/Typing/variants/tests/case_sensitive--mixed.out) | [.out](../week07/Typing/variants/tests/case_sensitive--mixed.out) |
| `Typing/variant_case_sensitive--partial` | 一致 | [.out](week07/Typing/variants/tests/case_sensitive--partial.out) | [.out](../week07/Typing/variants/tests/case_sensitive--partial.out) |
| `Typing/variant_case_sensitive--same_position` | 一致 | [.out](week07/Typing/variants/tests/case_sensitive--same_position.out) | [.out](../week07/Typing/variants/tests/case_sensitive--same_position.out) |
| `Typing/variant_case_sensitive--upper_all` | 一致 | [.out](week07/Typing/variants/tests/case_sensitive--upper_all.out) | [.out](../week07/Typing/variants/tests/case_sensitive--upper_all.out) |

## week08

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `CopyText/basic` | 一致 | [.out](week08/CopyText/tests/basic.out) | [.out](../week08/CopyText/tests/basic.out) |
| `CopyText/variant_index` | 一致 | [.out](week08/CopyText/variants/tests/index.out) | [.out](../week08/CopyText/variants/tests/index.out) |
| `CopyText/variant_short_form` | 一致 | [.out](week08/CopyText/variants/tests/short_form.out) | [.out](../week08/CopyText/variants/tests/short_form.out) |
| `Decompose/basic` | 一致 | [.out](week08/Decompose/tests/basic.out) | [.out](../week08/Decompose/tests/basic.out) |
| `Decompose/variant_five` | 一致 | [.out](week08/Decompose/variants/tests/five.out) | [.out](../week08/Decompose/variants/tests/five.out) |
| `Decompose/variant_min_pointer_3_9` | 一致 | [.out](week08/Decompose/variants/tests/min_pointer_3_9.out) | [.out](../week08/Decompose/variants/tests/min_pointer_3_9.out) |
| `Decompose/variant_min_pointer_5_5` | 一致 | [.out](week08/Decompose/variants/tests/min_pointer_5_5.out) | [.out](../week08/Decompose/variants/tests/min_pointer_5_5.out) |
| `Decompose/variant_min_pointer_9_3` | 一致 | [.out](week08/Decompose/variants/tests/min_pointer_9_3.out) | [.out](../week08/Decompose/variants/tests/min_pointer_9_3.out) |
| `Decompose/variant_minus_0_5` | 一致 | [.out](week08/Decompose/variants/tests/minus_0_5.out) | [.out](../week08/Decompose/variants/tests/minus_0_5.out) |
| `Decompose/variant_minus_100` | 一致 | [.out](week08/Decompose/variants/tests/minus_100.out) | [.out](../week08/Decompose/variants/tests/minus_100.out) |
| `Decompose/variant_minus_3_14` | 一致 | [.out](week08/Decompose/variants/tests/minus_3_14.out) | [.out](../week08/Decompose/variants/tests/minus_3_14.out) |
| `Decompose/variant_plus_100` | 一致 | [.out](week08/Decompose/variants/tests/plus_100.out) | [.out](../week08/Decompose/variants/tests/plus_100.out) |
| `Decompose/variant_value_args` | 一致 | [.out](week08/Decompose/variants/tests/value_args.out) | [.out](../week08/Decompose/variants/tests/value_args.out) |
| `Decompose/variant_x_99_99` | 一致 | [.out](week08/Decompose/variants/tests/x_99_99.out) | [.out](../week08/Decompose/variants/tests/x_99_99.out) |
| `Decompose/variant_zero` | 一致 | [.out](week08/Decompose/variants/tests/zero.out) | [.out](../week08/Decompose/variants/tests/zero.out) |
| `MinMax/basic` | 一致 | [.out](week08/MinMax/tests/basic.out) | [.out](../week08/MinMax/tests/basic.out) |
| `MinMax/variant_all_negative` | 一致 | [.out](week08/MinMax/variants/tests/all_negative.out) | [.out](../week08/MinMax/variants/tests/all_negative.out) |
| `MinMax/variant_five_elements` | 一致 | [.out](week08/MinMax/variants/tests/five_elements.out) | [.out](../week08/MinMax/variants/tests/five_elements.out) |
| `MinMax/variant_local` | 一致 | [.out](week08/MinMax/variants/tests/local.out) | [.out](../week08/MinMax/variants/tests/local.out) |
| `MinMax/variant_local_all_negative` | 一致 | [.out](week08/MinMax/variants/tests/local_all_negative.out) | [.out](../week08/MinMax/variants/tests/local_all_negative.out) |
| `MinMax/variant_local_five_elements` | 一致 | [.out](week08/MinMax/variants/tests/local_five_elements.out) | [.out](../week08/MinMax/variants/tests/local_five_elements.out) |
| `MinMax/variant_local_overlap` | 一致 | [.out](week08/MinMax/variants/tests/local_overlap.out) | [.out](../week08/MinMax/variants/tests/local_overlap.out) |
| `MinMax/variant_local_same_3` | 一致 | [.out](week08/MinMax/variants/tests/local_same_3.out) | [.out](../week08/MinMax/variants/tests/local_same_3.out) |
| `MinMax/variant_local_same_address` | 一致 | [.out](week08/MinMax/variants/tests/local_same_address.out) | [.out](../week08/MinMax/variants/tests/local_same_address.out) |
| `MinMax/variant_local_single_5` | 一致 | [.out](week08/MinMax/variants/tests/local_single_5.out) | [.out](../week08/MinMax/variants/tests/local_single_5.out) |
| `MinMax/variant_overlap` | 一致 | [.out](week08/MinMax/variants/tests/overlap.out) | [.out](../week08/MinMax/variants/tests/overlap.out) |
| `MinMax/variant_same_3` | 一致 | [.out](week08/MinMax/variants/tests/same_3.out) | [.out](../week08/MinMax/variants/tests/same_3.out) |
| `MinMax/variant_same_address` | 一致 | [.out](week08/MinMax/variants/tests/same_address.out) | [.out](../week08/MinMax/variants/tests/same_address.out) |
| `MinMax/variant_single_5` | 一致 | [.out](week08/MinMax/variants/tests/single_5.out) | [.out](../week08/MinMax/variants/tests/single_5.out) |
| `MinMax/variant_trace` | 一致 | [.out](week08/MinMax/variants/tests/trace.out) | [.out](../week08/MinMax/variants/tests/trace.out) |
| `PointerWalk/basic` | 一致 | [.out](week08/PointerWalk/tests/basic.out) | [.out](../week08/PointerWalk/tests/basic.out) |
| `PointerWalk/variant_ascending` | 一致 | [.out](week08/PointerWalk/variants/tests/ascending.out) | [.out](../week08/PointerWalk/variants/tests/ascending.out) |
| `PointerWalk/variant_inline` | 一致 | [.out](week08/PointerWalk/variants/tests/inline.out) | [.out](../week08/PointerWalk/variants/tests/inline.out) |
| `PointerWalk/variant_length_A` | 一致 | [.out](week08/PointerWalk/variants/tests/length_A.out) | [.out](../week08/PointerWalk/variants/tests/length_A.out) |
| `PointerWalk/variant_length_Hello` | 一致 | [.out](week08/PointerWalk/variants/tests/length_Hello.out) | [.out](../week08/PointerWalk/variants/tests/length_Hello.out) |
| `PointerWalk/variant_length_empty` | 一致 | [.out](week08/PointerWalk/variants/tests/length_empty.out) | [.out](../week08/PointerWalk/variants/tests/length_empty.out) |
| `PointerWalk/variant_post_increment` | 一致 | [.out](week08/PointerWalk/variants/tests/post_increment.out) | [.out](../week08/PointerWalk/variants/tests/post_increment.out) |
| `PointerWalk/variant_q_a1` | 一致 | [.out](week08/PointerWalk/variants/tests/q_a1.out) | [.out](../week08/PointerWalk/variants/tests/q_a1.out) |
| `PointerWalk/variant_reverse_diff` | 一致 | [.out](week08/PointerWalk/variants/tests/reverse_diff.out) | [.out](../week08/PointerWalk/variants/tests/reverse_diff.out) |
| `PointerWalk/variant_set_one_first` | 一致 | [.out](week08/PointerWalk/variants/tests/set_one_first.out) | [.out](../week08/PointerWalk/variants/tests/set_one_first.out) |
| `PointerWalk/variant_zeros` | 一致 | [.out](week08/PointerWalk/variants/tests/zeros.out) | [.out](../week08/PointerWalk/variants/tests/zeros.out) |
| `Swap/basic` | 一致 | [.out](week08/Swap/tests/basic.out) | [.out](../week08/Swap/tests/basic.out) |
| `Swap/variant_both_8` | 一致 | [.out](week08/Swap/variants/tests/both_8.out) | [.out](../week08/Swap/variants/tests/both_8.out) |
| `Swap/variant_copy_pointer` | 一致 | [.out](week08/Swap/variants/tests/copy_pointer.out) | [.out](../week08/Swap/variants/tests/copy_pointer.out) |
| `Swap/variant_swap_double_address` | 一致 | [.out](week08/Swap/variants/tests/swap_double_address.out) | [.out](../week08/Swap/variants/tests/swap_double_address.out) |
| `Swap/variant_swap_double_pointer` | 一致 | [.out](week08/Swap/variants/tests/swap_double_pointer.out) | [.out](../week08/Swap/variants/tests/swap_double_pointer.out) |
| `Swap/variant_swap_double_value` | 一致 | [.out](week08/Swap/variants/tests/swap_double_value.out) | [.out](../week08/Swap/variants/tests/swap_double_value.out) |
| `Swap/variant_trace` | 一致 | [.out](week08/Swap/variants/tests/trace.out) | [.out](../week08/Swap/variants/tests/trace.out) |
| `Swap/variant_wrong_swap` | 一致 | [.out](week08/Swap/variants/tests/wrong_swap.out) | [.out](../week08/Swap/variants/tests/wrong_swap.out) |
| `Swap/variant_y_5` | 一致 | [.out](week08/Swap/variants/tests/y_5.out) | [.out](../week08/Swap/variants/tests/y_5.out) |

## week09

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `ArrayTypes/basic` | 一致 | [.out](week09/ArrayTypes/tests/basic.out) | [.out](../week09/ArrayTypes/tests/basic.out) |
| `FindMax/basic` | 一致 | [.out](week09/FindMax/tests/basic.out) | [.out](../week09/FindMax/tests/basic.out) |
| `FindMax/variant_n0` | 一致 | [.out](week09/FindMax/variants/tests/n0.out) | [.out](../week09/FindMax/variants/tests/n0.out) |
| `FindMax/variant_n1` | 一致 | [.out](week09/FindMax/variants/tests/n1.out) | [.out](../week09/FindMax/variants/tests/n1.out) |
| `FindMax/variant_n_m1` | 一致 | [.out](week09/FindMax/variants/tests/n_m1.out) | [.out](../week09/FindMax/variants/tests/n_m1.out) |
| `FindMax/variant_out_first` | 一致 | [.out](week09/FindMax/variants/tests/out_first.out) | [.out](../week09/FindMax/variants/tests/out_first.out) |
| `FindMax/variant_stale` | 一致 | [.out](week09/FindMax/variants/tests/stale.out) | [.out](../week09/FindMax/variants/tests/stale.out) |
| `FindMax/variant_tie` | 一致 | [.out](week09/FindMax/variants/tests/tie.out) | [.out](../week09/FindMax/variants/tests/tie.out) |
| `FindMax/variant_tie_ge` | 一致 | [.out](week09/FindMax/variants/tests/tie_ge.out) | [.out](../week09/FindMax/variants/tests/tie_ge.out) |
| `FindMax/variant_trace` | 一致 | [.out](week09/FindMax/variants/tests/trace.out) | [.out](../week09/FindMax/variants/tests/trace.out) |
| `MatrixMean/basic` | 一致 | [.out](week09/MatrixMean/tests/basic.out) | [.out](../week09/MatrixMean/tests/basic.out) |
| `MatrixMean/variant_array_param` | 一致 | [.out](week09/MatrixMean/variants/tests/array_param.out) | [.out](../week09/MatrixMean/variants/tests/array_param.out) |
| `MatrixMean/variant_flat_fraction` | 一致 | [.out](week09/MatrixMean/variants/tests/flat_fraction.out) | [.out](../week09/MatrixMean/variants/tests/flat_fraction.out) |
| `MatrixMean/variant_flat_low_high` | 一致 | [.out](week09/MatrixMean/variants/tests/flat_low_high.out) | [.out](../week09/MatrixMean/variants/tests/flat_low_high.out) |
| `MatrixMean/variant_flat_means` | 一致 | [.out](week09/MatrixMean/variants/tests/flat_means.out) | [.out](../week09/MatrixMean/variants/tests/flat_means.out) |
| `MatrixMean/variant_flat_rows0` | 一致 | [.out](week09/MatrixMean/variants/tests/flat_rows0.out) | [.out](../week09/MatrixMean/variants/tests/flat_rows0.out) |
| `MatrixMean/variant_flat_rows1` | 一致 | [.out](week09/MatrixMean/variants/tests/flat_rows1.out) | [.out](../week09/MatrixMean/variants/tests/flat_rows1.out) |
| `MatrixMean/variant_fraction` | 一致 | [.out](week09/MatrixMean/variants/tests/fraction.out) | [.out](../week09/MatrixMean/variants/tests/fraction.out) |
| `MatrixMean/variant_int_division` | 一致 | [.out](week09/MatrixMean/variants/tests/int_division.out) | [.out](../week09/MatrixMean/variants/tests/int_division.out) |
| `MatrixMean/variant_low_high` | 一致 | [.out](week09/MatrixMean/variants/tests/low_high.out) | [.out](../week09/MatrixMean/variants/tests/low_high.out) |
| `MatrixMean/variant_overall` | 一致 | [.out](week09/MatrixMean/variants/tests/overall.out) | [.out](../week09/MatrixMean/variants/tests/overall.out) |
| `MatrixMean/variant_overall_rows0` | 一致 | [.out](week09/MatrixMean/variants/tests/overall_rows0.out) | [.out](../week09/MatrixMean/variants/tests/overall_rows0.out) |
| `MatrixMean/variant_rows0` | 一致 | [.out](week09/MatrixMean/variants/tests/rows0.out) | [.out](../week09/MatrixMean/variants/tests/rows0.out) |
| `MatrixMean/variant_rows1` | 一致 | [.out](week09/MatrixMean/variants/tests/rows1.out) | [.out](../week09/MatrixMean/variants/tests/rows1.out) |
| `MatrixMean/variant_sizeof_check` | 一致 | [.out](week09/MatrixMean/variants/tests/sizeof_check.out) | [.out](../week09/MatrixMean/variants/tests/sizeof_check.out) |
| `Names/basic` | 一致 | [.out](week09/Names/tests/basic.out) | [.out](../week09/Names/tests/basic.out) |
| `Names/variant_city` | 一致 | [.out](week09/Names/variants/tests/city.out) | [.out](../week09/Names/variants/tests/city.out) |
| `Names/variant_direct` | 一致 | [.out](week09/Names/variants/tests/direct.out) | [.out](../week09/Names/variants/tests/direct.out) |
| `Names/variant_editable` | 一致 | [.out](week09/Names/variants/tests/editable.out) | [.out](../week09/Names/variants/tests/editable.out) |
| `Names/variant_swap_1_1` | 一致 | [.out](week09/Names/variants/tests/swap_1_1.out) | [.out](../week09/Names/variants/tests/swap_1_1.out) |
| `Names/variant_swap_twice` | 一致 | [.out](week09/Names/variants/tests/swap_twice.out) | [.out](../week09/Names/variants/tests/swap_twice.out) |
| `RaggedRows/basic` | 一致 | [.out](week09/RaggedRows/tests/basic.out) | [.out](../week09/RaggedRows/tests/basic.out) |
| `RaggedRows/variant_animal` | 一致 | [.out](week09/RaggedRows/variants/tests/animal.out) | [.out](../week09/RaggedRows/variants/tests/animal.out) |
| `RaggedRows/variant_letters` | 一致 | [.out](week09/RaggedRows/variants/tests/letters.out) | [.out](../week09/RaggedRows/variants/tests/letters.out) |
| `RaggedRows/variant_means` | 一致 | [.out](week09/RaggedRows/variants/tests/means.out) | [.out](../week09/RaggedRows/variants/tests/means.out) |
| `RaggedRows/variant_swap_with_lengths` | 一致 | [.out](week09/RaggedRows/variants/tests/swap_with_lengths.out) | [.out](../week09/RaggedRows/variants/tests/swap_with_lengths.out) |
| `ReturnMaximum/basic` | 一致 | [.out](week09/ReturnMaximum/tests/basic.out) | [.out](../week09/ReturnMaximum/tests/basic.out) |
| `ReturnMaximum/variant_best_zero` | 一致 | [.out](week09/ReturnMaximum/variants/tests/best_zero.out) | [.out](../week09/ReturnMaximum/variants/tests/best_zero.out) |
| `ReturnMaximum/variant_max_index` | 一致 | [.out](week09/ReturnMaximum/variants/tests/max_index.out) | [.out](../week09/ReturnMaximum/variants/tests/max_index.out) |
| `ReturnMaximum/variant_max_index_n0` | 一致 | [.out](week09/ReturnMaximum/variants/tests/max_index_n0.out) | [.out](../week09/ReturnMaximum/variants/tests/max_index_n0.out) |
| `ReturnMaximum/variant_max_index_negative` | 一致 | [.out](week09/ReturnMaximum/variants/tests/max_index_negative.out) | [.out](../week09/ReturnMaximum/variants/tests/max_index_negative.out) |
| `ReturnMaximum/variant_negative` | 一致 | [.out](week09/ReturnMaximum/variants/tests/negative.out) | [.out](../week09/ReturnMaximum/variants/tests/negative.out) |
| `ReturnMaximum/variant_pointer_n0` | 一致 | [.out](week09/ReturnMaximum/variants/tests/pointer_n0.out) | [.out](../week09/ReturnMaximum/variants/tests/pointer_n0.out) |
| `SwapRows/basic` | 一致 | [.out](week09/SwapRows/tests/basic.out) | [.out](../week09/SwapRows/tests/basic.out) |
| `SwapRows/variant_empty_fukui` | 一致 | [.out](week09/SwapRows/variants/tests/empty_fukui.out) | [.out](../week09/SwapRows/variants/tests/empty_fukui.out) |
| `SwapRows/variant_fukuiawa` | 一致 | [.out](week09/SwapRows/variants/tests/fukuiawa.out) | [.out](../week09/SwapRows/variants/tests/fukuiawa.out) |
| `SwapRows/variant_row_start` | 一致 | [.out](week09/SwapRows/variants/tests/row_start.out) | [.out](../week09/SwapRows/variants/tests/row_start.out) |
| `SwapRows/variant_same_row` | 一致 | [.out](week09/SwapRows/variants/tests/same_row.out) | [.out](../week09/SwapRows/variants/tests/same_row.out) |
| `SwapRows/variant_twice` | 一致 | [.out](week09/SwapRows/variants/tests/twice.out) | [.out](../week09/SwapRows/variants/tests/twice.out) |
| `SwapRows/variant_until_terminator` | 一致 | [.out](week09/SwapRows/variants/tests/until_terminator.out) | [.out](../week09/SwapRows/variants/tests/until_terminator.out) |

## week10

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `Arguments/all_three` | 一致 | [.out](week10/Arguments/tests/all_three.out) | [.out](../week10/Arguments/tests/all_three.out) |
| `Arguments/empty_and_fukui` | 一致 | [.out](week10/Arguments/tests/empty_and_fukui.out) | [.out](../week10/Arguments/tests/empty_and_fukui.out) |
| `Arguments/empty_arg` | 一致 | [.out](week10/Arguments/tests/empty_arg.out) | [.out](../week10/Arguments/tests/empty_arg.out) |
| `Arguments/fukui_ishikawa` | 一致 | [.out](week10/Arguments/tests/fukui_ishikawa.out) | [.out](../week10/Arguments/tests/fukui_ishikawa.out) |
| `Arguments/nagano_ishikawa` | 一致 | [.out](week10/Arguments/tests/nagano_ishikawa.out) | [.out](../week10/Arguments/tests/nagano_ishikawa.out) |
| `Arguments/no_args` | 一致 | [.out](week10/Arguments/tests/no_args.out) | [.out](../week10/Arguments/tests/no_args.out) |
| `Arguments/not_hokuriku` | 一致 | [.out](week10/Arguments/tests/not_hokuriku.out) | [.out](../week10/Arguments/tests/not_hokuriku.out) |
| `Arguments/prefix_only` | 一致 | [.out](week10/Arguments/tests/prefix_only.out) | [.out](../week10/Arguments/tests/prefix_only.out) |
| `Arguments/space_and_toyama` | 一致 | [.out](week10/Arguments/tests/space_and_toyama.out) | [.out](../week10/Arguments/tests/space_and_toyama.out) |
| `Arguments/space_in_arg` | 一致 | [.out](week10/Arguments/tests/space_in_arg.out) | [.out](../week10/Arguments/tests/space_in_arg.out) |
| `Arguments/toyama` | 一致 | [.out](week10/Arguments/tests/toyama.out) | [.out](../week10/Arguments/tests/toyama.out) |
| `Arguments/uppercase_toyama` | 一致 | [.out](week10/Arguments/tests/uppercase_toyama.out) | [.out](../week10/Arguments/tests/uppercase_toyama.out) |
| `Binary/basic` | 一致 | [.out](week10/Binary/tests/basic.out) [.files](week10/Binary/tests/basic.files) | [.out](../week10/Binary/tests/basic.out) |
| `Binary/overwrite` | 一致 | [.out](week10/Binary/tests/overwrite.out) [.files](week10/Binary/tests/overwrite.files) | [.out](../week10/Binary/tests/overwrite.out) |
| `Binary/variant_show_n` | 一致 | [.out](week10/Binary/variants/tests/show_n.out) [.files](week10/Binary/variants/tests/show_n.files) | [.out](../week10/Binary/variants/tests/show_n.out) |
| `Binary/variant_utf8_a` | 一致 | [.out](week10/Binary/variants/tests/utf8_a.out) [.files](week10/Binary/variants/tests/utf8_a.files) | [.out](../week10/Binary/variants/tests/utf8_a.out) |
| `ByteOrder/basic` | 一致 | [.out](week10/ByteOrder/tests/basic.out) | [.out](../week10/ByteOrder/tests/basic.out) |
| `ByteOrder/variant_bits_of_byte` | 一致 | [.out](week10/ByteOrder/variants/tests/bits_of_byte.out) | [.out](../week10/ByteOrder/variants/tests/bits_of_byte.out) |
| `ByteOrder/variant_value_0x1234` | 一致 | [.out](week10/ByteOrder/variants/tests/value_0x1234.out) | [.out](../week10/ByteOrder/variants/tests/value_0x1234.out) |
| `CheckValue/bad_abc_line` | 一致 | [.out](week10/CheckValue/tests/bad_abc_line.out) [.err](week10/CheckValue/tests/bad_abc_line.err) [.code](week10/CheckValue/tests/bad_abc_line.code) | [.out](../week10/CheckValue/tests/bad_abc_line.out) |
| `CheckValue/bad_after_found` | 一致 | [.out](week10/CheckValue/tests/bad_after_found.out) [.err](week10/CheckValue/tests/bad_after_found.err) [.code](week10/CheckValue/tests/bad_after_found.code) | [.out](../week10/CheckValue/tests/bad_after_found.out) |
| `CheckValue/bad_bom` | 一致 | [.out](week10/CheckValue/tests/bad_bom.out) [.err](week10/CheckValue/tests/bad_bom.err) [.code](week10/CheckValue/tests/bad_bom.code) | [.out](../week10/CheckValue/tests/bad_bom.out) |
| `CheckValue/bad_empty_file` | 一致 | [.out](week10/CheckValue/tests/bad_empty_file.out) [.err](week10/CheckValue/tests/bad_empty_file.err) [.code](week10/CheckValue/tests/bad_empty_file.code) | [.out](../week10/CheckValue/tests/bad_empty_file.out) |
| `CheckValue/bad_empty_line_inside` | 一致 | [.out](week10/CheckValue/tests/bad_empty_line_inside.out) [.err](week10/CheckValue/tests/bad_empty_line_inside.err) [.code](week10/CheckValue/tests/bad_empty_line_inside.code) | [.out](../week10/CheckValue/tests/bad_empty_line_inside.out) |
| `CheckValue/bad_extra_empty_line` | 一致 | [.out](week10/CheckValue/tests/bad_extra_empty_line.out) [.err](week10/CheckValue/tests/bad_extra_empty_line.err) [.code](week10/CheckValue/tests/bad_extra_empty_line.code) | [.out](../week10/CheckValue/tests/bad_extra_empty_line.out) |
| `CheckValue/bad_extra_number` | 一致 | [.out](week10/CheckValue/tests/bad_extra_number.out) [.err](week10/CheckValue/tests/bad_extra_number.err) [.code](week10/CheckValue/tests/bad_extra_number.code) | [.out](../week10/CheckValue/tests/bad_extra_number.out) |
| `CheckValue/bad_header_101` | 一致 | [.out](week10/CheckValue/tests/bad_header_101.out) [.err](week10/CheckValue/tests/bad_header_101.err) [.code](week10/CheckValue/tests/bad_header_101.code) | [.out](../week10/CheckValue/tests/bad_header_101.out) |
| `CheckValue/bad_header_12x` | 一致 | [.out](week10/CheckValue/tests/bad_header_12x.out) [.err](week10/CheckValue/tests/bad_header_12x.err) [.code](week10/CheckValue/tests/bad_header_12x.code) | [.out](../week10/CheckValue/tests/bad_header_12x.out) |
| `CheckValue/bad_header_negative` | 一致 | [.out](week10/CheckValue/tests/bad_header_negative.out) [.err](week10/CheckValue/tests/bad_header_negative.err) [.code](week10/CheckValue/tests/bad_header_negative.code) | [.out](../week10/CheckValue/tests/bad_header_negative.out) |
| `CheckValue/bad_line_31_bytes` | 一致 | [.out](week10/CheckValue/tests/bad_line_31_bytes.out) [.err](week10/CheckValue/tests/bad_line_31_bytes.err) [.code](week10/CheckValue/tests/bad_line_31_bytes.code) | [.out](../week10/CheckValue/tests/bad_line_31_bytes.out) |
| `CheckValue/bad_long_header` | 一致 | [.out](week10/CheckValue/tests/bad_long_header.out) [.err](week10/CheckValue/tests/bad_long_header.err) [.code](week10/CheckValue/tests/bad_long_header.code) | [.out](../week10/CheckValue/tests/bad_long_header.out) |
| `CheckValue/bad_missing_last` | 一致 | [.out](week10/CheckValue/tests/bad_missing_last.out) [.err](week10/CheckValue/tests/bad_missing_last.err) [.code](week10/CheckValue/tests/bad_missing_last.code) | [.out](../week10/CheckValue/tests/bad_missing_last.out) |
| `CheckValue/bad_spaces_only_line` | 一致 | [.out](week10/CheckValue/tests/bad_spaces_only_line.out) [.err](week10/CheckValue/tests/bad_spaces_only_line.err) [.code](week10/CheckValue/tests/bad_spaces_only_line.code) | [.out](../week10/CheckValue/tests/bad_spaces_only_line.out) |
| `CheckValue/bad_value_99999` | 一致 | [.out](week10/CheckValue/tests/bad_value_99999.out) [.err](week10/CheckValue/tests/bad_value_99999.err) [.code](week10/CheckValue/tests/bad_value_99999.code) | [.out](../week10/CheckValue/tests/bad_value_99999.out) |
| `CheckValue/crlf_file` | 一致 | [.out](week10/CheckValue/tests/crlf_file.out) | [.out](../week10/CheckValue/tests/crlf_file.out) |
| `CheckValue/empty_filename` | 一致 | [.out](week10/CheckValue/tests/empty_filename.out) [.err](week10/CheckValue/tests/empty_filename.err) [.code](week10/CheckValue/tests/empty_filename.code) | [.out](../week10/CheckValue/tests/empty_filename.out) |
| `CheckValue/found_9` | 一致 | [.out](week10/CheckValue/tests/found_9.out) | [.out](../week10/CheckValue/tests/found_9.out) |
| `CheckValue/found_first_0` | 一致 | [.out](week10/CheckValue/tests/found_first_0.out) | [.out](../week10/CheckValue/tests/found_first_0.out) |
| `CheckValue/header_is_not_data` | 一致 | [.out](week10/CheckValue/tests/header_is_not_data.out) | [.out](../week10/CheckValue/tests/header_is_not_data.out) |
| `CheckValue/line_30_bytes` | 一致 | [.out](week10/CheckValue/tests/line_30_bytes.out) | [.out](../week10/CheckValue/tests/line_30_bytes.out) |
| `CheckValue/missing_file` | 一致 | [.out](week10/CheckValue/tests/missing_file.out) [.err](week10/CheckValue/tests/missing_file.err) [.code](week10/CheckValue/tests/missing_file.code) | [.out](../week10/CheckValue/tests/missing_file.out) |
| `CheckValue/n_0_file` | 一致 | [.out](week10/CheckValue/tests/n_0_file.out) | [.out](../week10/CheckValue/tests/n_0_file.out) |
| `CheckValue/n_100_found_9801` | 一致 | [.out](week10/CheckValue/tests/n_100_found_9801.out) | [.out](../week10/CheckValue/tests/n_100_found_9801.out) |
| `CheckValue/n_100_not_found_9800` | 一致 | [.out](week10/CheckValue/tests/n_100_not_found_9800.out) | [.out](../week10/CheckValue/tests/n_100_not_found_9800.out) |
| `CheckValue/no_args` | 一致 | [.out](week10/CheckValue/tests/no_args.out) [.err](week10/CheckValue/tests/no_args.err) [.code](week10/CheckValue/tests/no_args.code) | [.out](../week10/CheckValue/tests/no_args.out) |
| `CheckValue/no_final_newline` | 一致 | [.out](week10/CheckValue/tests/no_final_newline.out) | [.out](../week10/CheckValue/tests/no_final_newline.out) |
| `CheckValue/not_found_12` | 一致 | [.out](week10/CheckValue/tests/not_found_12.out) | [.out](../week10/CheckValue/tests/not_found_12.out) |
| `CheckValue/not_squares_accepted` | 一致 | [.out](week10/CheckValue/tests/not_squares_accepted.out) | [.out](../week10/CheckValue/tests/not_squares_accepted.out) |
| `CheckValue/nul_not_checked` | 一致 | [.out](week10/CheckValue/tests/nul_not_checked.out) | [.out](../week10/CheckValue/tests/nul_not_checked.out) |
| `CheckValue/one_arg` | 一致 | [.out](week10/CheckValue/tests/one_arg.out) [.err](week10/CheckValue/tests/one_arg.err) [.code](week10/CheckValue/tests/one_arg.code) | [.out](../week10/CheckValue/tests/one_arg.out) |
| `CheckValue/space_in_name` | 一致 | [.out](week10/CheckValue/tests/space_in_name.out) | [.out](../week10/CheckValue/tests/space_in_name.out) |
| `CheckValue/spaces_around_values` | 一致 | [.out](week10/CheckValue/tests/spaces_around_values.out) | [.out](../week10/CheckValue/tests/spaces_around_values.out) |
| `CheckValue/target_12x` | 一致 | [.out](week10/CheckValue/tests/target_12x.out) [.err](week10/CheckValue/tests/target_12x.err) [.code](week10/CheckValue/tests/target_12x.code) | [.out](../week10/CheckValue/tests/target_12x.out) |
| `CheckValue/target_9802` | 一致 | [.out](week10/CheckValue/tests/target_9802.out) [.err](week10/CheckValue/tests/target_9802.err) [.code](week10/CheckValue/tests/target_9802.code) | [.out](../week10/CheckValue/tests/target_9802.out) |
| `CheckValue/target_negative_1` | 一致 | [.out](week10/CheckValue/tests/target_negative_1.out) [.err](week10/CheckValue/tests/target_negative_1.err) [.code](week10/CheckValue/tests/target_negative_1.code) | [.out](../week10/CheckValue/tests/target_negative_1.out) |
| `CheckValue/too_many_args` | 一致 | [.out](week10/CheckValue/tests/too_many_args.out) [.err](week10/CheckValue/tests/too_many_args.err) [.code](week10/CheckValue/tests/too_many_args.code) | [.out](../week10/CheckValue/tests/too_many_args.out) |
| `CheckValue/variant_store_values--bad_abc_line` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_abc_line.out) [.err](week10/CheckValue/variants/tests/store_values--bad_abc_line.err) [.code](week10/CheckValue/variants/tests/store_values--bad_abc_line.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_abc_line.out) |
| `CheckValue/variant_store_values--bad_after_found` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_after_found.out) [.err](week10/CheckValue/variants/tests/store_values--bad_after_found.err) [.code](week10/CheckValue/variants/tests/store_values--bad_after_found.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_after_found.out) |
| `CheckValue/variant_store_values--bad_bom` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_bom.out) [.err](week10/CheckValue/variants/tests/store_values--bad_bom.err) [.code](week10/CheckValue/variants/tests/store_values--bad_bom.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_bom.out) |
| `CheckValue/variant_store_values--bad_empty_file` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_empty_file.out) [.err](week10/CheckValue/variants/tests/store_values--bad_empty_file.err) [.code](week10/CheckValue/variants/tests/store_values--bad_empty_file.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_empty_file.out) |
| `CheckValue/variant_store_values--bad_empty_line_inside` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_empty_line_inside.out) [.err](week10/CheckValue/variants/tests/store_values--bad_empty_line_inside.err) [.code](week10/CheckValue/variants/tests/store_values--bad_empty_line_inside.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_empty_line_inside.out) |
| `CheckValue/variant_store_values--bad_extra_empty_line` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_extra_empty_line.out) [.err](week10/CheckValue/variants/tests/store_values--bad_extra_empty_line.err) [.code](week10/CheckValue/variants/tests/store_values--bad_extra_empty_line.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_extra_empty_line.out) |
| `CheckValue/variant_store_values--bad_extra_number` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_extra_number.out) [.err](week10/CheckValue/variants/tests/store_values--bad_extra_number.err) [.code](week10/CheckValue/variants/tests/store_values--bad_extra_number.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_extra_number.out) |
| `CheckValue/variant_store_values--bad_header_101` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_header_101.out) [.err](week10/CheckValue/variants/tests/store_values--bad_header_101.err) [.code](week10/CheckValue/variants/tests/store_values--bad_header_101.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_header_101.out) |
| `CheckValue/variant_store_values--bad_header_12x` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_header_12x.out) [.err](week10/CheckValue/variants/tests/store_values--bad_header_12x.err) [.code](week10/CheckValue/variants/tests/store_values--bad_header_12x.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_header_12x.out) |
| `CheckValue/variant_store_values--bad_header_negative` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_header_negative.out) [.err](week10/CheckValue/variants/tests/store_values--bad_header_negative.err) [.code](week10/CheckValue/variants/tests/store_values--bad_header_negative.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_header_negative.out) |
| `CheckValue/variant_store_values--bad_line_31_bytes` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_line_31_bytes.out) [.err](week10/CheckValue/variants/tests/store_values--bad_line_31_bytes.err) [.code](week10/CheckValue/variants/tests/store_values--bad_line_31_bytes.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_line_31_bytes.out) |
| `CheckValue/variant_store_values--bad_long_header` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_long_header.out) [.err](week10/CheckValue/variants/tests/store_values--bad_long_header.err) [.code](week10/CheckValue/variants/tests/store_values--bad_long_header.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_long_header.out) |
| `CheckValue/variant_store_values--bad_missing_last` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_missing_last.out) [.err](week10/CheckValue/variants/tests/store_values--bad_missing_last.err) [.code](week10/CheckValue/variants/tests/store_values--bad_missing_last.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_missing_last.out) |
| `CheckValue/variant_store_values--bad_spaces_only_line` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_spaces_only_line.out) [.err](week10/CheckValue/variants/tests/store_values--bad_spaces_only_line.err) [.code](week10/CheckValue/variants/tests/store_values--bad_spaces_only_line.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_spaces_only_line.out) |
| `CheckValue/variant_store_values--bad_value_99999` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--bad_value_99999.out) [.err](week10/CheckValue/variants/tests/store_values--bad_value_99999.err) [.code](week10/CheckValue/variants/tests/store_values--bad_value_99999.code) | [.out](../week10/CheckValue/variants/tests/store_values--bad_value_99999.out) |
| `CheckValue/variant_store_values--crlf_file` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--crlf_file.out) | [.out](../week10/CheckValue/variants/tests/store_values--crlf_file.out) |
| `CheckValue/variant_store_values--empty_filename` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--empty_filename.out) [.err](week10/CheckValue/variants/tests/store_values--empty_filename.err) [.code](week10/CheckValue/variants/tests/store_values--empty_filename.code) | [.out](../week10/CheckValue/variants/tests/store_values--empty_filename.out) |
| `CheckValue/variant_store_values--found_9` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--found_9.out) | [.out](../week10/CheckValue/variants/tests/store_values--found_9.out) |
| `CheckValue/variant_store_values--found_first_0` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--found_first_0.out) | [.out](../week10/CheckValue/variants/tests/store_values--found_first_0.out) |
| `CheckValue/variant_store_values--header_is_not_data` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--header_is_not_data.out) | [.out](../week10/CheckValue/variants/tests/store_values--header_is_not_data.out) |
| `CheckValue/variant_store_values--line_30_bytes` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--line_30_bytes.out) | [.out](../week10/CheckValue/variants/tests/store_values--line_30_bytes.out) |
| `CheckValue/variant_store_values--missing_file` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--missing_file.out) [.err](week10/CheckValue/variants/tests/store_values--missing_file.err) [.code](week10/CheckValue/variants/tests/store_values--missing_file.code) | [.out](../week10/CheckValue/variants/tests/store_values--missing_file.out) |
| `CheckValue/variant_store_values--n_0_file` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--n_0_file.out) | [.out](../week10/CheckValue/variants/tests/store_values--n_0_file.out) |
| `CheckValue/variant_store_values--n_100_found_9801` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--n_100_found_9801.out) | [.out](../week10/CheckValue/variants/tests/store_values--n_100_found_9801.out) |
| `CheckValue/variant_store_values--n_100_not_found_9800` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--n_100_not_found_9800.out) | [.out](../week10/CheckValue/variants/tests/store_values--n_100_not_found_9800.out) |
| `CheckValue/variant_store_values--no_args` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--no_args.out) [.err](week10/CheckValue/variants/tests/store_values--no_args.err) [.code](week10/CheckValue/variants/tests/store_values--no_args.code) | [.out](../week10/CheckValue/variants/tests/store_values--no_args.out) |
| `CheckValue/variant_store_values--no_final_newline` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--no_final_newline.out) | [.out](../week10/CheckValue/variants/tests/store_values--no_final_newline.out) |
| `CheckValue/variant_store_values--not_found_12` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--not_found_12.out) | [.out](../week10/CheckValue/variants/tests/store_values--not_found_12.out) |
| `CheckValue/variant_store_values--not_squares_accepted` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--not_squares_accepted.out) | [.out](../week10/CheckValue/variants/tests/store_values--not_squares_accepted.out) |
| `CheckValue/variant_store_values--nul_not_checked` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--nul_not_checked.out) | [.out](../week10/CheckValue/variants/tests/store_values--nul_not_checked.out) |
| `CheckValue/variant_store_values--one_arg` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--one_arg.out) [.err](week10/CheckValue/variants/tests/store_values--one_arg.err) [.code](week10/CheckValue/variants/tests/store_values--one_arg.code) | [.out](../week10/CheckValue/variants/tests/store_values--one_arg.out) |
| `CheckValue/variant_store_values--space_in_name` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--space_in_name.out) | [.out](../week10/CheckValue/variants/tests/store_values--space_in_name.out) |
| `CheckValue/variant_store_values--spaces_around_values` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--spaces_around_values.out) | [.out](../week10/CheckValue/variants/tests/store_values--spaces_around_values.out) |
| `CheckValue/variant_store_values--target_12x` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--target_12x.out) [.err](week10/CheckValue/variants/tests/store_values--target_12x.err) [.code](week10/CheckValue/variants/tests/store_values--target_12x.code) | [.out](../week10/CheckValue/variants/tests/store_values--target_12x.out) |
| `CheckValue/variant_store_values--target_9802` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--target_9802.out) [.err](week10/CheckValue/variants/tests/store_values--target_9802.err) [.code](week10/CheckValue/variants/tests/store_values--target_9802.code) | [.out](../week10/CheckValue/variants/tests/store_values--target_9802.out) |
| `CheckValue/variant_store_values--target_negative_1` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--target_negative_1.out) [.err](week10/CheckValue/variants/tests/store_values--target_negative_1.err) [.code](week10/CheckValue/variants/tests/store_values--target_negative_1.code) | [.out](../week10/CheckValue/variants/tests/store_values--target_negative_1.out) |
| `CheckValue/variant_store_values--too_many_args` | 一致 | [.out](week10/CheckValue/variants/tests/store_values--too_many_args.out) [.err](week10/CheckValue/variants/tests/store_values--too_many_args.err) [.code](week10/CheckValue/variants/tests/store_values--too_many_args.code) | [.out](../week10/CheckValue/variants/tests/store_values--too_many_args.out) |
| `LineLengths/a31_newline` | 一致 | [.out](week10/LineLengths/tests/a31_newline.out) | [.out](../week10/LineLengths/tests/a31_newline.out) |
| `LineLengths/a31_no_newline` | 一致 | [.out](week10/LineLengths/tests/a31_no_newline.out) | [.out](../week10/LineLengths/tests/a31_no_newline.out) |
| `LineLengths/a32_newline` | 一致 | [.out](week10/LineLengths/tests/a32_newline.out) [.err](week10/LineLengths/tests/a32_newline.err) [.code](week10/LineLengths/tests/a32_newline.code) | [.out](../week10/LineLengths/tests/a32_newline.out) |
| `LineLengths/a32_no_newline` | 一致 | [.out](week10/LineLengths/tests/a32_no_newline.out) [.err](week10/LineLengths/tests/a32_no_newline.err) [.code](week10/LineLengths/tests/a32_no_newline.code) | [.out](../week10/LineLengths/tests/a32_no_newline.out) |
| `LineLengths/abc_newline` | 一致 | [.out](week10/LineLengths/tests/abc_newline.out) | [.out](../week10/LineLengths/tests/abc_newline.out) |
| `LineLengths/abc_no_newline` | 一致 | [.out](week10/LineLengths/tests/abc_no_newline.out) | [.out](../week10/LineLengths/tests/abc_no_newline.out) |
| `LineLengths/basic` | 一致 | [.out](week10/LineLengths/tests/basic.out) | [.out](../week10/LineLengths/tests/basic.out) |
| `LineLengths/empty_file` | 一致 | [.out](week10/LineLengths/tests/empty_file.out) | [.out](../week10/LineLengths/tests/empty_file.out) |
| `LineLengths/empty_line` | 一致 | [.out](week10/LineLengths/tests/empty_line.out) | [.out](../week10/LineLengths/tests/empty_line.out) |
| `LineLengths/missing_file` | 一致 | [.out](week10/LineLengths/tests/missing_file.out) [.err](week10/LineLengths/tests/missing_file.err) [.code](week10/LineLengths/tests/missing_file.code) | [.out](../week10/LineLengths/tests/missing_file.out) |
| `LineLengths/mixed` | 一致 | [.out](week10/LineLengths/tests/mixed.out) | [.out](../week10/LineLengths/tests/mixed.out) |
| `LineLengths/no_args` | 一致 | [.out](week10/LineLengths/tests/no_args.out) [.err](week10/LineLengths/tests/no_args.err) [.code](week10/LineLengths/tests/no_args.code) | [.out](../week10/LineLengths/tests/no_args.out) |
| `LineLengths/too_long_after_line` | 一致 | [.out](week10/LineLengths/tests/too_long_after_line.out) [.err](week10/LineLengths/tests/too_long_after_line.err) [.code](week10/LineLengths/tests/too_long_after_line.code) | [.out](../week10/LineLengths/tests/too_long_after_line.out) |
| `LineLengths/variant_count_chars--a31_newline` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--a31_newline.out) | [.out](../week10/LineLengths/variants/tests/count_chars--a31_newline.out) |
| `LineLengths/variant_count_chars--a31_no_newline` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--a31_no_newline.out) | [.out](../week10/LineLengths/variants/tests/count_chars--a31_no_newline.out) |
| `LineLengths/variant_count_chars--a32_newline` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--a32_newline.out) [.err](week10/LineLengths/variants/tests/count_chars--a32_newline.err) [.code](week10/LineLengths/variants/tests/count_chars--a32_newline.code) | [.out](../week10/LineLengths/variants/tests/count_chars--a32_newline.out) |
| `LineLengths/variant_count_chars--a32_no_newline` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--a32_no_newline.out) [.err](week10/LineLengths/variants/tests/count_chars--a32_no_newline.err) [.code](week10/LineLengths/variants/tests/count_chars--a32_no_newline.code) | [.out](../week10/LineLengths/variants/tests/count_chars--a32_no_newline.out) |
| `LineLengths/variant_count_chars--abc_newline` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--abc_newline.out) | [.out](../week10/LineLengths/variants/tests/count_chars--abc_newline.out) |
| `LineLengths/variant_count_chars--abc_no_newline` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--abc_no_newline.out) | [.out](../week10/LineLengths/variants/tests/count_chars--abc_no_newline.out) |
| `LineLengths/variant_count_chars--basic` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--basic.out) | [.out](../week10/LineLengths/variants/tests/count_chars--basic.out) |
| `LineLengths/variant_count_chars--empty_file` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--empty_file.out) | [.out](../week10/LineLengths/variants/tests/count_chars--empty_file.out) |
| `LineLengths/variant_count_chars--empty_line` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--empty_line.out) | [.out](../week10/LineLengths/variants/tests/count_chars--empty_line.out) |
| `LineLengths/variant_count_chars--missing_file` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--missing_file.out) [.err](week10/LineLengths/variants/tests/count_chars--missing_file.err) [.code](week10/LineLengths/variants/tests/count_chars--missing_file.code) | [.out](../week10/LineLengths/variants/tests/count_chars--missing_file.out) |
| `LineLengths/variant_count_chars--mixed` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--mixed.out) | [.out](../week10/LineLengths/variants/tests/count_chars--mixed.out) |
| `LineLengths/variant_count_chars--no_args` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--no_args.out) [.err](week10/LineLengths/variants/tests/count_chars--no_args.err) [.code](week10/LineLengths/variants/tests/count_chars--no_args.code) | [.out](../week10/LineLengths/variants/tests/count_chars--no_args.out) |
| `LineLengths/variant_count_chars--too_long_after_line` | 一致 | [.out](week10/LineLengths/variants/tests/count_chars--too_long_after_line.out) [.err](week10/LineLengths/variants/tests/count_chars--too_long_after_line.err) [.code](week10/LineLengths/variants/tests/count_chars--too_long_after_line.code) | [.out](../week10/LineLengths/variants/tests/count_chars--too_long_after_line.out) |
| `NumberFormats/basic` | 一致 | [.out](week10/NumberFormats/tests/basic.out) [.files](week10/NumberFormats/tests/basic.files) | [.out](../week10/NumberFormats/tests/basic.out) |
| `NumberFormats/overwrite` | 一致 | [.out](week10/NumberFormats/tests/overwrite.out) [.files](week10/NumberFormats/tests/overwrite.files) | [.out](../week10/NumberFormats/tests/overwrite.out) |
| `NumberFormats/variant_precision_0125` | 一致 | [.out](week10/NumberFormats/variants/tests/precision_0125.out) [.files](week10/NumberFormats/variants/tests/precision_0125.files) | [.out](../week10/NumberFormats/variants/tests/precision_0125.out) |
| `ParseNumber/boundary_100` | 一致 | [.out](week10/ParseNumber/tests/boundary_100.out) | [.out](../week10/ParseNumber/tests/boundary_100.out) |
| `ParseNumber/boundary_101` | 一致 | [.out](week10/ParseNumber/tests/boundary_101.out) [.err](week10/ParseNumber/tests/boundary_101.err) [.code](week10/ParseNumber/tests/boundary_101.code) | [.out](../week10/ParseNumber/tests/boundary_101.out) |
| `ParseNumber/empty_arg` | 一致 | [.out](week10/ParseNumber/tests/empty_arg.out) [.err](week10/ParseNumber/tests/empty_arg.err) [.code](week10/ParseNumber/tests/empty_arg.code) | [.out](../week10/ParseNumber/tests/empty_arg.out) |
| `ParseNumber/leading_space` | 一致 | [.out](week10/ParseNumber/tests/leading_space.out) | [.out](../week10/ParseNumber/tests/leading_space.out) |
| `ParseNumber/letters_abc` | 一致 | [.out](week10/ParseNumber/tests/letters_abc.out) [.err](week10/ParseNumber/tests/letters_abc.err) [.code](week10/ParseNumber/tests/letters_abc.code) | [.out](../week10/ParseNumber/tests/letters_abc.out) |
| `ParseNumber/negative_1` | 一致 | [.out](week10/ParseNumber/tests/negative_1.out) [.err](week10/ParseNumber/tests/negative_1.err) [.code](week10/ParseNumber/tests/negative_1.code) | [.out](../week10/ParseNumber/tests/negative_1.out) |
| `ParseNumber/no_args` | 一致 | [.out](week10/ParseNumber/tests/no_args.out) [.err](week10/ParseNumber/tests/no_args.err) [.code](week10/ParseNumber/tests/no_args.code) | [.out](../week10/ParseNumber/tests/no_args.out) |
| `ParseNumber/plus_42` | 一致 | [.out](week10/ParseNumber/tests/plus_42.out) | [.out](../week10/ParseNumber/tests/plus_42.out) |
| `ParseNumber/ten_digits` | 一致 | [.out](week10/ParseNumber/tests/ten_digits.out) [.err](week10/ParseNumber/tests/ten_digits.err) [.code](week10/ParseNumber/tests/ten_digits.code) | [.out](../week10/ParseNumber/tests/ten_digits.out) |
| `ParseNumber/too_many_args` | 一致 | [.out](week10/ParseNumber/tests/too_many_args.out) [.err](week10/ParseNumber/tests/too_many_args.err) [.code](week10/ParseNumber/tests/too_many_args.code) | [.out](../week10/ParseNumber/tests/too_many_args.out) |
| `ParseNumber/trailing_space` | 一致 | [.out](week10/ParseNumber/tests/trailing_space.out) [.err](week10/ParseNumber/tests/trailing_space.err) [.code](week10/ParseNumber/tests/trailing_space.code) | [.out](../week10/ParseNumber/tests/trailing_space.out) |
| `ParseNumber/trailing_x` | 一致 | [.out](week10/ParseNumber/tests/trailing_x.out) [.err](week10/ParseNumber/tests/trailing_x.err) [.code](week10/ParseNumber/tests/trailing_x.code) | [.out](../week10/ParseNumber/tests/trailing_x.out) |
| `ParseNumber/value_42` | 一致 | [.out](week10/ParseNumber/tests/value_42.out) | [.out](../week10/ParseNumber/tests/value_42.out) |
| `ParseNumber/variant_sum--eleven_values` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--eleven_values.out) [.err](week10/ParseNumber/variants/tests/sum--eleven_values.err) [.code](week10/ParseNumber/variants/tests/sum--eleven_values.code) | [.out](../week10/ParseNumber/variants/tests/sum--eleven_values.out) |
| `ParseNumber/variant_sum--empty_arg` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--empty_arg.out) [.err](week10/ParseNumber/variants/tests/sum--empty_arg.err) [.code](week10/ParseNumber/variants/tests/sum--empty_arg.code) | [.out](../week10/ParseNumber/variants/tests/sum--empty_arg.out) |
| `ParseNumber/variant_sum--invalid_middle` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--invalid_middle.out) [.err](week10/ParseNumber/variants/tests/sum--invalid_middle.err) [.code](week10/ParseNumber/variants/tests/sum--invalid_middle.code) | [.out](../week10/ParseNumber/variants/tests/sum--invalid_middle.out) |
| `ParseNumber/variant_sum--negative_1` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--negative_1.out) [.err](week10/ParseNumber/variants/tests/sum--negative_1.err) [.code](week10/ParseNumber/variants/tests/sum--negative_1.code) | [.out](../week10/ParseNumber/variants/tests/sum--negative_1.out) |
| `ParseNumber/variant_sum--no_args` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--no_args.out) [.err](week10/ParseNumber/variants/tests/sum--no_args.err) [.code](week10/ParseNumber/variants/tests/sum--no_args.code) | [.out](../week10/ParseNumber/variants/tests/sum--no_args.out) |
| `ParseNumber/variant_sum--one_value` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--one_value.out) | [.out](../week10/ParseNumber/variants/tests/sum--one_value.out) |
| `ParseNumber/variant_sum--out_of_range_101` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--out_of_range_101.out) [.err](week10/ParseNumber/variants/tests/sum--out_of_range_101.err) [.code](week10/ParseNumber/variants/tests/sum--out_of_range_101.code) | [.out](../week10/ParseNumber/variants/tests/sum--out_of_range_101.out) |
| `ParseNumber/variant_sum--sum_0_100` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--sum_0_100.out) | [.out](../week10/ParseNumber/variants/tests/sum--sum_0_100.out) |
| `ParseNumber/variant_sum--sum_12_23_34` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--sum_12_23_34.out) | [.out](../week10/ParseNumber/variants/tests/sum--sum_12_23_34.out) |
| `ParseNumber/variant_sum--ten_values_max` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--ten_values_max.out) | [.out](../week10/ParseNumber/variants/tests/sum--ten_values_max.out) |
| `ParseNumber/variant_sum--trailing_x` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--trailing_x.out) [.err](week10/ParseNumber/variants/tests/sum--trailing_x.err) [.code](week10/ParseNumber/variants/tests/sum--trailing_x.code) | [.out](../week10/ParseNumber/variants/tests/sum--trailing_x.out) |
| `ParseNumber/variant_sum--two_values` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--two_values.out) | [.out](../week10/ParseNumber/variants/tests/sum--two_values.out) |
| `ParseNumber/variant_sum--very_long` | 一致 | [.out](week10/ParseNumber/variants/tests/sum--very_long.out) [.err](week10/ParseNumber/variants/tests/sum--very_long.err) [.code](week10/ParseNumber/variants/tests/sum--very_long.code) | [.out](../week10/ParseNumber/variants/tests/sum--very_long.out) |
| `ParseNumber/very_long` | 一致 | [.out](week10/ParseNumber/tests/very_long.out) [.err](week10/ParseNumber/tests/very_long.err) [.code](week10/ParseNumber/tests/very_long.code) | [.out](../week10/ParseNumber/tests/very_long.out) |
| `ParseNumber/very_long_negative` | 一致 | [.out](week10/ParseNumber/tests/very_long_negative.out) [.err](week10/ParseNumber/tests/very_long_negative.err) [.code](week10/ParseNumber/tests/very_long_negative.code) | [.out](../week10/ParseNumber/tests/very_long_negative.out) |
| `ParseNumber/zero` | 一致 | [.out](week10/ParseNumber/tests/zero.out) | [.out](../week10/ParseNumber/tests/zero.out) |
| `ReadText/basic` | 一致 | [.out](week10/ReadText/tests/basic.out) | [.out](../week10/ReadText/tests/basic.out) |
| `ReadText/empty_arg` | 一致 | [.out](week10/ReadText/tests/empty_arg.out) [.err](week10/ReadText/tests/empty_arg.err) [.code](week10/ReadText/tests/empty_arg.code) | [.out](../week10/ReadText/tests/empty_arg.out) |
| `ReadText/empty_file` | 一致 | [.out](week10/ReadText/tests/empty_file.out) | [.out](../week10/ReadText/tests/empty_file.out) |
| `ReadText/missing_file` | 一致 | [.out](week10/ReadText/tests/missing_file.out) [.err](week10/ReadText/tests/missing_file.err) [.code](week10/ReadText/tests/missing_file.code) | [.out](../week10/ReadText/tests/missing_file.out) |
| `ReadText/no_args` | 一致 | [.out](week10/ReadText/tests/no_args.out) [.err](week10/ReadText/tests/no_args.err) [.code](week10/ReadText/tests/no_args.code) | [.out](../week10/ReadText/tests/no_args.out) |
| `ReadText/no_final_newline` | 一致 | [.out](week10/ReadText/tests/no_final_newline.out) | [.out](../week10/ReadText/tests/no_final_newline.out) |
| `ReadText/read_scores` | 一致 | [.out](week10/ReadText/tests/read_scores.out) | [.out](../week10/ReadText/tests/read_scores.out) |
| `ReadText/space_in_name` | 一致 | [.out](week10/ReadText/tests/space_in_name.out) | [.out](../week10/ReadText/tests/space_in_name.out) |
| `ReadText/space_unquoted` | 一致 | [.out](week10/ReadText/tests/space_unquoted.out) [.err](week10/ReadText/tests/space_unquoted.err) [.code](week10/ReadText/tests/space_unquoted.code) | [.out](../week10/ReadText/tests/space_unquoted.out) |
| `ReadText/variant_read_lines--basic` | 一致 | [.out](week10/ReadText/variants/tests/read_lines--basic.out) | [.out](../week10/ReadText/variants/tests/read_lines--basic.out) |
| `ReadText/variant_read_lines--empty_arg` | 一致 | [.out](week10/ReadText/variants/tests/read_lines--empty_arg.out) [.err](week10/ReadText/variants/tests/read_lines--empty_arg.err) [.code](week10/ReadText/variants/tests/read_lines--empty_arg.code) | [.out](../week10/ReadText/variants/tests/read_lines--empty_arg.out) |
| `ReadText/variant_read_lines--empty_file` | 一致 | [.out](week10/ReadText/variants/tests/read_lines--empty_file.out) | [.out](../week10/ReadText/variants/tests/read_lines--empty_file.out) |
| `ReadText/variant_read_lines--missing_file` | 一致 | [.out](week10/ReadText/variants/tests/read_lines--missing_file.out) [.err](week10/ReadText/variants/tests/read_lines--missing_file.err) [.code](week10/ReadText/variants/tests/read_lines--missing_file.code) | [.out](../week10/ReadText/variants/tests/read_lines--missing_file.out) |
| `ReadText/variant_read_lines--no_args` | 一致 | [.out](week10/ReadText/variants/tests/read_lines--no_args.out) [.err](week10/ReadText/variants/tests/read_lines--no_args.err) [.code](week10/ReadText/variants/tests/read_lines--no_args.code) | [.out](../week10/ReadText/variants/tests/read_lines--no_args.out) |
| `ReadText/variant_read_lines--no_final_newline` | 一致 | [.out](week10/ReadText/variants/tests/read_lines--no_final_newline.out) | [.out](../week10/ReadText/variants/tests/read_lines--no_final_newline.out) |
| `ReadText/variant_read_lines--read_scores` | 一致 | [.out](week10/ReadText/variants/tests/read_lines--read_scores.out) | [.out](../week10/ReadText/variants/tests/read_lines--read_scores.out) |
| `ReadText/variant_read_lines--space_in_name` | 一致 | [.out](week10/ReadText/variants/tests/read_lines--space_in_name.out) | [.out](../week10/ReadText/variants/tests/read_lines--space_in_name.out) |
| `ReadText/variant_read_lines--space_unquoted` | 一致 | [.out](week10/ReadText/variants/tests/read_lines--space_unquoted.out) [.err](week10/ReadText/variants/tests/read_lines--space_unquoted.err) [.code](week10/ReadText/variants/tests/read_lines--space_unquoted.code) | [.out](../week10/ReadText/variants/tests/read_lines--space_unquoted.out) |
| `WriteSquares/empty_filename` | 一致 | [.out](week10/WriteSquares/tests/empty_filename.out) [.err](week10/WriteSquares/tests/empty_filename.err) [.code](week10/WriteSquares/tests/empty_filename.code) | [.out](../week10/WriteSquares/tests/empty_filename.out) |
| `WriteSquares/existing_file` | 一致 | [.out](week10/WriteSquares/tests/existing_file.out) [.err](week10/WriteSquares/tests/existing_file.err) [.code](week10/WriteSquares/tests/existing_file.code) [.files](week10/WriteSquares/tests/existing_file.files) | [.out](../week10/WriteSquares/tests/existing_file.out) |
| `WriteSquares/n_0` | 一致 | [.out](week10/WriteSquares/tests/n_0.out) [.files](week10/WriteSquares/tests/n_0.files) | [.out](../week10/WriteSquares/tests/n_0.out) |
| `WriteSquares/n_100` | 一致 | [.out](week10/WriteSquares/tests/n_100.out) [.files](week10/WriteSquares/tests/n_100.files) | [.out](../week10/WriteSquares/tests/n_100.out) |
| `WriteSquares/n_101` | 一致 | [.out](week10/WriteSquares/tests/n_101.out) [.err](week10/WriteSquares/tests/n_101.err) [.code](week10/WriteSquares/tests/n_101.code) | [.out](../week10/WriteSquares/tests/n_101.out) |
| `WriteSquares/n_12x` | 一致 | [.out](week10/WriteSquares/tests/n_12x.out) [.err](week10/WriteSquares/tests/n_12x.err) [.code](week10/WriteSquares/tests/n_12x.code) | [.out](../week10/WriteSquares/tests/n_12x.out) |
| `WriteSquares/n_4` | 一致 | [.out](week10/WriteSquares/tests/n_4.out) [.files](week10/WriteSquares/tests/n_4.files) | [.out](../week10/WriteSquares/tests/n_4.out) |
| `WriteSquares/n_negative_1` | 一致 | [.out](week10/WriteSquares/tests/n_negative_1.out) [.err](week10/WriteSquares/tests/n_negative_1.err) [.code](week10/WriteSquares/tests/n_negative_1.code) | [.out](../week10/WriteSquares/tests/n_negative_1.out) |
| `WriteSquares/n_very_long` | 一致 | [.out](week10/WriteSquares/tests/n_very_long.out) [.err](week10/WriteSquares/tests/n_very_long.err) [.code](week10/WriteSquares/tests/n_very_long.code) | [.out](../week10/WriteSquares/tests/n_very_long.out) |
| `WriteSquares/no_args` | 一致 | [.out](week10/WriteSquares/tests/no_args.out) [.err](week10/WriteSquares/tests/no_args.err) [.code](week10/WriteSquares/tests/no_args.code) | [.out](../week10/WriteSquares/tests/no_args.out) |
| `WriteSquares/one_arg` | 一致 | [.out](week10/WriteSquares/tests/one_arg.out) [.err](week10/WriteSquares/tests/one_arg.err) [.code](week10/WriteSquares/tests/one_arg.code) | [.out](../week10/WriteSquares/tests/one_arg.out) |
| `WriteSquares/space_in_name` | 一致 | [.out](week10/WriteSquares/tests/space_in_name.out) [.files](week10/WriteSquares/tests/space_in_name.files) | [.out](../week10/WriteSquares/tests/space_in_name.out) |
| `WriteSquares/too_many_args` | 一致 | [.out](week10/WriteSquares/tests/too_many_args.out) [.err](week10/WriteSquares/tests/too_many_args.err) [.code](week10/WriteSquares/tests/too_many_args.code) | [.out](../week10/WriteSquares/tests/too_many_args.out) |
| `WriteSquares/unused_name` | 一致 | [.out](week10/WriteSquares/tests/unused_name.out) [.files](week10/WriteSquares/tests/unused_name.files) | [.out](../week10/WriteSquares/tests/unused_name.out) |
| `WriteText/new_file` | 一致 | [.out](week10/WriteText/tests/new_file.out) [.files](week10/WriteText/tests/new_file.files) | [.out](../week10/WriteText/tests/new_file.out) |
| `WriteText/overwrite_3_lines` | 一致 | [.out](week10/WriteText/tests/overwrite_3_lines.out) [.files](week10/WriteText/tests/overwrite_3_lines.files) | [.out](../week10/WriteText/tests/overwrite_3_lines.out) |
| `WriteText/overwrite_other` | 一致 | [.out](week10/WriteText/tests/overwrite_other.out) [.files](week10/WriteText/tests/overwrite_other.files) | [.out](../week10/WriteText/tests/overwrite_other.out) |
| `WriteText/variant_mode_a--append_to_3_lines` | 一致 | [.out](week10/WriteText/variants/tests/mode_a--append_to_3_lines.out) [.files](week10/WriteText/variants/tests/mode_a--append_to_3_lines.files) | [.out](../week10/WriteText/variants/tests/mode_a--append_to_3_lines.out) |
| `WriteText/variant_mode_a--append_to_6_lines` | 一致 | [.out](week10/WriteText/variants/tests/mode_a--append_to_6_lines.out) [.files](week10/WriteText/variants/tests/mode_a--append_to_6_lines.files) | [.out](../week10/WriteText/variants/tests/mode_a--append_to_6_lines.out) |
| `WriteText/variant_mode_a--new_file` | 一致 | [.out](week10/WriteText/variants/tests/mode_a--new_file.out) [.files](week10/WriteText/variants/tests/mode_a--new_file.files) | [.out](../week10/WriteText/variants/tests/mode_a--new_file.out) |
| `WriteText/variant_mode_wx--existing_file` | 一致 | [.out](week10/WriteText/variants/tests/mode_wx--existing_file.out) [.err](week10/WriteText/variants/tests/mode_wx--existing_file.err) [.code](week10/WriteText/variants/tests/mode_wx--existing_file.code) [.files](week10/WriteText/variants/tests/mode_wx--existing_file.files) | [.out](../week10/WriteText/variants/tests/mode_wx--existing_file.out) |
| `WriteText/variant_mode_wx--new_file` | 一致 | [.out](week10/WriteText/variants/tests/mode_wx--new_file.out) [.files](week10/WriteText/variants/tests/mode_wx--new_file.files) | [.out](../week10/WriteText/variants/tests/mode_wx--new_file.out) |

## week11

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `CopyMembers/basic` | 一致 | [.out](week11/CopyMembers/tests/basic.out) | [.out](../week11/CopyMembers/tests/basic.out) |
| `CopyMembers/variant_replace_fuga` | 一致 | [.out](week11/CopyMembers/variants/tests/replace_fuga.out) | [.out](../week11/CopyMembers/variants/tests/replace_fuga.out) |
| `PointInit/basic` | 一致 | [.out](week11/PointInit/tests/basic.out) | [.out](../week11/PointInit/tests/basic.out) |
| `PointInit/variant_positional` | 一致 | [.out](week11/PointInit/variants/tests/positional.out) | [.out](../week11/PointInit/variants/tests/positional.out) |
| `PointInit/variant_untagged` | 一致 | [.out](week11/PointInit/variants/tests/untagged.out) | [.out](../week11/PointInit/variants/tests/untagged.out) |
| `PointMove/basic` | 一致 | [.out](week11/PointMove/tests/basic.out) | [.out](../week11/PointMove/tests/basic.out) |
| `PointMove/variant_b_x_100` | 一致 | [.out](week11/PointMove/variants/tests/b_x_100.out) | [.out](../week11/PointMove/variants/tests/b_x_100.out) |
| `PointMove/variant_call_assign` | 一致 | [.out](week11/PointMove/variants/tests/call_assign.out) | [.out](../week11/PointMove/variants/tests/call_assign.out) |
| `PointMove/variant_call_discard` | 一致 | [.out](week11/PointMove/variants/tests/call_discard.out) | [.out](../week11/PointMove/variants/tests/call_discard.out) |
| `PointMove/variant_call_in_place` | 一致 | [.out](week11/PointMove/variants/tests/call_in_place.out) | [.out](../week11/PointMove/variants/tests/call_in_place.out) |
| `PointMove/variant_move_0_0` | 一致 | [.out](week11/PointMove/variants/tests/move_0_0.out) | [.out](../week11/PointMove/variants/tests/move_0_0.out) |
| `PointMove/variant_move_2_3` | 一致 | [.out](week11/PointMove/variants/tests/move_2_3.out) | [.out](../week11/PointMove/variants/tests/move_2_3.out) |
| `PointMove/variant_move_m1_m2` | 一致 | [.out](week11/PointMove/variants/tests/move_m1_m2.out) | [.out](../week11/PointMove/variants/tests/move_m1_m2.out) |
| `Rect/basic` | 一致 | [.out](week11/Rect/tests/basic.out) | [.out](../week11/Rect/tests/basic.out) |
| `Rect/variant_name_20` | 一致 | [.out](week11/Rect/variants/tests/name_20.out) | [.out](../week11/Rect/variants/tests/name_20.out) |
| `Rect/variant_name_21` | 一致 | [.out](week11/Rect/variants/tests/name_21.out) [.err](week11/Rect/variants/tests/name_21.err) [.code](week11/Rect/variants/tests/name_21.code) | [.out](../week11/Rect/variants/tests/name_21.out) |
| `Rect/variant_negative_coords` | 一致 | [.out](week11/Rect/variants/tests/negative_coords.out) | [.out](../week11/Rect/variants/tests/negative_coords.out) |
| `Rect/variant_reversed_both` | 一致 | [.out](week11/Rect/variants/tests/reversed_both.out) | [.out](../week11/Rect/variants/tests/reversed_both.out) |
| `Rect/variant_reversed_y` | 一致 | [.out](week11/Rect/variants/tests/reversed_y.out) | [.out](../week11/Rect/variants/tests/reversed_y.out) |
| `Rect/variant_zero_height` | 一致 | [.out](week11/Rect/variants/tests/zero_height.out) | [.out](../week11/Rect/variants/tests/zero_height.out) |
| `Rect/variant_zero_width` | 一致 | [.out](week11/Rect/variants/tests/zero_width.out) | [.out](../week11/Rect/variants/tests/zero_width.out) |
| `RectContains/basic` | 一致 | [.out](week11/RectContains/tests/basic.out) | [.out](../week11/RectContains/tests/basic.out) |
| `RectContains/variant_closed_3_2` | 一致 | [.out](week11/RectContains/variants/tests/closed_3_2.out) | [.out](../week11/RectContains/variants/tests/closed_3_2.out) |
| `RectContains/variant_name_test_rect` | 一致 | [.out](week11/RectContains/variants/tests/name_test_rect.out) | [.out](../week11/RectContains/variants/tests/name_test_rect.out) |
| `RectContains/variant_order_1_1_3_4` | 一致 | [.out](week11/RectContains/variants/tests/order_1_1_3_4.out) | [.out](../week11/RectContains/variants/tests/order_1_1_3_4.out) |
| `RectContains/variant_order_3_1_1_4` | 一致 | [.out](week11/RectContains/variants/tests/order_3_1_1_4.out) | [.out](../week11/RectContains/variants/tests/order_3_1_1_4.out) |
| `RectContains/variant_order_3_4_1_1` | 一致 | [.out](week11/RectContains/variants/tests/order_3_4_1_1.out) | [.out](../week11/RectContains/variants/tests/order_3_4_1_1.out) |
| `RectContains/variant_point_0_2` | 一致 | [.out](week11/RectContains/variants/tests/point_0_2.out) | [.out](../week11/RectContains/variants/tests/point_0_2.out) |
| `RectContains/variant_point_1_1` | 一致 | [.out](week11/RectContains/variants/tests/point_1_1.out) | [.out](../week11/RectContains/variants/tests/point_1_1.out) |
| `RectContains/variant_point_1_3` | 一致 | [.out](week11/RectContains/variants/tests/point_1_3.out) | [.out](../week11/RectContains/variants/tests/point_1_3.out) |
| `RectContains/variant_point_2_4` | 一致 | [.out](week11/RectContains/variants/tests/point_2_4.out) | [.out](../week11/RectContains/variants/tests/point_2_4.out) |
| `RectContains/variant_point_2_5` | 一致 | [.out](week11/RectContains/variants/tests/point_2_5.out) | [.out](../week11/RectContains/variants/tests/point_2_5.out) |
| `RectContains/variant_point_3_2` | 一致 | [.out](week11/RectContains/variants/tests/point_3_2.out) | [.out](../week11/RectContains/variants/tests/point_3_2.out) |
| `RectContains/variant_swap_only_1_4_3_1` | 一致 | [.out](week11/RectContains/variants/tests/swap_only_1_4_3_1.out) | [.out](../week11/RectContains/variants/tests/swap_only_1_4_3_1.out) |
| `RectContains/variant_swap_only_3_1_1_4` | 一致 | [.out](week11/RectContains/variants/tests/swap_only_3_1_1_4.out) | [.out](../week11/RectContains/variants/tests/swap_only_3_1_1_4.out) |
| `RectContains/variant_swap_only_3_4_1_1` | 一致 | [.out](week11/RectContains/variants/tests/swap_only_3_4_1_1.out) | [.out](../week11/RectContains/variants/tests/swap_only_3_4_1_1.out) |
| `RectContains/variant_zero_width` | 一致 | [.out](week11/RectContains/variants/tests/zero_width.out) | [.out](../week11/RectContains/variants/tests/zero_width.out) |
| `StructLayout/basic` | 一致 | [.out](week11/StructLayout/tests/basic.out) | [.out](../week11/StructLayout/tests/basic.out) |
| `StructLayout/variant_record_reordered` | 一致 | [.out](week11/StructLayout/variants/tests/record_reordered.out) | [.out](../week11/StructLayout/variants/tests/record_reordered.out) |
| `Students/basic` | 一致 | [.out](week11/Students/tests/basic.out) | [.out](../week11/Students/tests/basic.out) |
| `Students/variant_all_0` | 一致 | [.out](week11/Students/variants/tests/all_0.out) | [.out](../week11/Students/variants/tests/all_0.out) |
| `Students/variant_all_100` | 一致 | [.out](week11/Students/variants/tests/all_100.out) | [.out](../week11/Students/variants/tests/all_100.out) |
| `Students/variant_int_division` | 一致 | [.out](week11/Students/variants/tests/int_division.out) | [.out](../week11/Students/variants/tests/int_division.out) |
| `Students/variant_n_1` | 一致 | [.out](week11/Students/variants/tests/n_1.out) | [.out](../week11/Students/variants/tests/n_1.out) |
| `Students/variant_n_2` | 一致 | [.out](week11/Students/variants/tests/n_2.out) | [.out](../week11/Students/variants/tests/n_2.out) |
| `Students/variant_same_student` | 一致 | [.out](week11/Students/variants/tests/same_student.out) | [.out](../week11/Students/variants/tests/same_student.out) |
| `Students/variant_same_student_score_only_swap` | 一致 | [.out](week11/Students/variants/tests/same_student_score_only_swap.out) | [.out](../week11/Students/variants/tests/same_student_score_only_swap.out) |
| `Students/variant_score_only_swap` | 一致 | [.out](week11/Students/variants/tests/score_only_swap.out) | [.out](../week11/Students/variants/tests/score_only_swap.out) |
| `Students/variant_scores_80_70_91` | 一致 | [.out](week11/Students/variants/tests/scores_80_70_91.out) | [.out](../week11/Students/variants/tests/scores_80_70_91.out) |

## week12

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `CalcApp/basic` | 一致 | [.out](week12/CalcApp/tests/basic.out) | [.out](../week12/CalcApp/tests/basic.out) |
| `CalcApp/variant_lecture` | 一致 | [.out](week12/CalcApp/variants/tests/lecture.out) | [.out](../week12/CalcApp/variants/tests/lecture.out) |
| `LibraryCheck/basic` | 一致 | [.out](week12/LibraryCheck/tests/basic.out) | [.out](../week12/LibraryCheck/tests/basic.out) |
| `LibraryCheck/variant_ndebug` | 一致 | [.out](week12/LibraryCheck/variants/tests/ndebug.out) | [.out](../week12/LibraryCheck/variants/tests/ndebug.out) |
| `SortModule/abc` | 一致 | [.out](week12/SortModule/tests/abc.out) [.err](week12/SortModule/tests/abc.err) [.code](week12/SortModule/tests/abc.code) | [.out](../week12/SortModule/tests/abc.out) |
| `SortModule/empty_string` | 一致 | [.out](week12/SortModule/tests/empty_string.out) [.err](week12/SortModule/tests/empty_string.err) [.code](week12/SortModule/tests/empty_string.code) | [.out](../week12/SortModule/tests/empty_string.out) |
| `SortModule/huge` | 一致 | [.out](week12/SortModule/tests/huge.out) [.err](week12/SortModule/tests/huge.err) [.code](week12/SortModule/tests/huge.code) | [.out](../week12/SortModule/tests/huge.out) |
| `SortModule/leading_space` | 一致 | [.out](week12/SortModule/tests/leading_space.out) | [.out](../week12/SortModule/tests/leading_space.out) |
| `SortModule/leading_zero` | 一致 | [.out](week12/SortModule/tests/leading_zero.out) | [.out](../week12/SortModule/tests/leading_zero.out) |
| `SortModule/minus1` | 一致 | [.out](week12/SortModule/tests/minus1.out) [.err](week12/SortModule/tests/minus1.err) [.code](week12/SortModule/tests/minus1.code) | [.out](../week12/SortModule/tests/minus1.out) |
| `SortModule/minus_zero` | 一致 | [.out](week12/SortModule/tests/minus_zero.out) | [.out](../week12/SortModule/tests/minus_zero.out) |
| `SortModule/n0` | 一致 | [.out](week12/SortModule/tests/n0.out) | [.out](../week12/SortModule/tests/n0.out) |
| `SortModule/n1` | 一致 | [.out](week12/SortModule/tests/n1.out) | [.out](../week12/SortModule/tests/n1.out) |
| `SortModule/n5` | 一致 | [.out](week12/SortModule/tests/n5.out) | [.out](../week12/SortModule/tests/n5.out) |
| `SortModule/n8` | 一致 | [.out](week12/SortModule/tests/n8.out) | [.out](../week12/SortModule/tests/n8.out) |
| `SortModule/n9` | 一致 | [.out](week12/SortModule/tests/n9.out) [.err](week12/SortModule/tests/n9.err) [.code](week12/SortModule/tests/n9.code) | [.out](../week12/SortModule/tests/n9.out) |
| `SortModule/no_args` | 一致 | [.out](week12/SortModule/tests/no_args.out) [.err](week12/SortModule/tests/no_args.err) [.code](week12/SortModule/tests/no_args.code) | [.out](../week12/SortModule/tests/no_args.out) |
| `SortModule/plus5` | 一致 | [.out](week12/SortModule/tests/plus5.out) | [.out](../week12/SortModule/tests/plus5.out) |
| `SortModule/trailing_space` | 一致 | [.out](week12/SortModule/tests/trailing_space.out) [.err](week12/SortModule/tests/trailing_space.err) [.code](week12/SortModule/tests/trailing_space.code) | [.out](../week12/SortModule/tests/trailing_space.out) |
| `SortModule/trailing_x` | 一致 | [.out](week12/SortModule/tests/trailing_x.out) [.err](week12/SortModule/tests/trailing_x.err) [.code](week12/SortModule/tests/trailing_x.code) | [.out](../week12/SortModule/tests/trailing_x.out) |
| `SortModule/two_args` | 一致 | [.out](week12/SortModule/tests/two_args.out) [.err](week12/SortModule/tests/two_args.err) [.code](week12/SortModule/tests/two_args.code) | [.out](../week12/SortModule/tests/two_args.out) |
| `SortModule/variant_insertion--abc` | 一致 | [.out](week12/SortModule/variants/tests/insertion--abc.out) [.err](week12/SortModule/variants/tests/insertion--abc.err) [.code](week12/SortModule/variants/tests/insertion--abc.code) | [.out](../week12/SortModule/variants/tests/insertion--abc.out) |
| `SortModule/variant_insertion--empty_string` | 一致 | [.out](week12/SortModule/variants/tests/insertion--empty_string.out) [.err](week12/SortModule/variants/tests/insertion--empty_string.err) [.code](week12/SortModule/variants/tests/insertion--empty_string.code) | [.out](../week12/SortModule/variants/tests/insertion--empty_string.out) |
| `SortModule/variant_insertion--huge` | 一致 | [.out](week12/SortModule/variants/tests/insertion--huge.out) [.err](week12/SortModule/variants/tests/insertion--huge.err) [.code](week12/SortModule/variants/tests/insertion--huge.code) | [.out](../week12/SortModule/variants/tests/insertion--huge.out) |
| `SortModule/variant_insertion--leading_space` | 一致 | [.out](week12/SortModule/variants/tests/insertion--leading_space.out) | [.out](../week12/SortModule/variants/tests/insertion--leading_space.out) |
| `SortModule/variant_insertion--leading_zero` | 一致 | [.out](week12/SortModule/variants/tests/insertion--leading_zero.out) | [.out](../week12/SortModule/variants/tests/insertion--leading_zero.out) |
| `SortModule/variant_insertion--minus1` | 一致 | [.out](week12/SortModule/variants/tests/insertion--minus1.out) [.err](week12/SortModule/variants/tests/insertion--minus1.err) [.code](week12/SortModule/variants/tests/insertion--minus1.code) | [.out](../week12/SortModule/variants/tests/insertion--minus1.out) |
| `SortModule/variant_insertion--minus_zero` | 一致 | [.out](week12/SortModule/variants/tests/insertion--minus_zero.out) | [.out](../week12/SortModule/variants/tests/insertion--minus_zero.out) |
| `SortModule/variant_insertion--n0` | 一致 | [.out](week12/SortModule/variants/tests/insertion--n0.out) | [.out](../week12/SortModule/variants/tests/insertion--n0.out) |
| `SortModule/variant_insertion--n1` | 一致 | [.out](week12/SortModule/variants/tests/insertion--n1.out) | [.out](../week12/SortModule/variants/tests/insertion--n1.out) |
| `SortModule/variant_insertion--n5` | 一致 | [.out](week12/SortModule/variants/tests/insertion--n5.out) | [.out](../week12/SortModule/variants/tests/insertion--n5.out) |
| `SortModule/variant_insertion--n8` | 一致 | [.out](week12/SortModule/variants/tests/insertion--n8.out) | [.out](../week12/SortModule/variants/tests/insertion--n8.out) |
| `SortModule/variant_insertion--n9` | 一致 | [.out](week12/SortModule/variants/tests/insertion--n9.out) [.err](week12/SortModule/variants/tests/insertion--n9.err) [.code](week12/SortModule/variants/tests/insertion--n9.code) | [.out](../week12/SortModule/variants/tests/insertion--n9.out) |
| `SortModule/variant_insertion--no_args` | 一致 | [.out](week12/SortModule/variants/tests/insertion--no_args.out) [.err](week12/SortModule/variants/tests/insertion--no_args.err) [.code](week12/SortModule/variants/tests/insertion--no_args.code) | [.out](../week12/SortModule/variants/tests/insertion--no_args.out) |
| `SortModule/variant_insertion--plus5` | 一致 | [.out](week12/SortModule/variants/tests/insertion--plus5.out) | [.out](../week12/SortModule/variants/tests/insertion--plus5.out) |
| `SortModule/variant_insertion--trailing_space` | 一致 | [.out](week12/SortModule/variants/tests/insertion--trailing_space.out) [.err](week12/SortModule/variants/tests/insertion--trailing_space.err) [.code](week12/SortModule/variants/tests/insertion--trailing_space.code) | [.out](../week12/SortModule/variants/tests/insertion--trailing_space.out) |
| `SortModule/variant_insertion--trailing_x` | 一致 | [.out](week12/SortModule/variants/tests/insertion--trailing_x.out) [.err](week12/SortModule/variants/tests/insertion--trailing_x.err) [.code](week12/SortModule/variants/tests/insertion--trailing_x.code) | [.out](../week12/SortModule/variants/tests/insertion--trailing_x.out) |
| `SortModule/variant_insertion--two_args` | 一致 | [.out](week12/SortModule/variants/tests/insertion--two_args.out) [.err](week12/SortModule/variants/tests/insertion--two_args.err) [.code](week12/SortModule/variants/tests/insertion--two_args.code) | [.out](../week12/SortModule/variants/tests/insertion--two_args.out) |
| `SortModule/variant_insertion_limits` | 一致 | [.out](week12/SortModule/variants/tests/insertion_limits.out) | [.out](../week12/SortModule/variants/tests/insertion_limits.out) |
| `SortModule/variant_limits` | 一致 | [.out](week12/SortModule/variants/tests/limits.out) | [.out](../week12/SortModule/variants/tests/limits.out) |
| `SplitCalc/basic` | 一致 | [.out](week12/SplitCalc/tests/basic.out) | [.out](../week12/SplitCalc/tests/basic.out) |
| `SplitCalc/variant_div_0_2` | 一致 | [.out](week12/SplitCalc/variants/tests/div_0_2.out) | [.out](../week12/SplitCalc/variants/tests/div_0_2.out) |
| `SplitCalc/variant_div_6_0` | 一致 | [.out](week12/SplitCalc/variants/tests/div_6_0.out) | [.out](../week12/SplitCalc/variants/tests/div_6_0.out) |
| `SplitCalc/variant_div_m6_2` | 一致 | [.out](week12/SplitCalc/variants/tests/div_m6_2.out) | [.out](../week12/SplitCalc/variants/tests/div_m6_2.out) |
| `SplitCalc/variant_lecture` | 一致 | [.out](week12/SplitCalc/variants/tests/lecture.out) | [.out](../week12/SplitCalc/variants/tests/lecture.out) |
| `SplitCalc/variant_sub_0_0` | 一致 | [.out](week12/SplitCalc/variants/tests/sub_0_0.out) | [.out](../week12/SplitCalc/variants/tests/sub_0_0.out) |
| `SplitCalc/variant_sub_2_5` | 一致 | [.out](week12/SplitCalc/variants/tests/sub_2_5.out) | [.out](../week12/SplitCalc/variants/tests/sub_2_5.out) |
| `VectorCalc/basic` | 一致 | [.out](week12/VectorCalc/tests/basic.out) | [.out](../week12/VectorCalc/tests/basic.out) |
| `VectorCalc/variant_alpha0` | 一致 | [.out](week12/VectorCalc/variants/tests/alpha0.out) | [.out](../week12/VectorCalc/variants/tests/alpha0.out) |
| `VectorCalc/variant_identity` | 一致 | [.out](week12/VectorCalc/variants/tests/identity.out) | [.out](../week12/VectorCalc/variants/tests/identity.out) |
| `VectorCalc/variant_no_direct_include` | 一致 | [.out](week12/VectorCalc/variants/tests/no_direct_include.out) | [.out](../week12/VectorCalc/variants/tests/no_direct_include.out) |
| `VectorCalc/variant_unchanged` | 一致 | [.out](week12/VectorCalc/variants/tests/unchanged.out) | [.out](../week12/VectorCalc/variants/tests/unchanged.out) |

## week13

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `Dynamic/basic_5` | 一致 | [.out](week13/Dynamic/tests/basic_5.out) | [.out](../week13/Dynamic/tests/basic_5.out) |
| `Dynamic/blank_space` | 一致 | [.out](week13/Dynamic/tests/blank_space.out) [.err](week13/Dynamic/tests/blank_space.err) [.code](week13/Dynamic/tests/blank_space.code) | [.out](../week13/Dynamic/tests/blank_space.out) |
| `Dynamic/empty_arg` | 一致 | [.out](week13/Dynamic/tests/empty_arg.out) [.err](week13/Dynamic/tests/empty_arg.err) [.code](week13/Dynamic/tests/empty_arg.code) | [.out](../week13/Dynamic/tests/empty_arg.out) |
| `Dynamic/erange` | 一致 | [.out](week13/Dynamic/tests/erange.out) [.err](week13/Dynamic/tests/erange.err) [.code](week13/Dynamic/tests/erange.code) | [.out](../week13/Dynamic/tests/erange.out) |
| `Dynamic/max_1000` | 一致 | [.out](week13/Dynamic/tests/max_1000.out) | [.out](../week13/Dynamic/tests/max_1000.out) |
| `Dynamic/negative` | 一致 | [.out](week13/Dynamic/tests/negative.out) [.err](week13/Dynamic/tests/negative.err) [.code](week13/Dynamic/tests/negative.code) | [.out](../week13/Dynamic/tests/negative.out) |
| `Dynamic/no_args` | 一致 | [.out](week13/Dynamic/tests/no_args.out) [.err](week13/Dynamic/tests/no_args.err) [.code](week13/Dynamic/tests/no_args.code) | [.out](../week13/Dynamic/tests/no_args.out) |
| `Dynamic/not_number_abc` | 一致 | [.out](week13/Dynamic/tests/not_number_abc.out) [.err](week13/Dynamic/tests/not_number_abc.err) [.code](week13/Dynamic/tests/not_number_abc.code) | [.out](../week13/Dynamic/tests/not_number_abc.out) |
| `Dynamic/one_1` | 一致 | [.out](week13/Dynamic/tests/one_1.out) | [.out](../week13/Dynamic/tests/one_1.out) |
| `Dynamic/over_1001` | 一致 | [.out](week13/Dynamic/tests/over_1001.out) [.err](week13/Dynamic/tests/over_1001.err) [.code](week13/Dynamic/tests/over_1001.code) | [.out](../week13/Dynamic/tests/over_1001.out) |
| `Dynamic/plus_sign` | 一致 | [.out](week13/Dynamic/tests/plus_sign.out) | [.out](../week13/Dynamic/tests/plus_sign.out) |
| `Dynamic/three_3` | 一致 | [.out](week13/Dynamic/tests/three_3.out) | [.out](../week13/Dynamic/tests/three_3.out) |
| `Dynamic/too_many_args` | 一致 | [.out](week13/Dynamic/tests/too_many_args.out) [.err](week13/Dynamic/tests/too_many_args.err) [.code](week13/Dynamic/tests/too_many_args.code) | [.out](../week13/Dynamic/tests/too_many_args.out) |
| `Dynamic/trailing_3x` | 一致 | [.out](week13/Dynamic/tests/trailing_3x.out) [.err](week13/Dynamic/tests/trailing_3x.err) [.code](week13/Dynamic/tests/trailing_3x.code) | [.out](../week13/Dynamic/tests/trailing_3x.out) |
| `Dynamic/two_2` | 一致 | [.out](week13/Dynamic/tests/two_2.out) | [.out](../week13/Dynamic/tests/two_2.out) |
| `Dynamic/variant_swap_all` | 一致 | [.out](week13/Dynamic/variants/tests/swap_all.out) | [.out](../week13/Dynamic/variants/tests/swap_all.out) |
| `Dynamic/variant_swap_pairs--n1` | 一致 | [.out](week13/Dynamic/variants/tests/swap_pairs--n1.out) | [.out](../week13/Dynamic/variants/tests/swap_pairs--n1.out) |
| `Dynamic/variant_swap_pairs--n2` | 一致 | [.out](week13/Dynamic/variants/tests/swap_pairs--n2.out) | [.out](../week13/Dynamic/variants/tests/swap_pairs--n2.out) |
| `Dynamic/variant_swap_pairs--n5` | 一致 | [.out](week13/Dynamic/variants/tests/swap_pairs--n5.out) | [.out](../week13/Dynamic/variants/tests/swap_pairs--n5.out) |
| `Dynamic/variant_trace--n3` | 一致 | [.out](week13/Dynamic/variants/tests/trace--n3.out) | [.out](../week13/Dynamic/variants/tests/trace--n3.out) |
| `Dynamic/zero` | 一致 | [.out](week13/Dynamic/tests/zero.out) [.err](week13/Dynamic/tests/zero.err) [.code](week13/Dynamic/tests/zero.code) | [.out](../week13/Dynamic/tests/zero.out) |
| `DynamicCopy/basic_5` | 一致 | [.out](week13/DynamicCopy/tests/basic_5.out) | [.out](../week13/DynamicCopy/tests/basic_5.out) |
| `DynamicCopy/blank_space` | 一致 | [.out](week13/DynamicCopy/tests/blank_space.out) [.err](week13/DynamicCopy/tests/blank_space.err) [.code](week13/DynamicCopy/tests/blank_space.code) | [.out](../week13/DynamicCopy/tests/blank_space.out) |
| `DynamicCopy/empty_arg` | 一致 | [.out](week13/DynamicCopy/tests/empty_arg.out) [.err](week13/DynamicCopy/tests/empty_arg.err) [.code](week13/DynamicCopy/tests/empty_arg.code) | [.out](../week13/DynamicCopy/tests/empty_arg.out) |
| `DynamicCopy/erange` | 一致 | [.out](week13/DynamicCopy/tests/erange.out) [.err](week13/DynamicCopy/tests/erange.err) [.code](week13/DynamicCopy/tests/erange.code) | [.out](../week13/DynamicCopy/tests/erange.out) |
| `DynamicCopy/max_1000` | 一致 | [.out](week13/DynamicCopy/tests/max_1000.out) | [.out](../week13/DynamicCopy/tests/max_1000.out) |
| `DynamicCopy/negative` | 一致 | [.out](week13/DynamicCopy/tests/negative.out) [.err](week13/DynamicCopy/tests/negative.err) [.code](week13/DynamicCopy/tests/negative.code) | [.out](../week13/DynamicCopy/tests/negative.out) |
| `DynamicCopy/no_args` | 一致 | [.out](week13/DynamicCopy/tests/no_args.out) [.err](week13/DynamicCopy/tests/no_args.err) [.code](week13/DynamicCopy/tests/no_args.code) | [.out](../week13/DynamicCopy/tests/no_args.out) |
| `DynamicCopy/not_number_abc` | 一致 | [.out](week13/DynamicCopy/tests/not_number_abc.out) [.err](week13/DynamicCopy/tests/not_number_abc.err) [.code](week13/DynamicCopy/tests/not_number_abc.code) | [.out](../week13/DynamicCopy/tests/not_number_abc.out) |
| `DynamicCopy/one_1` | 一致 | [.out](week13/DynamicCopy/tests/one_1.out) | [.out](../week13/DynamicCopy/tests/one_1.out) |
| `DynamicCopy/over_1001` | 一致 | [.out](week13/DynamicCopy/tests/over_1001.out) [.err](week13/DynamicCopy/tests/over_1001.err) [.code](week13/DynamicCopy/tests/over_1001.code) | [.out](../week13/DynamicCopy/tests/over_1001.out) |
| `DynamicCopy/plus_sign` | 一致 | [.out](week13/DynamicCopy/tests/plus_sign.out) | [.out](../week13/DynamicCopy/tests/plus_sign.out) |
| `DynamicCopy/too_many_args` | 一致 | [.out](week13/DynamicCopy/tests/too_many_args.out) [.err](week13/DynamicCopy/tests/too_many_args.err) [.code](week13/DynamicCopy/tests/too_many_args.code) | [.out](../week13/DynamicCopy/tests/too_many_args.out) |
| `DynamicCopy/trailing_3x` | 一致 | [.out](week13/DynamicCopy/tests/trailing_3x.out) [.err](week13/DynamicCopy/tests/trailing_3x.err) [.code](week13/DynamicCopy/tests/trailing_3x.code) | [.out](../week13/DynamicCopy/tests/trailing_3x.out) |
| `DynamicCopy/two_2` | 一致 | [.out](week13/DynamicCopy/tests/two_2.out) | [.out](../week13/DynamicCopy/tests/two_2.out) |
| `DynamicCopy/variant_copy_alloc_fail` | 一致 | [.out](week13/DynamicCopy/variants/tests/copy_alloc_fail.out) [.err](week13/DynamicCopy/variants/tests/copy_alloc_fail.err) [.code](week13/DynamicCopy/variants/tests/copy_alloc_fail.code) | [.out](../week13/DynamicCopy/variants/tests/copy_alloc_fail.out) |
| `DynamicCopy/variant_reverse_copy--n1` | 一致 | [.out](week13/DynamicCopy/variants/tests/reverse_copy--n1.out) | [.out](../week13/DynamicCopy/variants/tests/reverse_copy--n1.out) |
| `DynamicCopy/variant_reverse_copy--n1000` | 一致 | [.out](week13/DynamicCopy/variants/tests/reverse_copy--n1000.out) | [.out](../week13/DynamicCopy/variants/tests/reverse_copy--n1000.out) |
| `DynamicCopy/variant_reverse_copy--n2` | 一致 | [.out](week13/DynamicCopy/variants/tests/reverse_copy--n2.out) | [.out](../week13/DynamicCopy/variants/tests/reverse_copy--n2.out) |
| `DynamicCopy/variant_reverse_copy--n5` | 一致 | [.out](week13/DynamicCopy/variants/tests/reverse_copy--n5.out) | [.out](../week13/DynamicCopy/variants/tests/reverse_copy--n5.out) |
| `DynamicCopy/variant_reverse_copy_alloc_fail` | 一致 | [.out](week13/DynamicCopy/variants/tests/reverse_copy_alloc_fail.out) [.err](week13/DynamicCopy/variants/tests/reverse_copy_alloc_fail.err) [.code](week13/DynamicCopy/variants/tests/reverse_copy_alloc_fail.code) | [.out](../week13/DynamicCopy/variants/tests/reverse_copy_alloc_fail.out) |
| `DynamicCopy/zero` | 一致 | [.out](week13/DynamicCopy/tests/zero.out) [.err](week13/DynamicCopy/tests/zero.err) [.code](week13/DynamicCopy/tests/zero.code) | [.out](../week13/DynamicCopy/tests/zero.out) |
| `DynamicVector/basic` | 一致 | [.out](week13/DynamicVector/tests/basic.out) | [.out](../week13/DynamicVector/tests/basic.out) |
| `DynamicVector/variant_destroy_again` | 一致 | [.out](week13/DynamicVector/variants/tests/destroy_again.out) | [.out](../week13/DynamicVector/variants/tests/destroy_again.out) |
| `DynamicVector/variant_early_return` | 一致 | [.out](week13/DynamicVector/variants/tests/early_return.out) | [.out](../week13/DynamicVector/variants/tests/early_return.out) |
| `DynamicVectorFail/fail_on_call_2` | 一致 | [.out](week13/DynamicVectorFail/tests/fail_on_call_2.out) [.err](week13/DynamicVectorFail/tests/fail_on_call_2.err) [.code](week13/DynamicVectorFail/tests/fail_on_call_2.code) | [.out](../week13/DynamicVectorFail/tests/fail_on_call_2.out) |
| `DynamicVectorFail/variant_early_return_fail_on_call_1` | 一致 | [.out](week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_1.out) [.err](week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_1.err) [.code](week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_1.code) | [.out](../week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_1.out) |
| `DynamicVectorFail/variant_early_return_fail_on_call_2` | 一致 | [.out](week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_2.out) [.err](week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_2.err) [.code](week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_2.code) | [.out](../week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_2.out) |
| `DynamicVectorFail/variant_early_return_fail_on_call_3` | 一致 | [.out](week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_3.out) [.err](week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_3.err) [.code](week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_3.code) | [.out](../week13/DynamicVectorFail/variants/tests/early_return_fail_on_call_3.out) |
| `DynamicVectorFail/variant_fail_on_call_0` | 一致 | [.out](week13/DynamicVectorFail/variants/tests/fail_on_call_0.out) | [.out](../week13/DynamicVectorFail/variants/tests/fail_on_call_0.out) |
| `DynamicVectorFail/variant_fail_on_call_1` | 一致 | [.out](week13/DynamicVectorFail/variants/tests/fail_on_call_1.out) [.err](week13/DynamicVectorFail/variants/tests/fail_on_call_1.err) [.code](week13/DynamicVectorFail/variants/tests/fail_on_call_1.code) | [.out](../week13/DynamicVectorFail/variants/tests/fail_on_call_1.out) |
| `DynamicVectorFail/variant_fail_on_call_3` | 一致 | [.out](week13/DynamicVectorFail/variants/tests/fail_on_call_3.out) [.err](week13/DynamicVectorFail/variants/tests/fail_on_call_3.err) [.code](week13/DynamicVectorFail/variants/tests/fail_on_call_3.code) | [.out](../week13/DynamicVectorFail/variants/tests/fail_on_call_3.out) |
| `GrowArray/basic` | 一致 | [.out](week13/GrowArray/tests/basic.out) | [.out](../week13/GrowArray/tests/basic.out) |
| `GrowArray/variant_grow_1_to_1000` | 一致 | [.out](week13/GrowArray/variants/tests/grow_1_to_1000.out) | [.out](../week13/GrowArray/variants/tests/grow_1_to_1000.out) |
| `GrowArray/variant_grow_1_to_4` | 一致 | [.out](week13/GrowArray/variants/tests/grow_1_to_4.out) | [.out](../week13/GrowArray/variants/tests/grow_1_to_4.out) |
| `GrowArray/variant_new_over_3_to_1001` | 一致 | [.out](week13/GrowArray/variants/tests/new_over_3_to_1001.out) [.err](week13/GrowArray/variants/tests/new_over_3_to_1001.err) [.code](week13/GrowArray/variants/tests/new_over_3_to_1001.code) | [.out](../week13/GrowArray/variants/tests/new_over_3_to_1001.out) |
| `GrowArray/variant_new_zero_3_to_0` | 一致 | [.out](week13/GrowArray/variants/tests/new_zero_3_to_0.out) [.err](week13/GrowArray/variants/tests/new_zero_3_to_0.err) [.code](week13/GrowArray/variants/tests/new_zero_3_to_0.code) | [.out](../week13/GrowArray/variants/tests/new_zero_3_to_0.out) |
| `GrowArray/variant_old_over_1001_to_5` | 一致 | [.out](week13/GrowArray/variants/tests/old_over_1001_to_5.out) [.err](week13/GrowArray/variants/tests/old_over_1001_to_5.err) [.code](week13/GrowArray/variants/tests/old_over_1001_to_5.code) | [.out](../week13/GrowArray/variants/tests/old_over_1001_to_5.out) |
| `GrowArray/variant_old_zero_0_to_5` | 一致 | [.out](week13/GrowArray/variants/tests/old_zero_0_to_5.out) [.err](week13/GrowArray/variants/tests/old_zero_0_to_5.err) [.code](week13/GrowArray/variants/tests/old_zero_0_to_5.code) | [.out](../week13/GrowArray/variants/tests/old_zero_0_to_5.out) |
| `GrowArray/variant_same_3_to_3` | 一致 | [.out](week13/GrowArray/variants/tests/same_3_to_3.out) | [.out](../week13/GrowArray/variants/tests/same_3_to_3.out) |
| `GrowArray/variant_shrink_3_to_1` | 一致 | [.out](week13/GrowArray/variants/tests/shrink_3_to_1.out) | [.out](../week13/GrowArray/variants/tests/shrink_3_to_1.out) |
| `GrowArrayFail/realloc_fail` | 一致 | [.out](week13/GrowArrayFail/tests/realloc_fail.out) [.err](week13/GrowArrayFail/tests/realloc_fail.err) [.code](week13/GrowArrayFail/tests/realloc_fail.code) | [.out](../week13/GrowArrayFail/tests/realloc_fail.out) |
| `GrowArrayFail/variant_shrink_fail_3_to_1` | 一致 | [.out](week13/GrowArrayFail/variants/tests/shrink_fail_3_to_1.out) [.err](week13/GrowArrayFail/variants/tests/shrink_fail_3_to_1.err) [.code](week13/GrowArrayFail/variants/tests/shrink_fail_3_to_1.code) | [.out](../week13/GrowArrayFail/variants/tests/shrink_fail_3_to_1.out) |
| `GrowArrayFail/variant_simulate_failure_0` | 一致 | [.out](week13/GrowArrayFail/variants/tests/simulate_failure_0.out) | [.out](../week13/GrowArrayFail/variants/tests/simulate_failure_0.out) |
| `NewPoint/basic` | 一致 | [.out](week13/NewPoint/tests/basic.out) | [.out](../week13/NewPoint/tests/basic.out) |
| `NewPoint/variant_point_0_0` | 一致 | [.out](week13/NewPoint/variants/tests/point_0_0.out) | [.out](../week13/NewPoint/variants/tests/point_0_0.out) |
| `NewPoint/variant_point_m2_5` | 一致 | [.out](week13/NewPoint/variants/tests/point_m2_5.out) | [.out](../week13/NewPoint/variants/tests/point_m2_5.out) |
| `NewPoint/variant_return_styles` | 一致 | [.out](week13/NewPoint/variants/tests/return_styles.out) | [.out](../week13/NewPoint/variants/tests/return_styles.out) |
| `NewPoint/variant_two_statements` | 一致 | [.out](week13/NewPoint/variants/tests/two_statements.out) | [.out](../week13/NewPoint/variants/tests/two_statements.out) |
| `NewPointFail/allocation_failed` | 一致 | [.out](week13/NewPointFail/tests/allocation_failed.out) [.err](week13/NewPointFail/tests/allocation_failed.err) [.code](week13/NewPointFail/tests/allocation_failed.code) | [.out](../week13/NewPointFail/tests/allocation_failed.out) |
| `NewPointFail/variant_simulate_failure_0` | 一致 | [.out](week13/NewPointFail/variants/tests/simulate_failure_0.out) | [.out](../week13/NewPointFail/variants/tests/simulate_failure_0.out) |
| `SharedCount/basic` | 一致 | [.out](week13/SharedCount/tests/basic.out) | [.out](../week13/SharedCount/tests/basic.out) |
| `StorageCount/basic` | 一致 | [.out](week13/StorageCount/tests/basic.out) | [.out](../week13/StorageCount/tests/basic.out) |
| `StorageCount/variant_auto_count` | 一致 | [.out](week13/StorageCount/variants/tests/auto_count.out) | [.out](../week13/StorageCount/variants/tests/auto_count.out) |
| `StorageCount/variant_static_assign` | 一致 | [.out](week13/StorageCount/variants/tests/static_assign.out) | [.out](../week13/StorageCount/variants/tests/static_assign.out) |

## week14

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `CheckedFactorial/basic` | 一致 | [.out](week14/CheckedFactorial/tests/basic.out) | [.out](../week14/CheckedFactorial/tests/basic.out) |
| `CheckedFactorial/variant_n_0` | 一致 | [.out](week14/CheckedFactorial/variants/tests/n_0.out) | [.out](../week14/CheckedFactorial/variants/tests/n_0.out) |
| `CheckedFactorial/variant_n_1` | 一致 | [.out](week14/CheckedFactorial/variants/tests/n_1.out) | [.out](../week14/CheckedFactorial/variants/tests/n_1.out) |
| `CheckedFactorial/variant_n_20` | 一致 | [.out](week14/CheckedFactorial/variants/tests/n_20.out) | [.out](../week14/CheckedFactorial/variants/tests/n_20.out) |
| `CheckedFactorial/variant_n_21` | 一致 | [.out](week14/CheckedFactorial/variants/tests/n_21.out) | [.out](../week14/CheckedFactorial/variants/tests/n_21.out) |
| `CheckedFactorial/variant_n_minus1` | 一致 | [.out](week14/CheckedFactorial/variants/tests/n_minus1.out) | [.out](../week14/CheckedFactorial/variants/tests/n_minus1.out) |
| `CheckedFactorial/variant_null_out` | 一致 | [.out](week14/CheckedFactorial/variants/tests/null_out.out) | [.out](../week14/CheckedFactorial/variants/tests/null_out.out) |
| `Factorial/basic` | 一致 | [.out](week14/Factorial/tests/basic.out) | [.out](../week14/Factorial/tests/basic.out) |
| `Factorial/variant_base_0` | 一致 | [.out](week14/Factorial/variants/tests/base_0.out) | [.out](../week14/Factorial/variants/tests/base_0.out) |
| `Factorial/variant_base_0_n0` | 一致 | [.out](week14/Factorial/variants/tests/base_0_n0.out) | [.out](../week14/Factorial/variants/tests/base_0_n0.out) |
| `Factorial/variant_base_0_n1` | 一致 | [.out](week14/Factorial/variants/tests/base_0_n1.out) | [.out](../week14/Factorial/variants/tests/base_0_n1.out) |
| `Factorial/variant_base_0_n2` | 一致 | [.out](week14/Factorial/variants/tests/base_0_n2.out) | [.out](../week14/Factorial/variants/tests/base_0_n2.out) |
| `Factorial/variant_base_0_n20` | 一致 | [.out](week14/Factorial/variants/tests/base_0_n20.out) | [.out](../week14/Factorial/variants/tests/base_0_n20.out) |
| `Factorial/variant_base_0_n3` | 一致 | [.out](week14/Factorial/variants/tests/base_0_n3.out) | [.out](../week14/Factorial/variants/tests/base_0_n3.out) |
| `Factorial/variant_base_0_n4` | 一致 | [.out](week14/Factorial/variants/tests/base_0_n4.out) | [.out](../week14/Factorial/variants/tests/base_0_n4.out) |
| `Factorial/variant_count` | 一致 | [.out](week14/Factorial/variants/tests/count.out) | [.out](../week14/Factorial/variants/tests/count.out) |
| `Factorial/variant_n_0` | 一致 | [.out](week14/Factorial/variants/tests/n_0.out) | [.out](../week14/Factorial/variants/tests/n_0.out) |
| `Factorial/variant_n_1` | 一致 | [.out](week14/Factorial/variants/tests/n_1.out) | [.out](../week14/Factorial/variants/tests/n_1.out) |
| `Factorial/variant_n_10` | 一致 | [.out](week14/Factorial/variants/tests/n_10.out) | [.out](../week14/Factorial/variants/tests/n_10.out) |
| `Factorial/variant_n_20` | 一致 | [.out](week14/Factorial/variants/tests/n_20.out) | [.out](../week14/Factorial/variants/tests/n_20.out) |
| `Factorial/variant_n_21` | 一致 | [.out](week14/Factorial/variants/tests/n_21.out) [.err](week14/Factorial/variants/tests/n_21.err) [.code](week14/Factorial/variants/tests/n_21.code) | [.out](../week14/Factorial/variants/tests/n_21.out) |
| `Factorial/variant_n_3` | 一致 | [.out](week14/Factorial/variants/tests/n_3.out) | [.out](../week14/Factorial/variants/tests/n_3.out) |
| `Fibonacci/basic` | 一致 | [.out](week14/Fibonacci/tests/basic.out) | [.out](../week14/Fibonacci/tests/basic.out) |
| `Fibonacci/variant_n_0` | 一致 | [.out](week14/Fibonacci/variants/tests/n_0.out) | [.out](../week14/Fibonacci/variants/tests/n_0.out) |
| `Fibonacci/variant_n_1` | 一致 | [.out](week14/Fibonacci/variants/tests/n_1.out) | [.out](../week14/Fibonacci/variants/tests/n_1.out) |
| `Fibonacci/variant_n_10` | 一致 | [.out](week14/Fibonacci/variants/tests/n_10.out) | [.out](../week14/Fibonacci/variants/tests/n_10.out) |
| `Fibonacci/variant_n_2` | 一致 | [.out](week14/Fibonacci/variants/tests/n_2.out) | [.out](../week14/Fibonacci/variants/tests/n_2.out) |
| `Fibonacci/variant_n_20` | 一致 | [.out](week14/Fibonacci/variants/tests/n_20.out) | [.out](../week14/Fibonacci/variants/tests/n_20.out) |
| `Fibonacci/variant_n_21` | 一致 | [.out](week14/Fibonacci/variants/tests/n_21.out) [.err](week14/Fibonacci/variants/tests/n_21.err) [.code](week14/Fibonacci/variants/tests/n_21.code) | [.out](../week14/Fibonacci/variants/tests/n_21.out) |
| `Fibonacci/variant_n_3` | 一致 | [.out](week14/Fibonacci/variants/tests/n_3.out) | [.out](../week14/Fibonacci/variants/tests/n_3.out) |
| `Fibonacci/variant_n_5` | 一致 | [.out](week14/Fibonacci/variants/tests/n_5.out) | [.out](../week14/Fibonacci/variants/tests/n_5.out) |
| `Fibonacci/variant_n_minus1` | 一致 | [.out](week14/Fibonacci/variants/tests/n_minus1.out) [.err](week14/Fibonacci/variants/tests/n_minus1.err) [.code](week14/Fibonacci/variants/tests/n_minus1.code) | [.out](../week14/Fibonacci/variants/tests/n_minus1.out) |
| `Fibonacci/variant_no_reset` | 一致 | [.out](week14/Fibonacci/variants/tests/no_reset.out) | [.out](../week14/Fibonacci/variants/tests/no_reset.out) |
| `GcdLoop/basic` | 一致 | [.out](week14/GcdLoop/tests/basic.out) | [.out](../week14/GcdLoop/tests/basic.out) |
| `GcdLoop/variant_a0_b0` | 一致 | [.out](week14/GcdLoop/variants/tests/a0_b0.out) [.err](week14/GcdLoop/variants/tests/a0_b0.err) [.code](week14/GcdLoop/variants/tests/a0_b0.code) | [.out](../week14/GcdLoop/variants/tests/a0_b0.out) |
| `GcdLoop/variant_a0_b7` | 一致 | [.out](week14/GcdLoop/variants/tests/a0_b7.out) | [.out](../week14/GcdLoop/variants/tests/a0_b7.out) |
| `GcdLoop/variant_a100_b25` | 一致 | [.out](week14/GcdLoop/variants/tests/a100_b25.out) | [.out](../week14/GcdLoop/variants/tests/a100_b25.out) |
| `GcdLoop/variant_a13_b8` | 一致 | [.out](week14/GcdLoop/variants/tests/a13_b8.out) | [.out](../week14/GcdLoop/variants/tests/a13_b8.out) |
| `GcdLoop/variant_a18_b48` | 一致 | [.out](week14/GcdLoop/variants/tests/a18_b48.out) | [.out](../week14/GcdLoop/variants/tests/a18_b48.out) |
| `GcdLoop/variant_a7_b0` | 一致 | [.out](week14/GcdLoop/variants/tests/a7_b0.out) | [.out](../week14/GcdLoop/variants/tests/a7_b0.out) |
| `GcdLoop/variant_a7_b7` | 一致 | [.out](week14/GcdLoop/variants/tests/a7_b7.out) | [.out](../week14/GcdLoop/variants/tests/a7_b7.out) |
| `GcdLoop/variant_overwrite_first` | 一致 | [.out](week14/GcdLoop/variants/tests/overwrite_first.out) | [.out](../week14/GcdLoop/variants/tests/overwrite_first.out) |
| `GcdLoop/variant_overwrite_first_a13_b8` | 一致 | [.out](week14/GcdLoop/variants/tests/overwrite_first_a13_b8.out) | [.out](../week14/GcdLoop/variants/tests/overwrite_first_a13_b8.out) |
| `GcdLoop/variant_overwrite_first_a7_b0` | 一致 | [.out](week14/GcdLoop/variants/tests/overwrite_first_a7_b0.out) | [.out](../week14/GcdLoop/variants/tests/overwrite_first_a7_b0.out) |
| `GcdLoop/variant_trace_48_18` | 一致 | [.out](week14/GcdLoop/variants/tests/trace_48_18.out) | [.out](../week14/GcdLoop/variants/tests/trace_48_18.out) |
| `Trace/basic` | 一致 | [.out](week14/Trace/tests/basic.out) | [.out](../week14/Trace/tests/basic.out) |
| `Trace/variant_enter_after_check` | 一致 | [.out](week14/Trace/variants/tests/enter_after_check.out) | [.out](../week14/Trace/variants/tests/enter_after_check.out) |
| `Trace/variant_enter_after_check_n0` | 一致 | [.out](week14/Trace/variants/tests/enter_after_check_n0.out) | [.out](../week14/Trace/variants/tests/enter_after_check_n0.out) |
| `Trace/variant_leave_before_call` | 一致 | [.out](week14/Trace/variants/tests/leave_before_call.out) | [.out](../week14/Trace/variants/tests/leave_before_call.out) |
| `Trace/variant_n_0` | 一致 | [.out](week14/Trace/variants/tests/n_0.out) | [.out](../week14/Trace/variants/tests/n_0.out) |
| `Trace/variant_n_1` | 一致 | [.out](week14/Trace/variants/tests/n_1.out) | [.out](../week14/Trace/variants/tests/n_1.out) |
| `Trace/variant_n_100` | 一致 | [.out](week14/Trace/variants/tests/n_100.out) | [.out](../week14/Trace/variants/tests/n_100.out) |
| `Trace/variant_n_101` | 一致 | [.out](week14/Trace/variants/tests/n_101.out) [.err](week14/Trace/variants/tests/n_101.err) [.code](week14/Trace/variants/tests/n_101.code) | [.out](../week14/Trace/variants/tests/n_101.out) |
| `Trace/variant_n_2` | 一致 | [.out](week14/Trace/variants/tests/n_2.out) | [.out](../week14/Trace/variants/tests/n_2.out) |
| `Trace/variant_n_minus1` | 一致 | [.out](week14/Trace/variants/tests/n_minus1.out) [.err](week14/Trace/variants/tests/n_minus1.err) [.code](week14/Trace/variants/tests/n_minus1.code) | [.out](../week14/Trace/variants/tests/n_minus1.out) |
| `TreeTraversal/basic` | 一致 | [.out](week14/TreeTraversal/tests/basic.out) | [.out](../week14/TreeTraversal/tests/basic.out) |
| `TreeTraversal/variant_depth` | 一致 | [.out](week14/TreeTraversal/variants/tests/depth.out) | [.out](../week14/TreeTraversal/variants/tests/depth.out) |
| `TreeTraversal/variant_destroy` | 一致 | [.out](week14/TreeTraversal/variants/tests/destroy.out) | [.out](../week14/TreeTraversal/variants/tests/destroy.out) |
| `TreeTraversal/variant_line` | 一致 | [.out](week14/TreeTraversal/variants/tests/line.out) | [.out](../week14/TreeTraversal/variants/tests/line.out) |
| `TreeTraversal/variant_start_nodes2` | 一致 | [.out](week14/TreeTraversal/variants/tests/start_nodes2.out) | [.out](../week14/TreeTraversal/variants/tests/start_nodes2.out) |
| `TreeTraversal/variant_start_nodes3` | 一致 | [.out](week14/TreeTraversal/variants/tests/start_nodes3.out) | [.out](../week14/TreeTraversal/variants/tests/start_nodes3.out) |
| `TreeTraversal/variant_start_nodes6` | 一致 | [.out](week14/TreeTraversal/variants/tests/start_nodes6.out) | [.out](../week14/TreeTraversal/variants/tests/start_nodes6.out) |
| `TreeTraversal/variant_start_null` | 一致 | [.out](week14/TreeTraversal/variants/tests/start_null.out) | [.out](../week14/TreeTraversal/variants/tests/start_null.out) |
| `TreeTraversal/variant_walk_count` | 一致 | [.out](week14/TreeTraversal/variants/tests/walk_count.out) | [.out](../week14/TreeTraversal/variants/tests/walk_count.out) |
| `TreeTraversal/variant_walk_count_line` | 一致 | [.out](week14/TreeTraversal/variants/tests/walk_count_line.out) | [.out](../week14/TreeTraversal/variants/tests/walk_count_line.out) |

## debugging

| テスト | 結果 | 実際の出力 | 期待値 |
| --- | --- | --- | --- |
| `BugAnswerCheck/symptom` | 一致 | [.out](debugging/BugAnswerCheck/tests/symptom.out) | [.out](../debugging/BugAnswerCheck/tests/symptom.out) |
| `BugAnswerCheck/variant_fixed` | 一致 | [.out](debugging/BugAnswerCheck/variants/tests/fixed.out) | [.out](../debugging/BugAnswerCheck/variants/tests/fixed.out) |
| `BugBackupScores/variant_fixed` | 一致 | [.out](debugging/BugBackupScores/variants/tests/fixed.out) | [.out](../debugging/BugBackupScores/variants/tests/fixed.out) |
| `BugCharCount/empty_file` | 一致 | [.out](debugging/BugCharCount/tests/empty_file.out) | [.out](../debugging/BugCharCount/tests/empty_file.out) |
| `BugCharCount/three_lines` | 一致 | [.out](debugging/BugCharCount/tests/three_lines.out) | [.out](../debugging/BugCharCount/tests/three_lines.out) |
| `BugCharCount/variant_fixed--empty_file` | 一致 | [.out](debugging/BugCharCount/variants/tests/fixed--empty_file.out) | [.out](../debugging/BugCharCount/variants/tests/fixed--empty_file.out) |
| `BugCharCount/variant_fixed--no_final_newline` | 一致 | [.out](debugging/BugCharCount/variants/tests/fixed--no_final_newline.out) | [.out](../debugging/BugCharCount/variants/tests/fixed--no_final_newline.out) |
| `BugCharCount/variant_fixed--three_lines` | 一致 | [.out](debugging/BugCharCount/variants/tests/fixed--three_lines.out) | [.out](../debugging/BugCharCount/variants/tests/fixed--three_lines.out) |
| `BugCopyText/symptom` | 一致 | [.out](debugging/BugCopyText/tests/symptom.out) | [.out](../debugging/BugCopyText/tests/symptom.out) |
| `BugCopyText/variant_fixed` | 一致 | [.out](debugging/BugCopyText/variants/tests/fixed.out) | [.out](../debugging/BugCopyText/variants/tests/fixed.out) |
| `BugDigitSum/symptom` | 一致 | [.out](debugging/BugDigitSum/tests/symptom.out) | [.out](../debugging/BugDigitSum/tests/symptom.out) |
| `BugDigitSum/variant_fixed` | 一致 | [.out](debugging/BugDigitSum/variants/tests/fixed.out) | [.out](../debugging/BugDigitSum/variants/tests/fixed.out) |
| `BugEvenSum/symptom` | 一致 | [.out](debugging/BugEvenSum/tests/symptom.out) | [.out](../debugging/BugEvenSum/tests/symptom.out) |
| `BugEvenSum/variant_fixed` | 一致 | [.out](debugging/BugEvenSum/variants/tests/fixed.out) | [.out](../debugging/BugEvenSum/variants/tests/fixed.out) |
| `BugFactorial/variant_fixed` | 一致 | [.out](debugging/BugFactorial/variants/tests/fixed.out) | [.out](../debugging/BugFactorial/variants/tests/fixed.out) |
| `BugFactorialOverflow/variant_fixed` | 一致 | [.out](debugging/BugFactorialOverflow/variants/tests/fixed.out) | [.out](../debugging/BugFactorialOverflow/variants/tests/fixed.out) |
| `BugFindMax/symptom` | 一致 | [.out](debugging/BugFindMax/tests/symptom.out) | [.out](../debugging/BugFindMax/tests/symptom.out) |
| `BugFindMax/variant_fixed` | 一致 | [.out](debugging/BugFindMax/variants/tests/fixed.out) | [.out](../debugging/BugFindMax/variants/tests/fixed.out) |
| `BugGrade/symptom` | 一致 | [.out](debugging/BugGrade/tests/symptom.out) | [.out](../debugging/BugGrade/tests/symptom.out) |
| `BugGrade/variant_fixed` | 一致 | [.out](debugging/BugGrade/variants/tests/fixed.out) | [.out](../debugging/BugGrade/variants/tests/fixed.out) |
| `BugMallocSize/variant_fixed--five` | 一致 | [.out](debugging/BugMallocSize/variants/tests/fixed--five.out) | [.out](../debugging/BugMallocSize/variants/tests/fixed--five.out) |
| `BugMallocSize/variant_fixed--max_1000` | 一致 | [.out](debugging/BugMallocSize/variants/tests/fixed--max_1000.out) | [.out](../debugging/BugMallocSize/variants/tests/fixed--max_1000.out) |
| `BugMallocSize/variant_fixed--one` | 一致 | [.out](debugging/BugMallocSize/variants/tests/fixed--one.out) | [.out](../debugging/BugMallocSize/variants/tests/fixed--one.out) |
| `BugMallocSize/variant_fixed--zero` | 一致 | [.out](debugging/BugMallocSize/variants/tests/fixed--zero.out) [.err](debugging/BugMallocSize/variants/tests/fixed--zero.err) [.code](debugging/BugMallocSize/variants/tests/fixed--zero.code) | [.out](../debugging/BugMallocSize/variants/tests/fixed--zero.out) |
| `BugMeanScore/symptom` | 一致 | [.out](debugging/BugMeanScore/tests/symptom.out) | [.out](../debugging/BugMeanScore/tests/symptom.out) |
| `BugMeanScore/variant_fixed` | 一致 | [.out](debugging/BugMeanScore/variants/tests/fixed.out) | [.out](../debugging/BugMeanScore/variants/tests/fixed.out) |
| `BugReverseWord/variant_fixed--empty_line` | 一致 | [.out](debugging/BugReverseWord/variants/tests/fixed--empty_line.out) | [.out](../debugging/BugReverseWord/variants/tests/fixed--empty_line.out) |
| `BugReverseWord/variant_fixed--max_8` | 一致 | [.out](debugging/BugReverseWord/variants/tests/fixed--max_8.out) | [.out](../debugging/BugReverseWord/variants/tests/fixed--max_8.out) |
| `BugReverseWord/variant_fixed--one` | 一致 | [.out](debugging/BugReverseWord/variants/tests/fixed--one.out) | [.out](../debugging/BugReverseWord/variants/tests/fixed--one.out) |
| `BugReverseWord/variant_fixed--over_10` | 一致 | [.out](debugging/BugReverseWord/variants/tests/fixed--over_10.out) | [.out](../debugging/BugReverseWord/variants/tests/fixed--over_10.out) |
| `BugReverseWord/variant_fixed--short` | 一致 | [.out](debugging/BugReverseWord/variants/tests/fixed--short.out) | [.out](../debugging/BugReverseWord/variants/tests/fixed--short.out) |
| `BugRowSum/symptom` | 一致 | [.out](debugging/BugRowSum/tests/symptom.out) | [.out](../debugging/BugRowSum/tests/symptom.out) |
| `BugRowSum/variant_fixed` | 一致 | [.out](debugging/BugRowSum/variants/tests/fixed.out) | [.out](../debugging/BugRowSum/variants/tests/fixed.out) |
| `BugSharedCounter/symptom` | 一致 | [.out](debugging/BugSharedCounter/tests/symptom.out) | [.out](../debugging/BugSharedCounter/tests/symptom.out) |
| `BugSharedCounter/variant_fixed` | 一致 | .out | [.out](../debugging/BugSharedCounter/variants/tests/fixed.out) |
| `BugSkipCount/variant_fixed` | 一致 | [.out](debugging/BugSkipCount/variants/tests/fixed.out) | [.out](../debugging/BugSkipCount/variants/tests/fixed.out) |
| `BugStudentNames/symptom` | 一致 | [.out](debugging/BugStudentNames/tests/symptom.out) | [.out](../debugging/BugStudentNames/tests/symptom.out) |
| `BugStudentNames/variant_fixed--name_20` | 一致 | [.out](debugging/BugStudentNames/variants/tests/fixed--name_20.out) | [.out](../debugging/BugStudentNames/variants/tests/fixed--name_20.out) |
| `BugStudentNames/variant_fixed--name_21` | 一致 | [.out](debugging/BugStudentNames/variants/tests/fixed--name_21.out) [.err](debugging/BugStudentNames/variants/tests/fixed--name_21.err) [.code](debugging/BugStudentNames/variants/tests/fixed--name_21.code) | [.out](../debugging/BugStudentNames/variants/tests/fixed--name_21.out) |
| `BugStudentNames/variant_fixed--over_max` | 一致 | [.out](debugging/BugStudentNames/variants/tests/fixed--over_max.out) | [.out](../debugging/BugStudentNames/variants/tests/fixed--over_max.out) |
| `BugStudentNames/variant_fixed--three` | 一致 | [.out](debugging/BugStudentNames/variants/tests/fixed--three.out) | [.out](../debugging/BugStudentNames/variants/tests/fixed--three.out) |
| `BugUpper/abc` | 一致 | [.out](debugging/BugUpper/tests/abc.out) | [.out](../debugging/BugUpper/tests/abc.out) |
| `BugUpper/hello` | 一致 | [.out](debugging/BugUpper/tests/hello.out) | [.out](../debugging/BugUpper/tests/hello.out) |
| `BugUpper/variant_fixed--abc` | 一致 | [.out](debugging/BugUpper/variants/tests/fixed--abc.out) | [.out](../debugging/BugUpper/variants/tests/fixed--abc.out) |
| `BugUpper/variant_fixed--empty` | 一致 | [.out](debugging/BugUpper/variants/tests/fixed--empty.out) | [.out](../debugging/BugUpper/variants/tests/fixed--empty.out) |
| `BugUpper/variant_fixed--hello` | 一致 | [.out](debugging/BugUpper/variants/tests/fixed--hello.out) | [.out](../debugging/BugUpper/variants/tests/fixed--hello.out) |
| `BugUpper/variant_fixed--mixed` | 一致 | [.out](debugging/BugUpper/variants/tests/fixed--mixed.out) | [.out](../debugging/BugUpper/variants/tests/fixed--mixed.out) |
