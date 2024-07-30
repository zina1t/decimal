#include "s21_decimal.h"

int float_to_decimal(float f, s21_decimal* result) {
    int sign = 0;
    if (f < 0) {
        sign = 1;
        f = -f;
    }
    int scale = 0;
    while (f < 1) {
        f *= 10;
        scale++;
    }
    while (f >= 10) {
        f /= 10;
        scale--;
    }
    s21_decimal res = {0};
    for (int i = 0; i < 96; i++) {
        f *= 2;
        if (f >= 1) {
            res.bits[i / 32] |= 1 << (i % 32);
            f -= 1;
        }
    }
    s21_set_sign(&res, sign);
    s21_set_scale(&res, scale);
    *result = res;
    return 0;
}