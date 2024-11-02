
#include "s21_decimal.h"
int s21_from_s21_decimalo_int(s21_decimal src, int *dst) {
  int res = 1;
  if (src.bits[1] == 0 && src.bits[2] == 0) {
    *dst = src.bits[0];
    if (s21_get_sign(src)) {
      *dst *= -1;
    }
    *dst /= (int)pow(10, s21_get_scale(src));
    res = 0;
  }
  return res;
}