#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define S21_DECIMAL_MAX 79228162514264337593543950335.0
#define S21_DECIMAL_MIN -79228162514264337593543950335.0

#include <assert.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef enum { FALSE, TRUE } res;

int s21_is_greater(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_from_s21_decimal_float(s21_decimal src, float *dst);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal *res);
int s21_get_bit(s21_decimal value, int bit);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_from_s21_decimalo_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

int s21_get_bit(s21_decimal value, int bit);
int s21_get_scale(s21_decimal value);
int s21_get_sign(s21_decimal value);
void s21_toggle_sign(s21_decimal *value);
void s21_clear_bits(s21_decimal *result);
void s21_set_zero(s21_decimal *value);
int s21_decimal_null(s21_decimal num);
void s21_shift_right(s21_decimal *value, int shift_count);
int s21_get_bit_last(s21_decimal value);
int s21_get_bitLast(s21_decimal value);
int s21_is_zero(s21_decimal value);
void s21_shift_left(s21_decimal *value, int shift);
void s21_set_bit_1(s21_decimal *value, int position, int bit_value);
s21_decimal *s21_set_sign(s21_decimal *value, int bit);
s21_decimal *s21_set_bit(s21_decimal *value, int pos, int bit);
s21_decimal *s21_set_scale(s21_decimal *value, int scale);
s21_decimal *decreaseScale(s21_decimal *value, int shift);
int s21_add_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_decimal *increaseScale(s21_decimal *value, int shift);
s21_decimal *leftShift(s21_decimal *value, int shift);
void alignmentScale(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal *convert(s21_decimal *value);
void s21_subtract_magnitude(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);
int s21_get_scale_1(s21_decimal value);
void s21_set_sign_1(s21_decimal *dst, int is_negative);
void s21_set_scale_1(s21_decimal *dst, int scale);
void s21_normalization(s21_decimal *value_1, s21_decimal *value_2);
int s21_get_sign_1(s21_decimal value);
void align_scales(s21_decimal *value_1, s21_decimal *value_2);
int s21_compare_magnitude(s21_decimal value_1, s21_decimal value_2);

void setBit(s21_decimal *dec, int bit_position, int bit_value);
void setScale(s21_decimal *dec, int new_scale);
void setSign(s21_decimal *dec, int sign);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int getSign(s21_decimal dec);

#endif
