#include "s21_decimal.h"

int main(void) {
    s21_decimal num1 = {{1, 20, 3, 1}};
    s21_decimal num2 = {{4, 4, 4, 1}};
    s21_decimal result = {{1, 1, 1, 1}};
    s21_add(num1, num2, &result);
    for (int i = 0; i < 4; i++) {
        printf("%u ", result.bits[i]);
    }
    return 0;
}