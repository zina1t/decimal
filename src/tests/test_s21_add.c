#include <check.h>

#include "../s21_decimal.h"

// Тесты для s21_add
START_TEST(test_s21_add_positive) {
  s21_decimal value_1 = {{100, 0, 0, 0}};  // 100
  s21_decimal value_2 = {{200, 0, 0, 0}};  // 200
  s21_decimal result;
  s21_add(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], 300);  // Ожидается 300
}
END_TEST

START_TEST(test_s21_add_negative) {
  s21_decimal value_1 = {{100, 0, 0, 0x80000000}};  // -100
  s21_decimal value_2 = {{50, 0, 0, 0}};            // 50
  s21_decimal result;
  s21_add(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], -50);  // Ожидается -50
}
END_TEST

// Тесты для s21_div
START_TEST(test_s21_div_positive) {
  s21_decimal value_1 = {{100, 0, 0, 0}};  // 100
  s21_decimal value_2 = {{4, 0, 0, 0}};    // 4
  s21_decimal result;
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);  // Проверка успешного выполнения
  ck_assert_int_eq(result.bits[0], 25);  // Ожидается 25
}
END_TEST

START_TEST(test_s21_div_zero_divisor) {
  s21_decimal value_1 = {{100, 0, 0, 0}};  // 100
  s21_decimal value_2 = {{0, 0, 0, 0}};    // 0
  s21_decimal result;
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(
      status,
      3);  // Ожидается ошибка деления на ноль (предполагаем код ошибки - 3)
}
END_TEST

