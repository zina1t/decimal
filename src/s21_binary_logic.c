#include "binary.h"
#include "helpers.h"

s21_decimal s21_binary_and(s21_decimal num1, s21_decimal num2) {
    s21_decimal res = {{0, 0, 0, 0}};
    for (int i = 0; i < 4; i++) {
        res.bits[i] = num1.bits[i] & num2.bits[i];
    }
    return res;
}

s21_decimal s21_binary_or(s21_decimal num1, s21_decimal num2) {
    s21_decimal res = {{0, 0, 0, 0}};
    for (int i = 0; i < 4; i++) {
        res.bits[i] = num1.bits[i] | num2.bits[i];
    }
    return res;
}

s21_decimal s21_binary_xor(s21_decimal num1, s21_decimal num2) {
    s21_decimal res = {{0, 0, 0, 0}};
    for (int i = 0; i < 4; i++) {
        res.bits[i] = num1.bits[i] ^ num2.bits[i];
    }
    return res;
}