#include "s21_decimal.h"

int s21_sub(s21_decimal num1, s21_decimal num2, s21_decimal* res) {
    s21_decimal result = {0};
    int borrow = 0;
    align_scales(&num1, &num2);
    int magnitude_comparison = compare_magnitude(num1, num2);
    if (magnitude_comparison < 0) {
        s21_decimal temp = num1;
        num1 = num2;
        num2 = temp;
    }
    for (int i = 0; i < 96; i++) {
        int bit1 = s21_get_bit(num1, i);
        int bit2 = s21_get_bit(num2, i);
        int diff = bit1 - bit2 - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        s21_set_bit(&result, diff, i);
    }
    int scale = s21_get_scale(num1);
    s21_set_scale(&result, scale);
    if (magnitude_comparison < 0) {
        s21_set_sign(&result, s21_get_sign(num2));
    } else {
        s21_set_sign(&result, s21_get_sign(num1));
    }
    *res = result;
    return 0; 
}