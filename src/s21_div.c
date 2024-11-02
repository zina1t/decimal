#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero = {{0, 0, 0, 0}};
  *result = zero;

  if (s21_is_zero(value_2)) {
    return 3;
  }

  int sign1 = s21_get_sign_1(value_1);
  int sign2 = s21_get_sign_1(value_2);

  s21_set_sign_1(&value_1, 0);
  s21_set_sign_1(&value_2, 0);

  align_scales(&value_1, &value_2);

  s21_decimal quotient = zero;
  s21_decimal remainder = zero;
  s21_decimal divisor = value_2;

  int result_scale = s21_get_scale_1(value_1);

  for (int i = s21_get_bit_last(value_1); i >= 0; i--) {
    s21_shift_left(&remainder, 1);
    if (s21_get_bit(value_1, i)) {
      s21_set_bit_1(&remainder, 0, 1);
    }

    if (s21_is_greater_or_equal(remainder, divisor)) {
      s21_sub(remainder, divisor, &remainder);
      s21_set_bit_1(&quotient, i, 1);
    }
  }

  while (!s21_is_zero(remainder) && result_scale < 28) {
    s21_shift_left(&remainder, 1);
    s21_shift_left(&quotient, 1);
    if (s21_is_greater_or_equal(remainder, divisor)) {
      s21_sub(remainder, divisor, &remainder);
      s21_set_bit_1(&quotient, 0, 1);
    }
    result_scale++;
  }

  s21_decimal half_divisor = divisor;
  s21_shift_right(&half_divisor, 1);

  if (!s21_is_zero(remainder)) {
    if (s21_is_greater(remainder, half_divisor) ||
        (s21_is_equal(remainder, half_divisor) && s21_get_bit(quotient, 0))) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_add(quotient, one, &quotient);
    }
  }

  s21_set_scale_1(&quotient, result_scale);

  if (sign1 != sign2) {
    s21_set_sign_1(&quotient, 1);
  }

  if (s21_get_bit_last(quotient) > 95) {
    return 1;
  }

  *result = quotient;

  return 0;
}
