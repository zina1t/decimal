#include "s21_decimal.h"

int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal* res) {
    s21_decimal temp1 = num1;
    s21_decimal temp2 = num2;
    align_scales(&temp1, &temp2);
    int sign1 = s21_get_sign(temp1);
    int sign2 = s21_get_sign(temp2);
    if (sign1 == sign2) {
        s21_decimal result = {0};
        int overflow = 0;
        for (int i = 0; i < 96; i++) {
            int bit1 = s21_get_bit(temp1, i);
            int bit2 = s21_get_bit(temp2, i);
            int sum = bit1 + bit2 + overflow;
            if (sum >= 2) {
                overflow = 1;
                sum -= 2;
            } else {
                overflow = 0;
            }
            s21_set_bit(&result, sum, i);
        }
        if (overflow != 0) {
            return (sign1 == 0) ? 1 : 2; // Overflow or underflow depending on sign
        }
        int scale = s21_get_scale(temp1);
        s21_set_scale(&result, scale);
        s21_set_sign(&result, sign1);
        *res = result;
    } else {
        if (s21_is_greater(temp1, temp2)) {
            s21_subtract(temp1, temp2, res);
        } else {
            s21_subtract(temp2, temp1, res);
        }
    }

    return 0; 
}