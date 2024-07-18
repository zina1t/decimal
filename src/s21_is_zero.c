#include "s21_decimal.h"

int s21_is_zero(s21_decimal num) {
  int is_zero = 0;
  if (!num.bits[0] && !num.bits[1] && !num.bits[2] && !num.bits[3]) {
    is_zero = 1;
  }
  return is_zero;
}