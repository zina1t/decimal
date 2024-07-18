#include "s21_decimal.h"

int s21_get_scale(s21_decimal num) {
  int scale = 0;
  for (int i = 96 + 23; i >= 96 + 16; i--) {
    scale <<= 1;
    scale |= s21_get_bit(num, i);
  }
  return scale;
}