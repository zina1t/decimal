#include "s21_decimal.h"

int main(void) {
    s21_decimal num1 = {{2147483647, 2147483647, 2147483647, 0}};
    s21_decimal num2 = {{0, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_add(num1, num2, &result);
    for (int i = 0; i < 4; i++) {
        printf("%d ", result.bits[i]);
    }
    return 0;
}