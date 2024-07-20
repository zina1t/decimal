#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  s21_decimal temp = value_2;
  s21_set_sign(&temp, !s21_get_sign(value_2));
  s21_add(value_1, temp, result);
  return 0;
}