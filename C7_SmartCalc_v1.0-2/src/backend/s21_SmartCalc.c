#include "s21_SmartCalc.h"

void s21_substr(char *str1, const char *str2, const char *str3) {
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  int len3 = strlen(str3);

  char temp[MAXN];

  int i, j, k;
  i = j = k = 0;

  while (i < len1) {
    if (str1[i] == str2[0]) {
      j = 0;
      int initial_i = i;
      while (i < len1 && str1[i] == str2[j]) {
        i++;
        j++;
      }
      if (j == len2) {
        for (int l = 0; l < len3; l++) {
          temp[k++] = str3[l];
        }
      } else {
        i = initial_i;
      }
    }
    temp[k++] = str1[i++];
  }

  temp[k] = '\0';
  strcpy(str1, temp);
}

int countOccurrences(char str[], char s[]) {
  int i, j, count;
  count = 0;
  i = 0;
  j = 0;
  while (str[i] != '\0') {
    if (str[i] == s[j]) {
      j++;
      if (s[j] == '\0') {
        count++;
        j = 0;
      }
    } else {
      j = 0;
    }
    i++;
  }
  return count;
}

void init_char_stack(s21_char_stack *st) { st->top = 0; }

void push_char(s21_char_stack *st, char x) {
  st->data[st->top] = x;
  st->top++;
}

char last_char(s21_char_stack st) { return st.data[st.top - 1]; }

void pop_char(s21_char_stack *st) {
  if (st->top != 0) {
    st->top--;
  }
}

void init_double_stack(s21_double_stack *st) { st->top = 0; }

void push_double(s21_double_stack *st, double x) {
  st->data[st->top] = x;
  st->top++;
}

double last_double(s21_double_stack st) { return st.data[st.top - 1]; }

void pop_double(s21_double_stack *st) {
  if (st->top != 0) {
    st->top--;
  }
}

s21_bool isOperator(char c) {
  const char operators[] = {'(', '+', '-', '*', '/', '^', '%', '~', '`'};
  for (int i = 0; i < 9; ++i)
    if (c == operators[i]) return s21_true;
  return s21_false;
}

s21_bool isFunction(char c) {
  const char funcs[] = {'$', '@', '#', '|', 'S', 'C', 'T', 'L', '&'};
  for (int i = 0; i < 9; ++i)
    if (c == funcs[i]) return s21_true;
  return s21_false;
}

int getPriority(char c) {
  if (c == '(') return 0;
  if (c == '+' || c == '-') return 1;
  if (c == '*' || c == '/' || c == '%') return 2;
  if (c == '^') return 3;
  if (c == '~' || c == '`') return 4;
  if (isFunction(c)) return 5;
  return -1;
}

void convert_string_to_number(char str[], int *pos, char ans[]) {
  s21_bool was_point = s21_false;
  for (; (*pos) < (int)strlen(str); (*pos)++) {
    if ((str[(*pos)] >= '0' && str[(*pos)] <= '9') ||
        (str[(*pos)] == '.' && !was_point)) {
      if (str[(*pos)] == '.') was_point = s21_true;
      strncat(ans, str + (*pos), 1);
    } else {
      (*pos)--;
      break;
    }
  }
}

void make_postfix(char str[], char postfix[], s21_bool *error, double x) {
  int postfix_sz = 0, balance = 0;

  s21_bool positive_x = (x >= 0);

  s21_char_stack st;
  init_char_stack(&st);

  for (int i = 0; i < (int)strlen(str); ++i) {
    char c = str[i];
    s21_bool extra_if = (c == 'x' && x < 0);
    // printf("i = %d extra_if = %d\n", i, extra_if);
    if (c == 'x' && x >= 0) {
      // printf("hello\n");
      char db[MAXN] = {0};
      sprintf(db, "%.10lf", x);
      strcat(postfix, db);
      strcat(postfix, " ");
      postfix_sz = (int)strlen(postfix);
      if (!positive_x) x *= -1;
    } else if (c >= '0' && c <= '9') {
      char res[MAXN] = {0};
      convert_string_to_number(str, &i, res);
      strcat(postfix, res);
      strcat(postfix, " ");
      postfix_sz += (int)strlen(res) + 1;
    } else if (c == '(') {
      balance++;
      push_char(&st, c);
    } else if (c == ')') {
      balance--;
      if ((i > 0 && str[i - 1] == '(') || balance < 0) {
        (*error) = s21_true;
        break;
      }
      while (st.top > 0 && last_char(st) != '(') {
        postfix[postfix_sz++] = last_char(st);
        pop_char(&st);
      }
      pop_char(&st);
    } else if (isOperator(c) || isFunction(c) || extra_if) {
      // printf("OK\n");
      if (((c == '-') && (i == 0 || (i >= 1 && isOperator(str[i - 1])))) ||
          extra_if)
        c = '~';
      if (c == '+' && (i == 0 || (i >= 1 && isOperator(str[i - 1])))) c = '`';
      if (c != '^' && c != '~' && c != '`') {
        while (st.top > 0 && getPriority(last_char(st)) >= getPriority(c)) {
          postfix[postfix_sz++] = last_char(st);
          pop_char(&st);
        }
      } else {
        while (st.top > 0 && getPriority(last_char(st)) > getPriority(c)) {
          postfix[postfix_sz++] = last_char(st);
          pop_char(&st);
        }
      }
      push_char(&st, c);
      if (extra_if) {
        i--;
        x *= -1;
        continue;
      }
    } else {
      *error = s21_true;
      break;
    }
  }
  // printf("%d\n", (*error));
  if (balance != 0) {
    (*error) = s21_true;
    return;
  }
  if (!(*error)) {
    while (st.top > 0) {
      postfix[postfix_sz++] = last_char(st);
      pop_char(&st);
    }
  }
}

