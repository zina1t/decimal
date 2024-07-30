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
int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal * result);

int s21_correct_decimal(s21_decimal num);

int s21_sub(s21_decimal num1, s21_decimal num2, s21_decimal* res);
int s21_mul(s21_decimal num1, s21_decimal num2, s21_decimal* result);

int s21_decimal_null(s21_decimal num);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_less(s21_decimal num1, s21_decimal num2);

s21_decimal* convert(s21_decimal* num);

s21_decimal s21_negate(s21_decimal num);
int compare_magnitude(s21_decimal num1, s21_decimal num2);

int float_to_decimal(float f, s21_decimal* result);
int int_to_decimal(int i, s21_decimal* result);

s21_decimal get_zero();
s21_decimal clear_decimal(s21_decimal num);