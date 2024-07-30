
#include "s21_decimal.h"
int main(void) {    
    int i = -483648;
    s21_decimal result = {{0, 0, 0, 0}};
    int_to_decimal(i, &result);
    for (int i = 0; i < 4; i++) {
        printf("%u\n", result.bits[i]);
    }
    //printf("%d\n", s21_is_less(decimal1, decimal2));
    return 0;
}

