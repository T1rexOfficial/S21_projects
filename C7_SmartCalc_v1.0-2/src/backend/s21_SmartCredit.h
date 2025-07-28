#ifndef SRC_BACKEND_SMARTCREDIT_H_
#define SRC_BACKEND_SMARTCREDIT_H_

#include <locale.h>
#include <math.h>
#include <stdio.h>

typedef long long ll;
typedef long double ld;

void calcAnnuity(ld sum, int credit_time, ld rate);
void calcDifferentiated(ld sum, int credit_time, ld rate);

#endif // SRC_BACKEND_SMARTCREDIT_H_