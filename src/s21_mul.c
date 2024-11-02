#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
  int res = 0;
  int sign_result = (s21_get_sign(value_1) != s21_get_sign(value_2)) ? 1 : 0;
  s21_set_sign(&value_1, 0);
  s21_set_sign(&value_2, 0);

  int bit1 = s21_get_bitLast(value_1);
  for (int i = 0; i <= bit1; i++) {
    if (s21_get_bit(value_1, i)) {
      s21_decimal tmp_res = value_2;
      leftShift(&tmp_res, i);
      res = s21_add_bit(*result, tmp_res, result);
    }
  }
  while (res && (s21_get_scale(value_1) > 0 || s21_get_scale(value_2) > 0)) {
    s21_decimal *larger, *smaller;
    if (s21_get_bitLast(value_1) > s21_get_bitLast(value_2) &&
        s21_get_scale(value_1) > 0) {
      larger = &value_1;
      smaller = &value_2;
    } else if (s21_get_bitLast(value_2) > s21_get_bitLast(value_1) &&
               s21_get_scale(value_2) > 0) {
      larger = &value_2;
      smaller = &value_1;
    } else {
      break;
    }
    int scale = s21_get_scale(*larger);
    decreaseScale(larger, 1);
    s21_set_scale(larger, --scale);
    return s21_mul(*larger, *smaller, result);
  }

  int scale = s21_get_scale(value_1) + s21_get_scale(value_2);
  s21_set_scale(result, scale);
  s21_set_sign(result, sign_result);
  if (res && sign_result) res = 2;

  return res;
}