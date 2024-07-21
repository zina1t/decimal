#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
    int carry = 0;
    for (int i = 0; i < 4; i++) {
        unsigned int sum = value_1.bits[i] + value_2.bits[i] + carry;
        carry = sum >> 31;
        result->bits[i] = sum;
    }
    return carry;
}