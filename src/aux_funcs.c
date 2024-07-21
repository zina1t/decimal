#include "s21_decimal.h"

int s21_get_bit(int num, int bit) { 
  return !!(num & (1U << bit)); 
}

int s21_set_bit(int num, int bit) { 
  return (num | (1U << bit)); 
}

int s21_reset_bit(int num, int bit) { 
  return (num & ~(1U << bit)); 
}

int s21_get_sign(s21_decimal num) { 
  return s21_get_bit(num.bits[3], 31); 
}

void s21_set_sign(s21_decimal *num, int sign) {
  if (sign) {
    num->bits[3] = s21_set_bit(num->bits[3], 31);
  } else {
    num->bits[3] = s21_reset_bit(num->bits[3], 31);
 }
}

int s21_get_scale(s21_decimal num) {
  int scale = 0;
  for (int i = 96 + 16; i < 96 + 23; i++) {
    scale = scale << 1;
    scale += s21_get_bit(num.bits[3], i);
  }
  return scale;
}

void s21_set_scale(s21_decimal* num, int scale_value) {
  for (int i = 96 + 16; i < 96 + 23; i++) {
    if (scale_value & 1) {
      num->bits[3] = s21_set_bit(num->bits[3], i);
    } else {
      num->bits[3] = s21_reset_bit(num->bits[3], i);
    }
    scale_value >>= 1;
  }
}

int s21_correct_decimal(s21_decimal num) { // надо проверить правильность работы
  int error = 1;
  for (int i = 96; i < 128; i++) {
    if (((s21_get_bit(num.bits[3], i) != 0) && (i < 96 + 16)) || ((s21_get_bit(num.bits[3], i) != 0) && (i >= 96 + 24) && (i < 96 + 32))) {
      error = 0;
    }
  }
  if ((s21_get_scale(num) < 0) || (s21_get_scale(num) > 28)) {
    error = 0;
  }
  return error;
}

s21_decimal decimal_set_bit(s21_decimal num, int bit) {
  int num_int = bit / 32;
  int num_bit = bit % 32;
  num.bits[num_int] = s21_set_bit(num.bits[num_int], num_bit);
  return num;
}

int get_decimal_bit(s21_decimal num, int bit) {
  int num_int = bit / 32;
  int num_bit = bit % 32;
  return s21_get_bit(num.bits[num_int], num_bit);
}

int s21_not_zero_bit(s21_decimal num) {
  int pos = -1;
  for (int i = 127; i >= 0; i--) {
    if (get_decimal_bit(num, i)){
      pos = i;
      break;
    }
  }
  return pos;
}