#include "s21_decimal.h"

// Функция для сложения двух s21_decimal
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Проверка на переполнение
  s21_decimal zero = {{0, 0, 0, 0}};
  *result = zero;

  // Определяем знаки
  int sign1 = s21_get_sign_1(value_1);
  int sign2 = s21_get_sign_1(value_2);

  // Устанавливаем все числа положительными для удобства
  s21_set_sign_1(&value_1, 0);
  s21_set_sign_1(&value_2, 0);

  // Выравнивание по масштабу (scale)
  align_scales(&value_1, &value_2);

  // Сложение
  s21_decimal sum = zero;
  unsigned long long carry = 0;  // Перенос
  for (int i = 0; i < 96; i++) {
    // Суммируем биты с учетом переноса
    unsigned long long bit_sum =
        s21_get_bit(value_1, i) + s21_get_bit(value_2, i) + carry;
    carry = bit_sum >> 1;  // Перенос в следующий бит
    s21_set_bit_1(&sum, i, bit_sum & 1);
  }

  // Обработка переноса
  if (carry) {
    return 1;  // Переполнение
  }

  // Установка масштаба (scale) результата
  int result_scale = s21_get_scale_1(value_1);
  s21_set_scale_1(&sum, result_scale);

  // Установка знака результата
  if (sign1 == sign2) {
    s21_set_sign_1(&sum, sign1);
  } else {
    // Если знаки разные, нужно выполнить вычитание
    if (s21_is_greater(value_1, value_2)) {
      s21_sub(value_1, value_2, &sum);
      s21_set_sign_1(&sum, sign1);
    } else {
      s21_sub(value_2, value_1, &sum);
      s21_set_sign_1(&sum, sign2);
    }
  }

  *result = sum;
  return 0;  // Успешное выполнение
}