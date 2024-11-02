#include "s21_decimal.h"

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int res = 1;
  int sign_a = s21_get_sign(num1), sign_b = s21_get_sign(num2);
  if (!(s21_decimal_null(num1) && s21_decimal_null(num2))) {
    if (sign_a == sign_b) {
      alignmentScale(&num1, &num2);
      for (int i = 95; i >= 0; i--) {
        int bit_a = s21_get_bit(num1, i), bit_b = s21_get_bit(num2, i);
        if (bit_a != bit_b) {
          res = 0;
          break;
        }
      }
    } else {
      res = 0;
    }
  }
  return res;
}
