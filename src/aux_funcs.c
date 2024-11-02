#include "s21_decimal.h"

int s21_get_bit(s21_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}

void s21_set_sign_1(s21_decimal *dst, int is_negative) {
  if (is_negative) {
    dst->bits[3] |= (1u << 31);
  }
}

int s21_get_scale(s21_decimal value) { return (value.bits[3] >> 16) & 0xFF; }
int s21_get_scale_1(s21_decimal value) { return (value.bits[3] >> 16) & 0xFF; }

int s21_get_sign(s21_decimal value) {
  int result = !!(value.bits[3] & (1u << 31));
  return result;
}
int s21_get_sign_1(s21_decimal value) {
  return (value.bits[3] >> 31) & 1;  // Возвращает 1, если знак отрицательный
}

void s21_set_scale_1(s21_decimal *dst, int scale) {
  dst->bits[3] |= (scale << 16);
}

void s21_normalization(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_1 = s21_get_scale_1(*value_1);
  int scale_2 = s21_get_scale_1(*value_2);
  if (scale_1 > scale_2) {
    for (int i = 0; i < scale_1 - scale_2; i++) {
      for (int j = 0; j < 3; j++) {
        value_2->bits[j] *= 10;
      }
    }
  } else if (scale_1 < scale_2) {
    for (int i = 0; i < scale_2 - scale_1; i++) {
      for (int j = 0; j < 3; j++) {
        value_1->bits[j] *= 10;
      }
    }
  }
}

void s21_toggle_sign(s21_decimal *value) {
  // Инвертируем бит знака (31-й бит в четвертом блоке)
  value->bits[3] ^= (1U << 31);
}

void s21_clear_bits(s21_decimal *result) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
}

void s21_set_zero(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;  // Обнуляем все биты
  }
}

int s21_decimal_null(s21_decimal num) {
  for (int i = 0; i < 4; i++) {
    if (num.bits[i] != 0) return 0;
  }
  return 1;
}

void s21_shift_right(s21_decimal *value, int shift_count) {
  for (int i = 0; i < shift_count; i++) {
    // Сдвиг вправо на одну позицию
    for (int j = 0; j < 3; j++) {
      if (j < 2) {
        value->bits[j] >>= 1;
        if (value->bits[j + 1] & 1) {
          value->bits[j] |= (1u << 31);
        }
      } else {
        value->bits[j] >>= 1;
      }
    }
  }
}

// Получает индекс самого старшего бита, который установлен в 1
int s21_get_bit_last(s21_decimal value) {
  for (int i = 95; i >= 0; i--) {
    if (s21_get_bit(value, i)) {
      return i;
    }
  }
  return -1;  // Если все биты равны 0
}
int s21_get_bitLast(s21_decimal value) {
  int bitLast = 95;
  for (; (bitLast >= 0) && (!s21_get_bit(value, bitLast));) bitLast -= 1;
  return bitLast;
}
int s21_is_zero(s21_decimal value) {
  // Проверяем, что все биты всех элементов массива bits равны 0
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) {
    return 1;  // Число равно нулю
  }
  return 0;  // Число не равно нулю
}

void s21_shift_left(s21_decimal *value, int shift) {
  for (int i = 0; i < shift; i++) {
    // Сдвигаем биты влево
    unsigned int carry = 0;  // Переменная для хранения старшего бита
    for (int j = 0; j < 3; j++) {
      unsigned int next_carry =
          value->bits[j] >> 31;  // Старший бит для переноса
      value->bits[j] =
          (value->bits[j] << 1) | carry;  // Сдвиг влево с учётом переноса
      carry = next_carry;  // Обновляем перенос для следующего разряда
    }
  }
}

void s21_set_bit_1(s21_decimal *value, int position, int bit_value) {
  int index =
      position /
      32;  // Определяем, в каком из элементов массива хранится нужный бит
  int offset = position % 32;  // Определяем смещение внутри элемента

  if (bit_value) {
    value->bits[index] |= (1u << offset);  // Устанавливаем бит в 1
  } else {
    value->bits[index] &= ~(1u << offset);  // Устанавливаем бит в 0
  }
}

s21_decimal *s21_set_sign(s21_decimal *value, int bit) {
  value->bits[3] =
      (bit) ? (value->bits[3] | (1u << 31)) : (value->bits[3] & ~(1u << 31));
  return value;
}

s21_decimal *s21_set_bit(s21_decimal *value, int pos, int bit) {
  if (pos / 32 < 4 && bit)
    value->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 4 && !bit)
    value->bits[pos / 32] &= ~(1u << (pos % 32));
  return value;
}

s21_decimal *s21_set_scale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    int sign = s21_get_sign(*value);
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= scale << 16;
    sign ? s21_set_sign(value, 1) : value;
  }
  return value;
}

s21_decimal *decreaseScale(s21_decimal *value, int shift) {
  for (int y = 0; y < shift; y += 1) {
    unsigned long long overflow = value->bits[2];
    for (int x = 2; x >= 0; x -= 1) {
      value->bits[x] = overflow / 10;
      overflow =
          (overflow % 10) * (4294967295 + 1) + value->bits[x ? x - 1 : x];
    }
  }
  s21_set_scale(value, (s21_get_scale(*value) - shift));
  return value;
}

