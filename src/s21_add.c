#include "s21_decimal.h"

/*
int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal* res) {
    int carry = 0;
    for (int i = 0; i < 4; i++) {
        unsigned int sum = num1.bits[i] + num2.bits[i] + carry;
        carry = sum >> 31;
        res->bits[i] = sum;
    }
    return carry;
}

int s21_add_help(s21_decimal num1, s21_decimal num2, s21_decimal* res) {
    s21_big_decimal big_num1;
    s21_big_decimal big_num2;
    int scale1 = s21_get_scale(num1);
    int scale2 = s21_get_scale(num2);
    s21_big_normalize(num1, num2, &big_num1, &big_num2);
    s21_big_decimal result = s21_big_binary_add(big_num1, big_num2);
}
*/
