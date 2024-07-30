#include "s21_decimal.h"

int int_to_decimal(int i, s21_decimal* result) {
    int sign = 0;
    if (i < 0) {
        sign = 1;
        if (i != INT_MIN) {
            i = -i;
        }
    } else {
        sign = 0;
    }
    result->bits[0] = i;
    s21_set_sign(result, sign);
    return 0;
}