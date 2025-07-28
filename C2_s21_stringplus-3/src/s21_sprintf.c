#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  parameters p = {0};
  va_list va;
  va_start(va, format);
  char *begin = str;

  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
    } else {
      format++;
      initParameters(&p);
      format = parse(format, &p, va);
      p.specifier = *format;
      format++;

      char buff[BUFF_SIZE] = {'\0'};
      applySpecifier(buff, &p, va);

      for (s21_size_t i = 0; buff[i]; i++, str++) {
        *str = buff[i];
      }

      if (p.specifier == 'n') {
        int *n = va_arg(va, int *);
        *n = str - begin;
      }
    }
  }

  *str = '\0';
  va_end(va);

  return str - begin;
}

const char *parse(const char *format, parameters *p, va_list va) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' ||
         *format == '#') {
    switch (*format) {
      case '-':
        p->minusFlag = true;
        break;
      case '+':
        p->plusFlag = true;
        break;
      case ' ':
        p->spaceFlag = true;
        break;
      case '#':
        p->hashFlag = true;
        break;
      case '0':
        p->zeroFlag = true;
        break;
    }
    format++;
  }

  if (*format == '*') {
    format++;
    p->width = va_arg(va, int);
  } else if (s21_isDigit(*format)) {
    int width = *format - '0';
    format++;

    while (s21_isDigit(*format)) {
      width *= 10;
      width += *format - '0';
      format++;
    }

    p->width = width;
  }

  if (*format == '.') {
    p->hasDot = true;
    format++;

    if (*format == '*') {
      format++;
      p->precision = va_arg(va, int);
    } else {
      int precision = 0;
      p->hasDotWithoutNumber = true;
      while (s21_isDigit(*format)) {
        precision *= 10;
        precision += *format - '0';
        format++;
        p->hasDotWithoutNumber = false;
      }

      p->precision = precision;
    }
  }

  if (*format == 'h' || *format == 'l' || *format == 'L') {
    p->length = *format;
    format++;
  }

  return format;
}

void applySpecifier(char *str, parameters *p, va_list va) {
  switch (p->specifier) {
    case 'd':
      doInt(str, p, va);
      break;
    case 'i':
      doInt(str, p, va);
      break;
    case 'f':
      doFloat(str, p, va);
      break;
    case 'u':
      doUnsignedInt(str, p, va);
      break;
    case 's':
      doString(str, p, va);
      break;
    case 'c':
      doChar(str, p, va);
      break;
    case 'x':
      doHex(str, p, va);
      toLower(str);
      break;
    case 'X':
      doHex(str, p, va);
      break;
    case 'o':
      doOctal(str, p, va);
      break;
    case 'e':
      doExp(str, p, va);
      toLower(str);
      break;
    case 'E':
      doExp(str, p, va);
      break;
    case 'g':
      doG(str, p, va);
      toLower(str);
      break;
    case 'G':
      doG(str, p, va);
      break;
    case 'p':
      doPointer(str, p, va);
      toLower(str);
      break;
    case '%':
      str[0] = '%';
      break;
  }
}

void initParameters(parameters *p) {
  p->minusFlag = false;
  p->plusFlag = false;
  p->spaceFlag = false;
  p->zeroFlag = false;
  p->hashFlag = false;
  p->width = 0;
  p->hasDot = false;
  p->hasDotWithoutNumber = false;
  p->precision = 0;
  p->length = 0;
  p->specifier = 0;
}

