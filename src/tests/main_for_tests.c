#include <check.h>
#include <math.h>
#include <stdlib.h>

Suite *suite_s21_add();
// Suite *suite_s21_sub();
// Suite *suite_s21_from_decimal_to_float();
// Suite *suite_s21_from_decimal_to_int();
// Suite *suite_s21_floor();
// Suite *suite_s21_from_float_to_decimal();
// Suite *suite_s21_from_int_to_decimal();
// Suite *suite_s21_is_equal();
// Suite *suite_s21_is_greater();
// Suite *suite_s21_is_greater_or_equal();
// Suite *suite_s21_is_less();
// Suite *suite_s21_is_less_or_equal();
// Suite *suite_s21_is_not_equal();
// Suite *suite_s21_mul();
// Suite *suite_s21_negate();
// Suite *suite_s21_round();
// Suite *suite_s21_truncate();

int main() {
  int no_failed = 0;
  SRunner *runner;

  runner = srunner_create(suite_s21_add());
  // srunner_add_suite(runner, suite_s21_sub());
  // srunner_add_suite(runner, suite_s21_from_decimal_to_float());
  // srunner_add_suite(runner, suite_s21_from_decimal_to_int());
  // srunner_add_suite(runner, suite_s21_floor());
  // srunner_add_suite(runner, suite_s21_from_float_to_decimal());
  // srunner_add_suite(runner, suite_s21_from_int_to_decimal());
  // srunner_add_suite(runner, suite_s21_is_equal());
  // srunner_add_suite(runner, suite_s21_is_greater());
  // srunner_add_suite(runner, suite_s21_is_greater_or_equal());
  // srunner_add_suite(runner, suite_s21_is_less());
  // srunner_add_suite(runner, suite_s21_is_less_or_equal());
  // srunner_add_suite(runner, suite_s21_is_not_equal());
  // srunner_add_suite(runner, suite_s21_mul());
  // srunner_add_suite(runner, suite_s21_negate());
  // srunner_add_suite(runner, suite_s21_round());
  // srunner_add_suite(runner, suite_s21_truncate());

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
