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


int s21_get_sign(s21_decimal num);
void s21_set_sign(s21_decimal* num, int sign);

int s21_get_scale(s21_decimal num);
void s21_set_scale(s21_decimal* num, int scale_value);

int s21_get_bit(int num, int bit);
int s21_set_bit(int num, int bit);
int s21_reset_bit(int num, int bit);
s21_decimal decimal_set_bit(s21_decimal num, int bit);
int get_decimal_bit(s21_decimal num, int bit);
int s21_not_zero_bit(s21_decimal num);
int s21_correct_decimal(s21_decimal num);