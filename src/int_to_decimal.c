#include "s21_decimal.h"

int int_to_decimal(int i, s21_decimal* result) {
    int sign = 0;
    if (i < 0) {
        sign = 1;
        i = -i;
    }
    s21_decimal res = {0};
    for (int j = 0; j < 96; j++) {
        if (i & 1) {
            res.bits[j / 32] |= 1 << (j % 32);
        }
        i >>= 1;
    }
    s21_set_sign(&res, sign);
    *result = res;
    return 0;
}