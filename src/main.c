#include "s21_decimal.h"

int main(void) {
    s21_decimal num1 = {{, 0b00000, 0b11101, 0b10011}};
    for (int i = 0; i < 4; i++) {
        printf("%d", s21_get_bit(num1, i));
    }
    return 0;
}