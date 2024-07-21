#include "s21_decimal.h"

s21_decimal s21_binary_and(s21_decimal num1, s21_decimal num2, s21_decimal* res) {
    s21_decimal res = {{0, 0, 0, 0}};
    for (int i = 0; i < 4; i++) {
        res->bits[i] = num1.bits[i] & num2.bits[i];
    }
    return res;
}

s21_decimal s21_binary_or(s21_decimal num1, s21_decimal num2, s21_decimal* res) {
    s21_decimal res = {{0, 0, 0, 0}};
    for (int i = 0; i < 4; i++) {
        res->bits[i] = num1.bits[i] | num2.bits[i];
    }
    return res;
}

s21_decimal s21_binary_xor(s21_decimal num1, s21_decimal num2, s21_decimal* res) {
    s21_decimal res = {{0, 0, 0, 0}};
    for (int i = 0; i < 4; i++) {
        res->bits[i] = num1.bits[i] ^ num2.bits[i];
    }
    return res;
}

s21_decimal s21_binary_not(s21_decimal num, s21_decimal* res) {
    s21_decimal res = {{0, 0, 0, 0}};
    for (int i = 0; i < 4; i++) {
        res->bits[i] = ~num.bits[i];
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
        tmp = s21_binary_shift_left(carry, 1);
    }
    return res;
}

s21_big_decimal s21_big_binary_add(s21_big_decimal num1, s21_big_decimal num2) {
    s21_big_decimal res = num1;
    s21_big_decimal tmp = num2;
    while(!(s21_big_binary_is_zero(tmp))) {
        s21_big_decimal carry = s21_big_binary_and(res, tmp);
        res = s21_big_binary_xor(res, tmp);
        tmp = s21_big_binary_shift_left(carry, 1);
    }
    return res;
}