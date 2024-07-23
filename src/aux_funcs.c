#include "s21_decimal.h"

int s21_get_bit(s21_decimal num, int bit) { 
  return !!(num.bits[bit /32] & (1U << (bit % 32))); 
}

int s21_get_last_bit(s21_decimal num) {
  int last = 95;
  for (; (last >= 0) && (!s21_get_bit(num, last));) last -= 1;
  return last;
}

s21_decimal* s21_set_bit(s21_decimal* num, int bit, int pos) { 
   if (pos / 32 < 4 && bit)
    num->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 4 && !bit)
    num->bits[pos / 32] &= ~(1u << (pos % 32));
  return num;
}

int s21_reset_bit(int num, int bit) { 
  return (num & ~(1U << bit)); 
}

int s21_get_sign(s21_decimal num) { 
  return !!(num.bits[3] & (1u << 31));;
}

void s21_set_sign(s21_decimal *num, int sign) {
  if (sign) {
    num->bits[3] = num->bits[3] | (1u << 31);
  } else {
    num->bits[3] = num->bits[3] & ~(1u << 31);
  }
}

int s21_get_scale(s21_decimal num) {
  return (char)(num.bits[3] >> 16);
}

void s21_set_scale(s21_decimal* num, int scale_value) {
  num->bits[3] = num->bits[3] & 0xFF00FFFF;
  num->bits[3] = num->bits[3] | (scale_value << 16);
}


s21_decimal* shift_left(s21_decimal* num, int shift) {
   if (!(s21_get_last_bit(*num) + shift > 95)) {
    for (int y = 0; y < shift; y += 1) {
      int bit1 = s21_get_bit(*num, 31);
      int bit2 = s21_get_bit(*num, 63);
      for (int x = 0; x < 3; x += 1) num->bits[x] <<= 1;
      if (bit1) s21_set_bit(num, 32, 1);
      if (bit2) s21_set_bit(num, 64, 1);
    }
  }
  return num;
}

void align_scales(s21_decimal *num1, s21_decimal *num2) {
    int scale1 = s21_get_scale(*num1);
    int scale2 = s21_get_scale(*num2);
    while (scale1 > scale2) {
        *num2 = *shift_left(num2, 1);
        scale2++;
    }
    while (scale2 > scale1) {
        *num1 = *shift_left(num1, 1);
        scale1++;
    }
}

int s21_decimal_null(s21_decimal num) {
  for (int i = 0; i < 4; i++) {
    if (num.bits[i] != 0) return 0;
  }
  return 1;
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int res = 0;
  int sign_a = s21_get_sign(num1), sign_b = s21_get_sign(num2);
  if (!(s21_decimal_null(num1) && s21_decimal_null(num2))) {
    if (sign_a != sign_b) {
      if (sign_a == 0) {
        res = 1;
      } else {
        res = 0;
      }
    } else {
      align_scales(&num1, &num2);
      for (int i = 95; i >= 0; i--) {
        int bit_a = s21_get_bit(num1, i), bit_b = s21_get_bit(num2, i);
        if (bit_a != bit_b) {
          if (bit_a != 0) {
            res = (sign_a == 0) ? 1 : 0;
            break;
          } else {
            res = (sign_a == 0) ? 0 : 1;
            break;
          }
        }
      }
    }
  }
  return res;
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int res = 1;
  int sign_a = s21_get_sign(num1), sign_b = s21_get_sign(num2);
  if (!(s21_decimal_null(num1) && s21_decimal_null(num2))) {
    if (sign_a == sign_b) {
      align_scales(&num1, &num2);
      for (int i = 95; i >= 0; i--) {
        int bit_a = s21_get_bit(num1, i), bit_b = s21_get_bit(num2, i);
        if (bit_a != bit_b) {
          res = 0;
          break;
        }
      }
    } else {
      res = 0;
    }
  }
  return res;
}

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int res = 0;
  int sign_a = s21_get_sign(num1), sign_b = s21_get_sign(num2);
  if (!(s21_decimal_null(num1) && s21_decimal_null(num2))) {
    if (sign_a != sign_b) {
      if (sign_a == 0) {
        res = 0;
      } else {
        res = 1;
      }
    } else {
      align_scales(&num1, &num2);
      for (int i = 95; i >= 0; i--) {
        int bit_a = s21_get_bit(num1, i), bit_b = s21_get_bit(num2, i);
        if (bit_a != bit_b) {
          if (bit_a != 0) {
            res = (sign_a == 0) ? 0 : 1;
            break;
          } else {
            res = (sign_a == 0) ? 1 : 0;
            break;
          }
        }
      }
    }
  }
  return res;
}

s21_decimal* convert(s21_decimal* num) {
  s21_decimal res = {0};
  int scale = s21_get_scale(*num);
  int sign = s21_get_sign(*num);
  int last = s21_get_last_bit(*num);
  for (int i = 0; i < 96; i++) {
    if (i <= last) {
      s21_set_bit(&res, s21_get_bit(*num, i), i);
    } else {
      s21_set_bit(&res, 0, i);
    }
  }
  s21_set_scale(&res, scale);
  s21_set_sign(&res, sign);
  *num = res;
  return num;
}

int compare_magnitude(s21_decimal num1, s21_decimal num2) {
    for (int i = 95; i >= 0; i--) {
        int bit1 = s21_get_bit(num1, i);
        int bit2 = s21_get_bit(num2, i);
        if (bit1 != bit2) {
            return bit1 - bit2;
        }
    }
    return 0;
}

s21_decimal s21_negate(s21_decimal num) {
    s21_set_sign(&num, !s21_get_sign(num));
    return num;
}