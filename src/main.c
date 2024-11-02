#include <stdio.h>

#include "s21_decimal.h"

void init_decimal(s21_decimal *decimal, int int_part, int scale, int sign) {
  decimal->bits[0] = int_part;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = (scale << 16) | (sign << 31);
}

void test_s21_add_positive() {
  s21_decimal value_1, value_2, result, expected_result;

  // Устанавливаем значения для сложения 25 + 75 = 100
  init_decimal(&value_1, 25, 0, 0);  // 25
  init_decimal(&value_2, 75, 0, 0);  // 75
  init_decimal(&expected_result, 100, 0, 0);  // Ожидаемый результат 100

  if (s21_add(value_1, value_2, &result) == 0 &&
      s21_is_equal(result, expected_result)) {
    printf("test_s21_add_positive passed\n");
  } else {
    printf("test_s21_add_positive failed\n");
  }
}

void test_s21_add_negative() {
  s21_decimal value_1, value_2, result, expected_result;

  // Устанавливаем значения для сложения -25 + 75 = 50
  init_decimal(&value_1, 25, 0, 1);          // -25
  init_decimal(&value_2, 75, 0, 0);          // 75
  init_decimal(&expected_result, 50, 0, 0);  // Ожидаемый результат 50

  if (s21_add(value_1, value_2, &result) == 0 &&
      s21_is_equal(result, expected_result)) {
    printf("test_s21_add_negative passed\n");
  } else {
    printf("test_s21_add_negative failed\n");
  }
}

int main() {
  test_s21_add_positive();
  test_s21_add_negative();

  return 0;
}