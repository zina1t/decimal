
#include "s21_decimal.h"
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int scale = s21_get_scale_1(value);
  *result = value;

  if (scale > 0) {
    for (int i = 0; i < scale; i++) {
      for (int j = 0; j < 3; j++) {
        result->bits[j] /= 10;
      }
    }

    result->bits[3] &= ~(0xFF << 16);
  }

  return 0;
}