#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int code = 0;
  if (!dst) {
    code = 1;
  } else {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    int sign;
    if (src < 0) {
      sign = 1;
      if (src != INT_MIN) {
        src = -src;
      }
    } else {
      sign = 0;
    }
    dst->bits[0] = src;
    s21_set_sign(dst, sign);
  }

  return code;
}