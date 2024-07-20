#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_decimal temp2 = value_2;
  s21_set_sign(&temp2, 0);
  s21_set_sign(&temp, 0);
  s21_set_scale(&temp, s21_get_scale(value_1) + s21_get_scale(value_2));
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(value_1, i)) {
      s21_add(temp, temp2, &temp);
    }
    s21_shift_left(&temp2);
  }
  s21_set_sign(result, s21_get_sign(value_1) ^ s21_get_sign(value_2));
  *result = temp;
  return 0;
}