START_TEST(test_s21_floor) {
  s21_decimal value = {{123456, 0, 0, 0x00030000}};
  s21_decimal result;
  s21_floor(value, &result);
  ck_assert_int_eq(result.bits[0], 123);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float) {
  s21_decimal value = {{12345, 0, 0, 0x00020000}};
  float result;
  s21_from_s21_decimal_float(value, &result);
  ck_assert_float_eq(result, 123.45f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int) {
  s21_decimal value = {{12345, 0, 0, 0}};
  int result;
  s21_from_s21_decimalo_int(value, &result);
  ck_assert_int_eq(result, 12345);
}
END_TEST
START_TEST(test_s21_from_float_to_decimal) {
  float number = 123.456f;
  s21_decimal result = {{0, 0, 0, 0}};
  int float_res = s21_from_float_to_decimal(number, &result);

  s21_decimal expected = {{123456, 0, 0, 0x00030000}};

  ck_assert_int_eq(float_res, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_from_int_to_decimal) {
  int number = 12345;
  s21_decimal result;
  s21_from_int_to_decimal(number, &result);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_int_eq(result.bits[3], 0);  // Ожидается без знака и масштаб 0
}
END_TEST

START_TEST(test_s21_is_equal) {
  s21_decimal value_1 = {{555, 0, 0, 0x00010000}};
  s21_decimal value_2 = {{555, 0, 0, 0x00010000}};
  int res = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST
START_TEST(test_s21_is_greater_positive) {
  s21_decimal value_1 = {{12345, 0, 0, 0x00020000}};
  s21_decimal value_2 = {{6789, 0, 0, 0x00020000}};
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_is_greater_negative) {
  s21_decimal value_1 = {{50, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{100, 0, 0, 0x80000000}};
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_is_greater_equal) {
  s21_decimal value_1 = {{55, 0, 0, 0x00010000}};
  s21_decimal value_2 = {{55, 0, 0, 0x00010000}};
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_s21_is_less_positive_0) {
  s21_decimal value_1 = {{500, 0, 0, 0}};
  s21_decimal value_2 = {{1000, 0, 0, 0}};
  int res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_is_less_equal) {
  s21_decimal value_1 = {{1000, 0, 0, 0}};
  s21_decimal value_2 = {{1000, 0, 0, 0}};
  int res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_s21_is_less_negative) {
  s21_decimal value_1 = {{100, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{50, 0, 0, 0x80000000}};
  int res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_is_less_greater) {
  s21_decimal value_1 = {{2000, 0, 0, 0}};
  s21_decimal value_2 = {{1000, 0, 0, 0}};
  int res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_negative) {
  s21_decimal value_1 = {{100, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{50, 0, 0, 0x80000000}};
  int res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_greater) {
  s21_decimal value_1 = {{2000, 0, 0, 0}};
  s21_decimal value_2 = {{1000, 0, 0, 0}};
  int res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(test_s21_is_not_equal) {
  s21_decimal value_1 = {{100, 0, 0, 0}};
  s21_decimal value_2 = {{200, 0, 0, 0}};
  int res = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_equal) {
  s21_decimal value_1 = {{100, 0, 0, 0}};
  s21_decimal value_2 = {{100, 0, 0, 0}};
  int res = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(test_s21_mul_positive) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result;
  s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], 50);
}
END_TEST

START_TEST(test_s21_mul_negative) {
  s21_decimal value_1 = {{10, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result;
  s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(result.bits[3] & 0x80000000, 0x80000000);
}
END_TEST
START_TEST(test_s21_negate_positive) {
  s21_decimal value_1 = {{12345, 0, 0, 0x00020000}};
  s21_decimal result;
  s21_negate(value_1, &result);
  s21_decimal expected = {{12345, 0, 0, 0x80020000}};
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_negate_negative) {
  s21_decimal value_1 = {{99, 0, 0, 0x80000000}};
  s21_decimal result;
  s21_negate(value_1, &result);
  s21_decimal expected = {{99, 0, 0, 0}};
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST
START_TEST(test_s21_round) {
  s21_decimal value = {{123456, 0, 0, 0x00030000}};
  s21_decimal result;
  s21_round(value, &result);
  ck_assert_int_eq(result.bits[0], 123);
}
END_TEST
START_TEST(test_s21_sub_positive) {
  s21_decimal value_1 = {{300, 0, 0, 0}};
  s21_decimal value_2 = {{100, 0, 0, 0}};
  s21_decimal result;
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], 200);
}
END_TEST

START_TEST(test_s21_sub_negative) {
  s21_decimal value_1 = {{100, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{50, 0, 0, 0}};
  s21_decimal result;
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], 150);
  ck_assert_int_eq(result.bits[3] & 0x80000000, 0x80000000);
}
END_TEST
START_TEST(test_s21_truncate_positive) {
  s21_decimal value_1 = {{123456, 0, 0, 0x00030000}};
  s21_decimal result;
  s21_truncate(value_1, &result);
  s21_decimal expected = {{123, 0, 0, 0}};
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_truncate_negative) {
  s21_decimal value_1 = {{5075, 0, 0, 0x80020000}};
  s21_decimal result;
  s21_truncate(value_1, &result);
  s21_decimal expected = {{50, 0, 0, 0x80000000}};
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_truncate_small) {
  s21_decimal value_1 = {{1, 0, 0, 0x00030000}};
  s21_decimal result;
  s21_truncate(value_1, &result);
  s21_decimal expected = {{0, 0, 0, 0}};
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

Suite *suite_s21_add() {
  Suite *s = suite_create("suite_s21_add");
  TCase *tc = tcase_create("test_s21_add_tc");

  tcase_add_test(tc, test_s21_add_positive);
  tcase_add_test(tc, test_s21_add_negative);
  tcase_add_test(tc, test_s21_div_positive);
  tcase_add_test(tc, test_s21_div_zero_divisor);
  tcase_add_test(tc, test_s21_floor);
  tcase_add_test(tc, test_s21_from_decimal_to_float);
  tcase_add_test(tc, test_s21_from_decimal_to_int);
  tcase_add_test(tc, test_s21_from_float_to_decimal);
  tcase_add_test(tc, test_s21_from_int_to_decimal);
  tcase_add_test(tc, test_s21_is_equal);
  tcase_add_test(tc, test_s21_is_greater_positive);
  tcase_add_test(tc, test_s21_is_greater_negative);
  tcase_add_test(tc, test_s21_is_greater_equal);
  tcase_add_test(tc, test_s21_is_less_positive_0);
  tcase_add_test(tc, test_s21_is_less_equal);
  tcase_add_test(tc, test_s21_is_less_negative);
  tcase_add_test(tc, test_s21_is_less_greater);
  tcase_add_test(tc, test_s21_is_less_or_equal_negative);
  tcase_add_test(tc, test_s21_is_less_or_equal_greater);
  tcase_add_test(tc, test_s21_is_not_equal);
  tcase_add_test(tc, test_s21_is_not_equal_equal);
  tcase_add_test(tc, test_s21_mul_positive);
  tcase_add_test(tc, test_s21_mul_negative);
  tcase_add_test(tc, test_s21_negate_positive);
  tcase_add_test(tc, test_s21_negate_negative);
  tcase_add_test(tc, test_s21_round);
  tcase_add_test(tc, test_s21_sub_positive);
  tcase_add_test(tc, test_s21_sub_negative);
  tcase_add_test(tc, test_s21_truncate_positive);
  tcase_add_test(tc, test_s21_truncate_negative);
  tcase_add_test(tc, test_s21_truncate_small);

  suite_add_tcase(s, tc);
  return s;
}
