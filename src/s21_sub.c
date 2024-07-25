#include "s21_decimal.h"

int s21_sub(s21_decimal num1, s21_decimal num2, s21_decimal* res) {
    s21_decimal result = {0};
    int borrow = 0;
    
    // Get the signs of num1 and num2
    int sign1 = s21_get_sign(num1);
    int sign2 = s21_get_sign(num2);

    // If num2 is negative, convert it to positive and add to num1
    if (sign2) {
        s21_set_sign(&num2, 0); // make num2 positive
        s21_add(num1, num2, &result); // perform addition
    } else if (sign1) { // If num1 is negative, convert it to positive and subtract from num2
        s21_set_sign(&num1, 0); // make num1 positive
        s21_add(num1, num2, &result); // perform addition
        s21_set_sign(&result, 1); // set the result as negative
    } else {
        // Both num1 and num2 are positive or both are negative, proceed with subtraction
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
    }

    *res = result;
    return 0; 
}