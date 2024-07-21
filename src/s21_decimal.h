#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MINUS 0x80000000  // Bit mask to set the sign bit
#define PLUS 0x7FFFFFFF   // Bit mask to clear the sign bit

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

typedef struct s21_big_decimal {
  unsigned int bits[8];
} s21_big_decimal;

int s21_is_zero(s21_decimal num);
void null_decimal(s21_decimal* num);

int s21_get_sign(s21_decimal num);
void s21_set_sign(s21_decimal* num, int sign);
int s21_get_scale(s21_decimal num);
void s21_set_scale(s21_decimal* num, int scale_value);
int s21_get_bit(s21_decimal num, int bit);
void s21_set_bit(s21_decimal* num, int bit, unsigned value);
void s21_shift_left(s21_decimal* num);
void s21_normalize(s21_decimal* num1, s21_decimal* num2);



s21_decimal s21_binary_not(s21_decimal num);
int s21_binary_is_zero(s21_decimal num);
s21_decimal binary_add(s21_decimal num1, s21_decimal num2);
s21_big_decimal s21_big_binary_add(s21_big_decimal num1, s21_big_decimal num2);
s21_decimal binary_sub(s21_decimal num1, s21_decimal num2);
s21_big_decimal s21_big_binary_sub(s21_big_decimal num1, s21_big_decimal num2);
void s21_big_normalize(s21_decimal num1, s21_decimal num2, s21_big_decimal *num1b,
                          s21_big_decimal *num2b);


int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_add_help(s21_decimal num_1, s21_decimal num_2, s21_decimal* res);


int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
