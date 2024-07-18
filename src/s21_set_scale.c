#include "s21_decimal.h"

void s21_set_scale(s21_decimal* num, int scale_value) {
  for (int i = 96 + 16; i < 96 + 23; i++) {
    s21_set_bit(num, i, scale_value & 1);
    scale_value >>= 1;
  }
}