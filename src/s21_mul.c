#include "s21_decimal.h"

int s21_mul(s21_decimal num1, s21_decimal num2, s21_decimal* result) {
    int sign1 = s21_get_sign(num1);
    int sign2 = s21_get_sign(num2);
    s21_set_sign(&num1, 0);
    s21_set_sign(&num2, 0);
    s21_decimal res = {0};
    for (int i = 0; i < 96; i++) {
        if (s21_get_bit(num1, i)) {
            s21_decimal temp = num2;
            for (int j = 0; j < i; j++) {
                temp = *shift_left(&temp, 1);
            }
            s21_add(res, temp, &res);
        }
    }
    s21_set_sign(&res, sign1 ^ sign2);
    *result = res;
    return 0;
}