#include "s21_decimal.h"

int s21_get_sign(s21_decimal num) { return s21_get_bit(num, 127); }