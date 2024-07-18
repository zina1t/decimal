#include "s21_decimal.h"

void s21_set_bit(s21_decimal* num, int bit, unsigned value) {
  int num_int = bit / 32;
  int num_bit = bit % 32;
  if (value == 1) {
    num->bits[num_int] |= (1u << num_bit);
  } else {
    num->bits[num_int] &= (~((1u) << num_bit));
  }
}