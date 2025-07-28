#ifndef S21_MATH_H
#define S21_MATH_H

#define s21_NAN 0.0 / 0.0
#define s21_POSITIVE_INFINITY 1.0 / 0.0
#define s21_NEGATIVE_INFINITY -1.0 / 0.0
#define s21_EPS 1e-7
#define M_PI 3.14159265358979323846264338327950288
#define S21_E (2.71828182845904523536028747135266250)
#define s21_log10 (2.30258509299404590109)

typedef enum bool { false, true } bool;

int s21_isNan(double x);
int s21_abs(int x);
long double s21_fabs(double x);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_factorial(int n);
long double step(double x, int i);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_fmod(double x, double y);
long double s21_pow(double base, double exp);
long double s21_sin(double x);  // pow=376
long double s21_cos(double x);  // pow=462
long double s21_tan(double x);  // pow=736
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_atan(double x);  // pow=376
long double s21_sqrt(double x);

#endif  // S21_MATH_H