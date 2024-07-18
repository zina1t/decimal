#include "s21_decimal.h"

void s21_shift_left(s21_decimal* num) {
  unsigned memory = 0;
  for (int i = 0; i < (int)sizeof(s21_decimal) / sizeof(unsigned) - 1; ++i) {
    unsigned temp = num->bits[i];
    num->bits[i] <<= 1;
    num->bits[i] |= memory;
    memory = temp >> (32 - 1);
  }
}