
#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  memset(dst, 0, sizeof(s21_decimal));

  if (src > S21_DECIMAL_MAX || src < S21_DECIMAL_MIN) {
    return 1;
  }
  float int_part, frac_part;
  frac_part = modff(fabsf(src), &int_part);

  long long int int_value = (long long int)int_part;

  int is_negative = (src < 0);
  s21_set_sign(dst, is_negative);

  if (int_value > 0xFFFFFFFFLL) {
    dst->bits[1] = (int_value >> 32) & 0xFFFFFFFF;
  }
  dst->bits[0] = (int_value & 0xFFFFFFFF);

  int scale = 0;
  while (fabsf(frac_part) > 0.0f && scale < 28) {
    frac_part *= 10;
    int frac_int_part = (int)frac_part;

    dst->bits[0] += frac_int_part;

    if (dst->bits[0] > 0xFFFFFFFF) {
      dst->bits[1] += 1;
      dst->bits[0] -= 0x100000000;
    }

    frac_part -= frac_int_part;
    scale++;
  }

  s21_set_scale(dst, scale);

  return 0;
}
