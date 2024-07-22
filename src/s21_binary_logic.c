#include "binary.h"

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

int s21_decimal_is_zero(s21_decimal num) {
  for (int i = 0; i < 4; i++) {
    if (num.bits[i] != 0) {
      return 0;
    }
  }
  return 1;
}

int s21_decimal_compare(s21_decimal num1, s21_decimal num2) { 
    for (int i = 3; i >= 0; i--) {
        if (num1.bits[i] > num2.bits[i]) {
        return 1;
        } else if (num1.bits[i] < num2.bits[i]) {
        return -1;
        }
    }
  return 0;
}

int s21_big_decimal_compare(s21_big_decimal num1, s21_big_decimal num2) {
    for (int i = 7; i >= 0; i--) {
        if (num1.bits[i] > num2.bits[i]) {
            return 1;
        } else if (num1.bits[i] < num2.bits[i]) {
            return -1;
        }
    }
    return 0;
}

