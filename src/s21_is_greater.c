#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int sign_1 = s21_get_sign_1(value_1);
  int sign_2 = s21_get_sign_1(value_2);

  if (sign_1 == 0 && sign_2 == 1) {
    return 1;
  } else if (sign_1 == 1 && sign_2 == 0) {
    return 0;
  }

  s21_normalization(&value_1, &value_2);

  int cmp_result = s21_compare_magnitude(value_1, value_2);
  if (sign_1 == 0) {
    return cmp_result > 0 ? 1 : 0;
  } else {
    return cmp_result < 0 ? 1 : 0;
  }
}