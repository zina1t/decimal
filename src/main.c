
#include "binary.h"
int main(void) {
    s21_decimal num1 = {{0, 0, 23, 0}};
    s21_decimal num2 = {{0, 0, 2, 0}};
    printf("%d", s21_decimal_compare(num1, num2));
   
}