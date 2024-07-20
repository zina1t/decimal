#include "s21_decimal.h"

s21_big_decimal big_convert(s21_decimal src) {
    s21_big_decimal dst = {{0, 0, 0, 0, 0, 0, 0, 0}};
    for (int i = 0; i < 3; i++) {
        dst.bits[i] = src.bits[i];
    }
    dst.bits[7] = src.bits[3];
    return dst;
}

s21_decimal back_convert (s21_big_decimal src) {
    s21_decimal dst = {{0, 0, 0, 0}};
    for (int i = 0; i < 3; i++) {
        dst.bits[i] = src.bits[i]; 
    }
    dst.bits[3] = src.bits[7];
    return dst;
}