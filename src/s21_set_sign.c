#include "s21_decimal.h"

void s21_set_sign(s21_decimal *num, int sign) { s21_set_bit(num, 127, sign); }