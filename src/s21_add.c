#include "s21_decimal.h"

int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal* res) {
    s21_decimal temp1 = num1;
    s21_decimal temp2 = num2;
    align_scales(&temp1, &temp2);
    int sign1 = s21_get_sign(temp1);
    int sign2 = s21_get_sign(temp2);
    if (sign1 == sign2) {
        s21_decimal result = {0};
        int overflow = 0;
        for (int i = 0; i < 96; i++) {
            int bit1 = s21_get_bit(temp1, i);
            int bit2 = s21_get_bit(temp2, i);
            int sum = bit1 + bit2 + overflow;
            if (sum >= 2) {
                overflow = 1;
                sum -= 2;
            } else {
                overflow = 0;
            }
            s21_set_bit(&result, sum, i);
        }
        if (overflow != 0) {
            return (sign1 == 0) ? 1 : 2; // Overflow or underflow depending on sign
        }
        int scale = s21_get_scale(temp1);
        s21_set_scale(&result, scale);
        s21_set_sign(&result, sign1);
        *res = result;
    } else {
        if (s21_is_greater(temp1, temp2)) {
            printf("temp1 is greater\n");
            s21_set_sign(&temp2, 0);
            s21_sub(temp1, temp2, res);
        } else {
            printf("temp2 is greater\n");
            s21_sub(temp2, temp1, res);
        }
    }

    return 0; 
}


/*

79228162514264337593543950335 
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
-7922816251426433759354395033.5
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
71305346262837903834189555302
    s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};
count error

79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
-0.5
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
79228162514264337593543950334
    s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
count error


79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
0.4999999999999999999999999999
    s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
79228162514264337593543950335
    s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
error 1, but should be 0

*/