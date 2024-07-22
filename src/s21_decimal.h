#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MINUS 0x80000000  // Bit mask to set the sign bit
#define PLUS 0x7FFFFFFF   // Bit mask to clear the sign bit

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

typedef struct s21_big_decimal {
  unsigned int bits[8];
} s21_big_decimal;

int s21_get_bit(s21_decimal num, int bit);
s21_decimal* s21_set_bit(s21_decimal* num, int pos, int bit);
int s21_reset_bit(int num, int bit);
int s21_get_last_bit(s21_decimal num);

s21_decimal* shift_left(s21_decimal* num, int shift);

int s21_get_sign(s21_decimal num);
void s21_set_sign(s21_decimal* num, int sign);

int s21_get_scale(s21_decimal num);
void s21_set_scale(s21_decimal* num, int scale_value);
void align_scales(s21_decimal *num1, s21_decimal *num2);
int s21_add (s21_decimal num1, s21_decimal num2, s21_decimal * result);

int s21_correct_decimal(s21_decimal num);