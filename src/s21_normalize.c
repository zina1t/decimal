#include "s21_decimal.h"

void s21_normalize(s21_decimal* num1, s21_decimal* num2) {
  s21_decimal* temp;
  int diff;
  int flag = 0;
  if (s21_get_scale(*num1) < s21_get_scale(*num2)) {
    temp = num1;
    diff = s21_get_scale(*num2) - s21_get_scale(*num1);
  } else {
    temp = num2;
    diff = s21_get_scale(*num1) - s21_get_scale(*num2);
  }
  while (diff--) {
    s21_decimal x = {{10, 0, 0, 0}};
    flag = s21_mul(*temp, x, temp);
    if (flag) break;
    s21_set_scale(temp, s21_get_scale(*temp) + 1);
  }
}

/*
void s21_normalize(s21_decimal* num1, s21_decimal* num2) {
  int i = 0;
  while (s21_get_scale(*num1) != s21_get_scale(*num2)) {
    i++;
    if (s21_get_scale(*num1) < s21_get_scale(*num2)) {
      s21_set_scale(num1, i + 1);
    } else {
      s21_set_scale(num2, i + 1);
    }
  }
}
 мб работает
*/