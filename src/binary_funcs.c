#include "s21_decimal.h"



s21_decimal s21_binary_not(s21_decimal num) {
    s21_decimal res = {{0, 0, 0, 0}};
    for (int i = 0; i < 4; i++) {
        res.bits[i] = ~num.bits[i];
    }
    return res;
}

int s21_binary_is_zero(s21_decimal num) {
    int is_zero = 0;
    if (!num.bits[0] && !num.bits[1] && !num.bits[2] && !num.bits[3]) {
        is_zero = 1;
    }
    return is_zero;
}

s21_decimal binary_add(s21_decimal num1, s21_decimal num2) {
    s21_decimal res = num1;
    s21_decimal tmp = num2;
    while(!(s21_binary_is_zero(tmp))) {
        s21_decimal carry = s21_binary_and(res, tmp);
        res = s21_binary_xor(res, tmp);
        //tmp = s21_shift_left(carry, 1);
    }
    return res;
}

s21_big_decimal s21_big_binary_add(s21_big_decimal num1, s21_big_decimal num2) {
    s21_big_decimal res = num1;
    s21_big_decimal tmp = num2;
    while(!(s21_binary_is_zero(tmp))) {
        s21_decimal carry = s21_binary_and(res, tmp);
        res = s21_binary_xor(res, tmp);
        //tmp = s21_shift_left(carry, 1);
    }
    return res;
}

s21_decimal binary_sub(s21_decimal num1, s21_decimal num2) {
    s21_decimal res = num1;
    s21_decimal tmp = num2;
    while(!(s21_binary_is_zero(tmp))) {
        s21_decimal borrow = s21_binary_and(res, tmp);
        res = s21_binary_xor(res, tmp);
        //tmp = s21_shift_left(borrow, 1);
    }
    return res;
}

s21_big_decimal s21_big_binary_sub(s21_big_decimal num1, s21_big_decimal num2) {
    s21_big_decimal res = num1;
    s21_big_decimal tmp = num2;
    while(!(s21_binary_is_zero(tmp))) {
        s21_decimal borrow = s21_binary_and(res, tmp);
        res = s21_binary_xor(res, tmp);
        //tmp = s21_big_binary_shift_left(borrow, 1);
    }
    return res;
}

void s21_big_normalize(s21_decimal num1, s21_decimal num2, s21_big_decimal *num1b,
                          s21_big_decimal *num2b) {
                            int scale1 = s21_get_scale(num1);
                            int scale2 = s21_get_scale(num2);
                            s21_decimal temp1 = num1;
                            s21_decimal temp2 = num2;
                            temp1.bits[3] = 0;
                            temp2.bits[3] = 0;
                            if (scale1 < scale2) {
                                s21_set_scale(&temp1, scale2);
                                s21_set_scale(&temp2, scale2);
                            } else {
                                s21_set_scale(&temp1, scale1);
                                s21_set_scale(&temp2, scale1);
                            }
                            *num1b = s21_big_binary_shift_left(temp1, 96);
                            *num2b = s21_big_binary_shift_left(temp2, 96);
                          }