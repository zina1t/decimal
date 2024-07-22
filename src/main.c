
#include "binary.h"
int main(void) {
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_add(decimal1, decimal2, &result);
    printf("error%d\n", s21_add(decimal1, decimal2, &result));
    for (int i = 0; i < 4; i++) {
        printf("%u\n", result.bits[i]);
    }
    return 0;
}