int s21_add_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int fres = 0, exp = 0;
  for (int i = 0; i < 96; i += 1) {
    int bitValue_1 = s21_get_bit(value_1, i),
        bitValue_2 = s21_get_bit(value_2, i);
    if (!bitValue_1 && !bitValue_2)
      exp ? s21_set_bit(result, i, (exp = 0) + 1) : s21_set_bit(result, i, 0);
    else if (bitValue_1 != bitValue_2)
      exp ? s21_set_bit(result, i, (exp = 1) - 1) : s21_set_bit(result, i, 1);
    else
      exp ? s21_set_bit(result, i, (exp = 1))
          : s21_set_bit(result, i, (exp = 1) - 1);
    if (i == 95 && exp == 1 && !s21_get_bit(value_1, 97) &&
        !s21_get_bit(value_2, 97))
      fres = 1;
  }
  return fres;
}

s21_decimal *increaseScale(s21_decimal *value, int shift) {
  if (s21_get_scale(*value) + shift < 29) {
    s21_set_scale(value, s21_get_scale(*value) + shift);
    s21_decimal auxValue_1 = *value, auxValue_2 = *value;
    if (s21_add_bit(*leftShift(&auxValue_1, 1), *leftShift(&auxValue_2, 3),
                    value))
      s21_set_bit(value, 96, 1);
  }
  return value;
}

s21_decimal *leftShift(s21_decimal *value, int shift) {
  if (!(s21_get_bitLast(*value) + shift > 95)) {
    for (int y = 0; y < shift; y += 1) {
      int bitTransfer_1 = s21_get_bit(*value, 31);
      int bitTransfer_2 = s21_get_bit(*value, 63);
      for (int x = 0; x < 3; x += 1) value->bits[x] <<= 1;
      if (bitTransfer_1) s21_set_bit(value, 32, 1);
      if (bitTransfer_2) s21_set_bit(value, 64, 1);
    }
  }
  return value;
}

void alignmentScale(s21_decimal *value_1, s21_decimal *value_2) {
  if (s21_get_scale(*value_1) != s21_get_scale(*value_2)) {
    if (s21_get_scale(*value_1) < s21_get_scale(*value_2)) {
      alignmentScale(value_2, value_1);
    } else {
      int scaleLow = s21_get_scale(*value_2),
          scaleHigh = s21_get_scale(*value_1);
      for (; (scaleHigh - scaleLow) && !s21_get_bit(*value_2, 96);
           scaleLow += 1)
        increaseScale(value_2, 1);
      for (; scaleHigh - scaleLow; scaleHigh -= 1) {
        decreaseScale(value_1, scaleHigh - scaleLow);
        s21_set_scale(value_1, scaleLow);
      }
    }
  }
}

s21_decimal *convert(s21_decimal *value) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal add = {{1, 0, 0, 0}};
  for (int x = 0; x < 3; x += 1) value->bits[x] = ~value->bits[x];
  s21_add_bit(*value, add, &result);
  for (int x = 0; x < 3; x += 1) value->bits[x] = result.bits[x];
  s21_set_bit(value, 97, 1);
  return value;
}

void s21_subtract_magnitude(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result) {
  if (!s21_is_greater(value_1, value_2)) {
    s21_set_zero(result);
    return;
  }

  int borrow = 0;

  for (int i = 0; i < 4; i++) {
    unsigned long long bit_1 = value_1.bits[i];
    unsigned long long bit_2 = value_2.bits[i] + borrow;

    if (bit_1 < bit_2) {
      bit_1 += 0x100000000;
      borrow = 1;
    } else {
      borrow = 0;
    }

    result->bits[i] = bit_1 - bit_2;
  }
}

void align_scales(s21_decimal *value_1, s21_decimal *value_2) {
  int scale1 = s21_get_scale_1(*value_1);
  int scale2 = s21_get_scale_1(*value_2);

  if (scale1 < scale2) {
    // Увеличиваем масштаб value_1
    for (int i = 0; i < scale2 - scale1; i++) {
      // Применяем смещение
      for (int j = 0; j < 3; j++) {
        value_1->bits[j] =
            (value_1->bits[j] << 1) | (value_1->bits[j + 1] >> 31);
      }
      value_1->bits[3] <<= 1;  // Сдвиг старшего бита
    }
    s21_set_scale_1(value_1, scale2);
  } else if (scale1 > scale2) {
    // Увеличиваем масштаб value_2
    for (int i = 0; i < scale1 - scale2; i++) {
      for (int j = 0; j < 3; j++) {
        value_2->bits[j] =
            (value_2->bits[j] << 1) | (value_2->bits[j + 1] >> 31);
      }
      value_2->bits[3] <<= 1;  // Сдвиг старшего бита
    }
    s21_set_scale_1(value_2, scale1);
  }
}

int s21_compare_magnitude(s21_decimal value_1, s21_decimal value_2) {
  // Получаем масштабы
  int scale_1 = s21_get_scale_1(value_1);
  int scale_2 = s21_get_scale_1(value_2);

  // Сравниваем масштабы
  if (scale_1 > scale_2) {
    return 1;  // value_1 больше
  } else if (scale_1 < scale_2) {
    return -1;  // value_2 больше
  }

  // Если масштабы равны, сравниваем биты
  for (int i = 3; i >= 0; i--) {
    if (value_1.bits[i] > value_2.bits[i]) {
      return 1;  // value_1 больше
    } else if (value_1.bits[i] < value_2.bits[i]) {
      return -1;  // value_2 больше
    }
  }

  return 0;  // Числа равны
}
