#ifndef SRC_BACKEND_SMARTCALC_H_
#define SRC_BACKEND_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_PI 3.14159265358979323846264338327950288
#define MAXN 1000

typedef enum s21_bool { s21_false, s21_true } s21_bool;

void s21_substr(char *str1, const char *str2, const char *str3);
int countOccurrences(char str[], char s[]);

typedef struct s21_char_stack {
  char data[MAXN];
  int top;
} s21_char_stack;

void init_char_stack(s21_char_stack *st);
void push_char(s21_char_stack *st, char x);
char last_char(s21_char_stack st);
void pop_char(s21_char_stack *st);

typedef struct s21_double_stack {
  double data[MAXN];
  int top;
} s21_double_stack;

void init_double_stack(s21_double_stack *st);
void push_double(s21_double_stack *st, double x);
double last_double(s21_double_stack st);
void pop_double(s21_double_stack *st);

s21_bool isOperator(char c);
s21_bool isFunction(char c);
int getPriority(char c);

void convert_string_to_number(char str[], int *pos, char ans[]);
void make_postfix(char str[], char postfix[], s21_bool *error, double x);
double calc_term(char sign, double x, double y, s21_bool *error);
double calc_func(char sign, double x, s21_bool *error);
double calc_from_postfix(char postfix[], s21_bool *error);
void convert_1_char(char str[], s21_bool *error);
void calc(char str[], double *answer, s21_bool *error, double x);

#endif  // SRC_BACKEND_SMARTCALC_H_