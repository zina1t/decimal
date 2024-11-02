#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign_1(value_1);
  int sign_2 = s21_get_sign_1(value_2);

  s21_decimal temp_value_2 = value_2;

  if (sign_1 != sign_2) {
    s21_toggle_sign(&temp_value_2);
    return s21_add(value_1, temp_value_2, result);
  } else {
    s21_normalization(&value_1, &temp_value_2);

    int cmp_result = s21_compare_magnitude(value_1, temp_value_2);

    if (cmp_result == 0) {
      s21_set_zero(result);
      return 0;
    } else if ((cmp_result > 0 && sign_1 == 0) ||
               (cmp_result < 0 && sign_1 == 1)) {
      s21_subtract_magnitude(value_1, temp_value_2, result);
      s21_set_sign_1(result, sign_1);
    } else {
      s21_subtract_magnitude(temp_value_2, value_1, result);
      s21_set_sign_1(result, !sign_1);
    }
  }
  return 0;
}
