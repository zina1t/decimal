
#include "s21_decimal.h"
int main(void) {    
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    // -0.8228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    
    s21_decimal result = {{0, 0, 0, 0}};
    s21_mul(decimal1, decimal2, &result);
    printf("error%d\n", s21_mul(decimal1, decimal2, &result));
    for (int i = 0; i < 4; i++) {
        printf("%u\n", result.bits[i]);
    }
    //printf("%d\n", s21_is_less(decimal1, decimal2));
    return 0;
}

