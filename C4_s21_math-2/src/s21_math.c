#include "s21_math.h"

#include <float.h>
#include <stdio.h>

int s21_isNan(double x) { return (x != x); }

int s21_abs(int x) {
  if (x < 0) x *= -1;
  return x;
}

long double s21_fabs(double x) { return x < 0.0 ? -x : x; }

long double s21_floor(double x) {
  long double result = (long long int)x;
  if (s21_fabs(x) == s21_POSITIVE_INFINITY || s21_isNan(x))
    result = x;
  else if (s21_fabs(result - x) > 0.0 && s21_fabs(x) > 0.0 && x < 0.0)
    result--;
  return result;
}

long double s21_ceil(double x) {
  long double answer = 0;
  if (s21_isNan(x)) {
    answer = x;
  } else if (s21_fabs(x) != s21_POSITIVE_INFINITY) {
    answer = (long long int)x;
    if (s21_fabs(x - answer) > 0.0 && s21_fabs(x) > 0.0 && x >= 0.0) answer++;
  } else {
    answer = x;
  }
  return answer;
}

long double s21_factorial(int x) {
  long double res = 1;
  if (x == 0) res = 1;
  for (int i = x; i > 1; i--) {
    res *= i;
  }
  return res;
}

long double s21_exp(double x) {
  long double series_member = 1;
  long double prev_appr = 0;
  long double series = 1.0;
  double sign = (x > 0 ? 1.0 : -1.0);
  x = s21_fabs(x);
  unsigned long long int i = 1;
  while (s21_fabs(series - prev_appr) > 1e-16 && i < __UINT64_MAX__ &&
         series < DBL_MAX) {
    series_member *= (x / (long double)i);
    prev_appr = series;
    series += series_member;
    if (series > DBL_MAX) series = s21_POSITIVE_INFINITY;

    i++;
  }
  if (sign < 0) series = 1 / series;
  return series;
}

// Using Newton's method, the iteration simplifies to (implementation)
// which has cubic convergence to ln(x).
long double s21_log(double x) {
  long double yn =
      x - 1.0;  // using the first term of the taylor series as initial-value
  long double yn1 = yn;
  if (x == s21_POSITIVE_INFINITY || s21_isNan(x)) {
    yn1 = x;
  } else if (x == s21_NEGATIVE_INFINITY) {
    yn1 = s21_NAN;
  } else if (x > s21_EPS) {
    do {
      yn = yn1;
      if (yn > 10.) {
        long double temp = yn, tmp = 0.;
        while (temp > 10.) {
          tmp += s21_log10;
          temp /= 10.;
        }
        yn1 = tmp + 2 * (x - s21_exp(temp)) / (x + s21_exp(temp));
      } else
        yn1 = yn + 2 * (x - s21_exp(yn)) / (x + s21_exp(yn));
    } while (s21_fabs(yn - yn1) > s21_EPS);
  } else if (s21_fabs(x) < s21_EPS) {
    yn1 = s21_NEGATIVE_INFINITY;
  } else if (x < 0.0) {
    yn1 = s21_NAN;
  }
  return yn1;
}

long double s21_fmod(double x, double y) {
  long long int mod = 0;
  long double result = 0;
  if (s21_fabs(y) == s21_POSITIVE_INFINITY) {
    result = x;
  } else if (s21_fabs(x) == s21_POSITIVE_INFINITY) {
    result = s21_NAN;
  } else if (s21_fabs(y) != 0.0) {
    mod = x / y;
    result = (long double)x - mod * (long double)y;
  } else {
    result = s21_NAN;
  }
  return result;
}

