#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_truncate(value, result);
  if (value.bits[3] & (1 << 31)) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_sub(*result, one, result);
  }
  return 0;
}
