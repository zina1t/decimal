
#include "s21_decimal.h"
int main(void) {
    s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0x0}};
    s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_sub(decimal1, decimal2, &result);
    printf("error%d\n", s21_sub(decimal1, decimal2, &result));
    for (int i = 0; i < 4; i++) {
        printf("%u\n", result.bits[i]);
    }
    //printf("%d\n", s21_is_less(decimal1, decimal2));
    return 0;
}