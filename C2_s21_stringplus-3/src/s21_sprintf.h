#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <math.h>
#include <stdarg.h>

#include "s21_string.h"

#define BUFF_SIZE 4096

typedef struct {
  bool minusFlag;
  bool plusFlag;
  bool spaceFlag;
  bool zeroFlag;
  bool hashFlag;
  int width;
  bool hasDot;
  bool hasDotWithoutNumber;
  int precision;
  char length;
  char specifier;
} parameters;

int s21_sprintf(char *str, const char *format, ...);
const char *parse(const char *format, parameters *p, va_list va);
void applySpecifier(char *buff, parameters *p, va_list va);
char *s21_itoa(long long val, char *str, int base);
char *s21_ftoa(long double val, char *str, parameters *p);
int s21_isDigit(char c);
void s21_swap(char *x, char *y);
char *s21_reverseArray(char *buff, int i, int j);
void doInt(char *buff, parameters *p, va_list va);
void doUnsignedInt(char *str, parameters *p, va_list va);
void doString(char *str, parameters *p, va_list va);
void doChar(char *str, parameters *p, va_list va);
void doFloat(char *str, parameters *p, va_list va);
void doHex(char *str, parameters *p, va_list va);
void doOctal(char *str, parameters *p, va_list va);
void doExp(char *str, parameters *p, va_list va);
void doG(char *str, parameters *p, va_list va);
void doPointer(char *str, parameters *p, va_list va);
void doMantissa(char *str, int pow, char sign);
void writeWidthToNumber(char *str, parameters *p);
void writeWidthToFloatNumber(char *str, parameters *p);
void writeWidthToString(char *str, parameters *p, int len);
void writePrecision(char *str, parameters *p);
void writeFlags(char *str, parameters *p);
void write0andX(char *str);
void toLower(char *str);
void removeZeros(char *str, parameters *p);
void initParameters(parameters *p);

#endif  // SRC_S21_SPRINTF_H_
