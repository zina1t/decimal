#include "s21_decimal.h"

int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal* res) {
    s21_decimal temp1 = num1;
    s21_decimal temp2 = num2;

    // Align scales of both numbers
    align_scales(&temp1, &temp2);

    // Initialize result
    s21_decimal result = {0};
    int carry = 0;

    // Add bit by bit
    for (int i = 0; i < 96; i++) {
        int bit1 = s21_get_bit(temp1, i);
        int bit2 = s21_get_bit(temp2, i);
        int sum = bit1 + bit2 + carry;

        if (sum >= 2) {
            carry = 1;
            sum -= 2;
        } else {
            carry = 0;
        }

        s21_set_bit(&result, sum, i);
    }

    // Check for overflow and underflow
    int sign1 = s21_get_sign(temp1);
    int sign2 = s21_get_sign(temp2);

    if (carry != 0) {
        if (sign1 == sign2) {
            return (sign1 == 0) ? 1 : 2; // Overflow or underflow depending on sign
        }
    }

    // Set the scale of the result
    int scale = s21_get_scale(temp1);
    s21_set_scale(&result, scale);

    // Set the sign of the result
    if (sign1 == sign2) {
        s21_set_sign(&result, sign1);
    } else {
        // Handle mixed signs by comparing magnitudes
        if (s21_get_last_bit(temp1) > s21_get_last_bit(temp2)) {
            s21_set_sign(&result, sign1);
        } else {
            s21_set_sign(&result, sign2);
        }
    }

    *res = result;
    return 0; // Successful addition
}
