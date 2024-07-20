#include "s21_decimal.h"

int s21_get_bit(s21_decimal num, int bit) {
  int num_int = bit / 32;
  int num_bit = bit % 32;
  return (num.bits[num_int] & (1u << num_bit)) >> num_bit;
}

int s21_get_scale(s21_decimal num) {
  int scale = 0;
  for (int i = 96 + 23; i >= 96 + 16; i--) {
    scale <<= 1;
    scale |= s21_get_bit(num, i);
  }
  printf("scale %d\n", scale);
  return scale;
}

int s21_get_sign(s21_decimal num) { 
  printf("Sign: %d\n", s21_get_bit(num, 127));
  return s21_get_bit(num, 127); 
}

int s21_is_zero(s21_decimal num) {
  int is_zero = 0;
  if (!num.bits[0] && !num.bits[1] && !num.bits[2] && !num.bits[3]) {
    is_zero = 1;
  }
  return is_zero;
}

void s21_normalize(s21_decimal* num1, s21_decimal* num2) {
  s21_decimal* temp;
  int diff;
  int flag = 0;
  if (s21_get_scale(*num1) < s21_get_scale(*num2)) {
    temp = num1;
    diff = s21_get_scale(*num2) - s21_get_scale(*num1);
  } else {
    temp = num2;
    diff = s21_get_scale(*num1) - s21_get_scale(*num2);
  }
  while (diff--) {
    s21_decimal x = {{10, 0, 0, 0}};
    flag = s21_mul(*temp, x, temp);
    if (flag) break;
    s21_set_scale(temp, s21_get_scale(*temp) + 1);
  }
  printf("normalized\n");
}

void s21_set_bit(s21_decimal* num, int bit, unsigned value) {
  int num_int = bit / 32;
  int num_bit = bit % 32;
  if (value == 1) {
    num->bits[num_int] |= (1u << num_bit);
  } else {
    num->bits[num_int] &= (~((1u) << num_bit));
  }
}

void s21_set_scale(s21_decimal* num, int scale_value) {
  for (int i = 96 + 16; i < 96 + 23; i++) {
    s21_set_bit(num, i, scale_value & 1);
    scale_value >>= 1;
  }
}

void s21_set_sign(s21_decimal *num, int sign) { s21_set_bit(num, 127, sign); }

void s21_shift_left(s21_decimal* num) {
  unsigned memory = 0;
  for (int i = 0; i < (int)sizeof(s21_decimal) / sizeof(unsigned) - 1; ++i) {
    unsigned temp = num->bits[i];
    num->bits[i] <<= 1;
    num->bits[i] |= memory;
    memory = temp >> (32 - 1);
  }
}