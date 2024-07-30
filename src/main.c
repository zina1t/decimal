
#include "s21_decimal.h"
int main(void) {    
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 0.4999999999999999999999999999
    s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
    
    
    s21_decimal result = {{0, 0, 0, 0}};
    s21_add(decimal1, decimal2, &result);
    printf("error%d\n", s21_add(decimal1, decimal2, &result));
    for (int i = 0; i < 4; i++) {
        printf("%u\n", result.bits[i]);
    }
    //printf("%d\n", s21_is_less(decimal1, decimal2));
    return 0;
}