long double s21_pow(double base, double exp) {
  long double result = 0.0, lbase = base;
  if (s21_isNan(base) || s21_isNan(exp)) {
    result = s21_NAN;
  } else if (base == 1.0 || s21_fabs(exp) < s21_EPS) {
    result = 1.0;
  } else if (s21_fabs(base) < s21_EPS || exp == s21_NEGATIVE_INFINITY) {
    result = 0.0;
  } else if (lbase > 0.0) {
    result = s21_exp(exp * s21_log(lbase));
  } else if (base == s21_NEGATIVE_INFINITY) {
    if (exp > 0.0) {
      result = s21_POSITIVE_INFINITY;
    } else {
      result = 0.0;
    }
  } else if (exp - (long long)exp != 0) {
    result = s21_NAN;
  } else {
    lbase *= -1;
    result = s21_exp(exp * s21_log(lbase));
    if (s21_fmod(exp, 2) != 0.0) result *= -1;
  }
  return result;
}

long double s21_sin(double x) {
  long double result = 0, sign = 1.0, ex;
  if ((s21_fabs(x) == s21_POSITIVE_INFINITY) || s21_isNan(x)) {
    result = s21_NAN;
  } else {
    while (x < 0 || x > 2 * M_PI) {
      if (x < 0)
        x += 2 * M_PI;
      else
        x -= 2 * M_PI;
    }
    ex = x;
    for (int i = 0; i < 16; i++) {
      result += sign * ex / s21_factorial(2 * i + 1);
      ex *= x * x;
      sign = -sign;
    }
  }
  if (x == 0.0) result = 0.0;
  return result;
}

long double s21_cos(double x) {
  long double result = 0, sign = 1.0, ex = 1.0;
  if ((s21_fabs(x) == s21_POSITIVE_INFINITY) || s21_isNan(x)) {
    result = s21_NAN;
  } else {
    while (x < 0 || x > 2 * M_PI) {
      if (x < 0)
        x += 2 * M_PI;
      else
        x -= 2 * M_PI;
    }
    for (int i = 0; i < 16; i++) {
      result += sign * ex / s21_factorial(2 * i);
      ex *= x * x;
      sign = -sign;
    }
  }
  return result;
}

long double s21_tan(double x) { return (s21_sin(x) / s21_cos(x)); }

long double s21_asin(double x) {
  long double result = 0;
  if (x > 1 || x < -1) {
    result = s21_NAN;
  } else {
    result = s21_atan(x / s21_sqrt(1 - x * x));
  }
  return result;
}

long double s21_acos(double x) {
  long double result = 0.0;
  if (x == 1 || x == -1) {
    result = M_PI * (1.0 - x) / 2.0;
  } else if (x > 1.0 || x < -1.0) {
    result = s21_NAN;
  } else {
    result = (M_PI / 2.0) - s21_asin(x);
  }
  return result;
}

long double s21_atan(double x) {
  long double result = 0, sign = 1.0, ex;
  if (s21_isNan(x)) {
    result = x;
  } else if (x < 0) {
    result = -s21_atan(-x);
  } else if (x == 1.0) {
    result = 0.7853981633974483;
  } else if (x == -1.0) {
    result = -0.7853981633974483;
  } else if (x > -1. && x < 1.) {
    ex = x;
    for (int i = 0; i < 5000; i++) {
      result += (sign * ex) / (1. + 2. * i);
      ex *= x * x;
      sign = -sign;
    }
  } else {
    ex = 1. / x;
    for (int i = 0; i < 7000; i++) {
      result += sign * ex / (1. + 2. * i);
      ex /= (x * x);
      sign = -sign;
    }
    if (x >= 0)
      result = M_PI / 2. - result;
    else
      result = -(M_PI / 2. + result);
  }
  return result;
}

long double s21_sqrt(double x) {
  long double mid = 0.0;
  if (x >= 0) {
    long double left = 0, right = (x > 1.0 ? x : 1.0);
    mid = (left + right) / 2.0;
    while ((mid - left) > s21_EPS) {
      if (mid * mid > x) {
        right = mid;
      } else {
        left = mid;
      }
      mid = (left + right) / 2.0;
    }
  } else {
    mid = s21_NAN;
  }
  return mid;
}
