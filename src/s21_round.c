#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_truncate(value, result);
  s21_decimal fractional_part;
  s21_sub(value, *result, &fractional_part);

  s21_decimal half = {{5, 0, 0, 0}};
  s21_set_scale_1(&half, 1);

  if (s21_is_greater_or_equal(fractional_part, half)) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_add(*result, one, result);
  }
  return 0;
}
