#include "s21_decimal.h"
#include <stdio.h>

// Helper function to add two 32-bit integers with carry
int add_uint32(unsigned *result, unsigned a, unsigned b, int carry) {
    unsigned long long sum = (unsigned long long)a + b + carry;
    *result = (unsigned)sum;
    return (sum >> 32) & 1;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    // Ensure result is zeroed
    for (int i = 0; i < 4; ++i) {
        result->bits[i] = 0;
    }

    // Normalize scales
    s21_decimal temp1 = value_1;
    s21_decimal temp2 = value_2;
    s21_normalize(&temp1, &temp2);

    // Check signs
    int sign1 = s21_get_sign(temp1);
    int sign2 = s21_get_sign(temp2);
    int scale1 = s21_get_scale(temp1);
    int scale2 = s21_get_scale(temp2);

    // Ensure same scale
    if (scale1 != scale2) {
        if (scale1 < scale2) {
            s21_decimal multiplier = {{1, 0, 0, 0}};
            for (int i = scale1; i < scale2; ++i) {
                multiplier.bits[0] *= 10;
            }
            s21_mul(temp1, multiplier, &temp1);
            s21_set_scale(&temp1, scale2);
        } else {
            s21_decimal multiplier = {{1, 0, 0, 0}};
            for (int i = scale2; i < scale1; ++i) {
                multiplier.bits[0] *= 10;
            }
            s21_mul(temp2, multiplier, &temp2);
            s21_set_scale(&temp2, scale1);
        }
    }

    // Check if the signs are different
    if (sign1 != sign2) {
        // Subtract the smaller from the larger
        if (sign1) {
            s21_decimal temp = temp1;
            temp1 = temp2;
            temp2 = temp;
        }
        s21_decimal result_temp;
        s21_sub(temp1, temp2, &result_temp);
        s21_set_sign(&result_temp, sign1);
        *result = result_temp;
        return 0;
    }

    // Add the values
    int carry = 0;
    for (int i = 0; i < 3; ++i) {
        carry = add_uint32(&result->bits[i], temp1.bits[i], temp2.bits[i], carry);
    }
    result->bits[3] = temp1.bits[3] + temp2.bits[3] + carry;

    // Set the scale and sign of the result
    s21_set_scale(result, scale1);
    s21_set_sign(result, sign1);

    return 0;
}
