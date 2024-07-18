#include "s21_decimal.h"

int s21_get_bit(s21_decimal num, int bit) {
  int num_int = bit / 32;
  int num_bit = bit % 32;
  return (num.bits[num_int] & (1u << num_bit)) >> num_bit;
}