double calc_term(char sign, double x, double y, s21_bool *error) {
  double ans = 0;
  if (sign == '+') {
    ans = x + y;
  } else if (sign == '-') {
    ans = x - y;
  } else if (sign == '*') {
    ans = x * y;
  } else if (sign == '/' && y != 0) {
    ans = x / y;
  } else if (sign == '^') {
    ans = pow(x, y);
  } else if (sign == '%' && y != 0) {
    ans = fmod(x, y);
  } else {
    (*error) = s21_true;
  }
  return ans;
}

double calc_func(char sign, double x, s21_bool *error) {
  double ans = 0;
  // double rad = M_PI / 180.0;
  // double rad1 = 180.0 / M_PI;
  if (sign == '$' && x >= 0.0) {
    ans = sqrt(x);
  } else if (sign == '&' && x > 0.0) {
    ans = log10(x);
  } else if (sign == 'L' && x > 0.0) {
    ans = log(x);
  } else if (sign == 'S') {
    ans = sin(x);  // * rad);
  } else if (sign == 'C') {
    ans = cos(x);  // * rad);
  } else if (sign == 'T') {
    ans = tan(x);  // * rad);
  } else if (sign == '@' && x >= -1.0 && x <= 1.0) {
    ans = asin(x);  // * rad1;
  } else if (sign == '#' && x >= -1.0 && x <= 1.0) {
    ans = acos(x);  // * rad1;
  } else if (sign == '|') {
    ans = atan(x);  // * rad1;
  } else {
    (*error) = s21_true;
  }
  return ans;
}

double calc_from_postfix(char postfix[], s21_bool *error) {
  s21_double_stack locals;
  init_double_stack(&locals);
  for (int i = 0; i < (int)strlen(postfix); ++i) {
    char c = postfix[i];
    if (c >= '0' && c <= '9') {
      char res[MAXN] = {0};
      convert_string_to_number(postfix, &i, res);
      double cur = atof(res);
      push_double(&locals, cur);
    } else if (isOperator(c)) {
      if (c == '~' || c == '`') {
        double last = 0;
        if (locals.top > 0) {
          last = last_double(locals);
          pop_double(&locals);
        } else {
          (*error) = s21_true;
          return 0;
        }
        char unar = ((c == '~') ? '-' : '+');
        double unar_result = calc_term(unar, 0, last, error);
        push_double(&locals, unar_result);
        continue;
      }
      double num1 = 0;
      if (locals.top > 0) {
        num1 = last_double(locals);
        pop_double(&locals);
      } else {
        (*error) = s21_true;
        return 0;
      }
      double num2 = 0;
      if (locals.top > 0) {
        num2 = last_double(locals);
        pop_double(&locals);
      } else {
        (*error) = s21_true;
        return 0;
      }
      double res = calc_term(c, num2, num1, error);
      push_double(&locals, res);
    } else if (isFunction(c)) {
      double last = 0;
      if (locals.top > 0) {
        last = last_double(locals);
        pop_double(&locals);
      } else {
        (*error) = s21_true;
        return 0;
      }
      double func_result = calc_func(c, last, error);
      push_double(&locals, func_result);
    }
  }
  double answer = last_double(locals);
  pop_double(&locals);
  if (locals.top != 0) {
    (*error) = s21_true;
  }
  return answer;
}

void convert_1_char(char str[], s21_bool *error) {
  char *from[] = {"mod", "sqrt", "asin", "acos", "atan",
                  "sin", "cos",  "tan",  "ln",   "log"};
  char *to[] = {"%", "$", "@", "#", "|", "S", "C", "T", "L", "&"};
  *error = s21_false;
  for (int i = 0; i < 10; ++i) {
    if (strstr(str, to[i]) != NULL) {
      *error = s21_true;
      return;
    }
  }
  for (int i = 0; i < 10; ++i) {
    int cur_cnt = countOccurrences(str, from[i]);
    if (cur_cnt != 0) {
      for (int j = 0; j < cur_cnt; ++j) s21_substr(str, from[i], to[i]);
    }
  }
}

void calc(char str[], double *answer, s21_bool *error, double x) {
  char postfix[MAXN] = {0};
  (*answer) = 0;
  (*error) = s21_false;
  convert_1_char(str, error);
  // printf("tmp str = %s\n", str);
  if ((int)strlen(str) > 255) {
    (*error) = s21_true;
    return;
  }
  if (!(*error)) {
    make_postfix(str, postfix, error, x);
    if (!(*error)) {
      // printf("%s\n", postfix);
      (*answer) = calc_from_postfix(postfix, error);
    }
  }
}

// int main() {
//     char str[MAXN];
//     scanf("%s", str);

//     double answer = 0;
//     s21_bool error = s21_false;

//     calc(str, &answer, &error, -1);

//     if (!error)
//         printf("%lf\n", answer);
//     else
//         printf("ERROR!");
//     return 0;
// }