void doString(char *str, parameters *p, va_list va) {
  char buff[BUFF_SIZE] = {'\0'};

  if (p->length == 'l') {
    // wchar_t *tmp = va_arg(va, wchar_t *);
    // wcstombs(buff, tmp, BUFF_SIZE);
  } else {
    char *tmp = va_arg(va, char *);
    s21_strcpy(buff, tmp);
  }

  if (p->hasDot == true) {
    buff[p->precision] = '\0';
  }

  s21_size_t len = s21_strlen(buff);
  int shift = p->width - len;

  if (p->minusFlag == true && shift > 0) {
    s21_strcpy(str, buff);
    s21_memset(str + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(str, ' ', shift);
    s21_strcpy(str + shift, buff);
  } else {
    s21_strcpy(str, buff);
  }
}

void doInt(char *str, parameters *p, va_list va) {
  long long val = va_arg(va, long long);

  switch (p->length) {
    case 0:
      val = (int)val;
      break;
    case 'h':
      val = (short)val;
      break;
  }

  if (!(p->precision == 0 && val == 0 && p->hasDot == true)) {
    s21_itoa(val, str, 10);
  }

  writePrecision(str, p);
  writeFlags(str, p);
  writeWidthToNumber(str, p);
}

void doFloat(char *str, parameters *p, va_list va) {
  long double val;

  if (p->length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }

  if (p->hasDot == false) {
    p->precision = 6;
  }

  s21_ftoa(val, str, p);
  writePrecision(str, p);
  writeFlags(str, p);
  writeWidthToFloatNumber(str, p);
}
void doG(char *str, parameters *p, va_list va) {
  long double val;

  if (p->length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }

  int precision = p->precision;

  if (p->hasDot == false) {
    p->precision = 6;
  }

  if (p->precision == 0) {
    p->precision = 1;
  }

  long double tempVal = val;
  int pow = 0;
  bool isE;

  if ((int)tempVal - tempVal) {
    while ((int)tempVal == 0) {
      pow--;
      tempVal *= 10;
    }
  }

  while ((int)tempVal / 10 != 0) {
    pow++;
    tempVal /= 10;
  }

  if (-4 <= pow && pow < p->precision) {
    isE = false;
  } else {
    isE = true;
  }

  if (isE == true) {
    if (p->hashFlag == true && p->hasDotWithoutNumber == true) {
      p->precision = p->precision - pow - 1;
    } else {
      p->precision = p->precision - 1;
    }

    char sign = (int)val == 0 ? '-' : '+';
    int pow2 = 0;
    while ((int)val == 0) {
      pow2++;
      val *= 10;
    }

    while ((int)val / 10 != 0) {
      pow2++;
      val /= 10;
    }

    s21_ftoa(val, str, p);
    if (!(p->hashFlag == true && p->hasDotWithoutNumber == false)) {
      removeZeros(str, p);
    }
    doMantissa(str, pow2, sign);
  } else {
    p->precision = p->precision - pow - 1;
    s21_ftoa(val, str, p);
    int right = s21_strlen(s21_strchr(str, '.')) - 1;
    if (!(p->hashFlag == true && right <= p->precision &&
          p->hasDotWithoutNumber == false)) {
      removeZeros(str, p);
    }
  }

  p->precision = precision;

  writeFlags(str, p);
  writeWidthToFloatNumber(str, p);
}

void doExp(char *str, parameters *p, va_list va) {
  long double val;

  if (p->length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }

  if (p->hasDot == false) {
    p->precision = 6;
  }

  int pow = 0;
  char sign = (int)val == 0 ? '-' : '+';

  while ((int)val == 0) {
    pow++;
    val *= 10;
  }

  while ((int)val / 10 != 0) {
    pow++;
    val /= 10;
  }

  s21_ftoa(val, str, p);
  doMantissa(str, pow, sign);
  writePrecision(str, p);
  writeFlags(str, p);
  writeWidthToFloatNumber(str, p);
}

void doPointer(char *str, parameters *p, va_list va) {
  void *ptr = va_arg(va, void *);
  if (ptr != s21_NULL) {
    unsigned long long val = (unsigned long long)ptr;
    s21_itoa(val, str, 16);
    writePrecision(str, p);
    write0andX(str);
    writeWidthToNumber(str, p);
  } else {
#ifdef __APPLE__
    s21_strcat(str, "0x0");
#endif
#ifdef __linux__
    s21_strcat(str, "(nil)");
#endif
  }
}

void doChar(char *str, parameters *p, va_list va) {
  char buff[BUFF_SIZE] = {'\0'};

  char c = va_arg(va, int);
  char s[10] = {'\0'};
  s[0] = c;
  s21_strcat(buff, s);

  s21_size_t len = s21_strlen(buff);

  if (p->minusFlag == true) {
    s21_strcat(str, buff);
    writeWidthToString(str, p, len);
  } else {
    writeWidthToString(str, p, len);
    s21_strcat(str, buff);
  }
}
void doUnsignedInt(char *str, parameters *p, va_list va) {
  unsigned long long val = va_arg(va, unsigned long long);

  switch (p->length) {
    case 0:
      val = (unsigned int)val;
      break;
    case 'h':
      val = (unsigned short)val;
      break;
  }

  if (!(p->precision == 0 && val == 0 && p->hasDot == true)) {
    s21_itoa(val, str, 10);
  }

  writePrecision(str, p);
  writeWidthToNumber(str, p);
}

void doMantissa(char *str, int pow, char sign) {
  int len = s21_strlen(str);
  str[len] = 'E';
  str[len + 1] = sign;
  str[len + 3] = pow % 10 + '0';
  pow /= 10;
  str[len + 2] = pow % 10 + '0';
  str[len + 4] = '\0';
}

void removeZeros(char *str, parameters *p) {
  int i = s21_strlen(str) - 1;

  while (i > 0) {
    if (str[i] == '0') {
      str[i] = '\0';
      i--;
    } else {
      break;
    }
  }
  if (p->hashFlag == false) {
    if (str[i] == '.') {
      str[i] = '\0';
    }
  }
}

void writePrecision(char *str, parameters *p) {
  int precision = p->precision - s21_strlen(str);

  if (precision > 0) {
    char buff[BUFF_SIZE] = {'\0'};
    int minus = 0;

    if (str[0] == '-') {
      str[0] = '0';
      minus++;
    }

    s21_memset(buff, '0', precision + minus);
    s21_strcpy(buff + precision + minus, str);

    if (minus == 1) {
      buff[0] = '-';
    }

    s21_strcpy(str, buff);
  }
}

void writeWidthToNumber(char *str, parameters *p) {
  int width = p->width - s21_strlen(str);

  if (width > 0) {
    char buff[BUFF_SIZE] = {'\0'};

    if (p->minusFlag == false) {
      char c;

      if (p->hasDot == false && p->zeroFlag == true) {
        c = '0';
      } else {
        c = ' ';
      }

      s21_memset(buff, c, width);
      s21_strcpy(buff + width, str);
    } else {
      s21_strcpy(buff, str);
      s21_memset(buff + s21_strlen(buff), ' ', width);
    }
    s21_strcpy(str, buff);
  }
}

void writeWidthToString(char *str, parameters *p, int len) {
  int width = p->width - len;
  while (width > 0) {
    s21_strcat(str, " ");
    width--;
  }
}

void writeWidthToFloatNumber(char *str, parameters *p) {
  int width = p->width - s21_strlen(str);

  if (width > 0) {
    char buff[BUFF_SIZE] = {'\0'};

    if (p->minusFlag == false) {
      char c;

      if (p->zeroFlag == true) {
        c = '0';
      } else {
        c = ' ';
      }

      s21_memset(buff, c, width);
      s21_strcpy(buff + width, str);
    } else {
      s21_strcpy(buff, str);
      s21_memset(buff + s21_strlen(buff), ' ', width);
    }
    s21_strcpy(str, buff);
  }
}

void writeFlags(char *str, parameters *p) {
  if (str[0] != '-') {
    char buff[BUFF_SIZE] = {'\0'};

    if (p->plusFlag == true) {
      buff[0] = '+';
      s21_strcpy(buff + 1, str);
      s21_strcpy(str, buff);
    } else if (p->spaceFlag == true) {
      buff[0] = ' ';
      s21_strcpy(buff + 1, str);
      s21_strcpy(str, buff);
    }
  }
}

void doOctal(char *str, parameters *p, va_list va) {
  unsigned long long val = va_arg(va, unsigned long long);

  switch (p->length) {
    case 0:
      val = (unsigned int)val;
      break;
    case 'h':
      val = (unsigned short)val;
      break;
  }

  s21_itoa(val, str, 8);
  int precision = p->precision - s21_strlen(str);
  writePrecision(str, p);

  if (val != 0 && p->hashFlag == true && precision <= 0) {
    s21_memmove(str + 1, str, s21_strlen(str));
    str[0] = '0';
  }

  writeWidthToNumber(str, p);
}

void doHex(char *str, parameters *p, va_list va) {
  unsigned long long val = va_arg(va, unsigned long long);

  switch (p->length) {
    case 0:
      val = (unsigned int)val;
      break;
    case 'h':
      val = (unsigned short)val;
      break;
  }

  s21_itoa(val, str, 16);
  writePrecision(str, p);

  if (val != 0 && p->hashFlag == true) {
    write0andX(str);
  }

  writeWidthToNumber(str, p);
}

void write0andX(char *str) {
  s21_memmove(str + 2, str, s21_strlen(str));

  str[0] = '0';
  str[1] = 'X';
}

char *s21_itoa(long long val, char *str, int base) {
  int i = 0;

  bool abs = val < 0 ? 1 : 0;
  val = abs ? -val : val;

  while (val > 0) {
    long long num = val % base;

    if (num >= 10) {
      str[i] = 65 + (num - 10);
    } else {
      str[i] = 48 + num;
    }

    val = val / base;

    i++;
  }

  if (i == 0) {
    str[i++] = '0';
  }

  if (abs == true && base == 10) {
    str[i++] = '-';
  }

  str[i] = '\0';

  return s21_reverseArray(str, 0, i - 1);
}

char *s21_ftoa(long double val, char *str, parameters *p) {
  char buff[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool neg = val < 0 ? 1 : 0;
  val = neg ? val * -1 : val;
  long double l = 0, r = modfl(val, &l);

  if (p->precision == 0) {
    l = roundl(val);
    r = 0;
  }

  char fractions[BUFF_SIZE] = {'\0'};

  for (int i = 0; i < p->precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }

  long long right = roundl(r), left = l;

  if (!right) {
    for (int i = 0; i < p->precision; idx--, i++) buff[idx] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, idx--, i--)
      buff[idx] = (int)(right % 10 + 0.05) + '0';
  }

  if ((p->hasDot && p->precision != 0) || (int)r || (!p->hasDot && val == 0) ||
      s21_strlen(fractions) || (p->hasDot == true && p->hashFlag == true)) {
    buff[idx--] = '.';
  }

  if (!left) {
    buff[idx] = '0';
    idx--;
  } else {
    for (; left; left /= 10, idx--) buff[idx] = (int)(left % 10) + '0';
  }

  for (int i = 0; buff[idx + 1]; idx++, i++) {
    if (neg && i == 0) {
      str[i] = '-';
      i++;
    }
    str[i] = buff[idx + 1];
  }

  return str;
}

char *s21_reverseArray(char *buff, int i, int j) {
  while (i < j) {
    s21_swap(&buff[i++], &buff[j--]);
  }

  return buff;
}

void s21_swap(char *x, char *y) {
  char t = *x;
  *x = *y;
  *y = t;
}

int s21_isDigit(char c) { return (c >= '0' && c <= '9'); }

void toLower(char *str) {
  while (*str) {
    if (*str >= 'A' && *str <= 'Z') {
      *str = *str + 32;
    }
    str++;
  }
}
