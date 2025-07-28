#include "s21_SmartCredit.h"

void calcAnnuity(ld sum, int credit_time, ld rate) {
    rate /= 1200.0;
    ld res = pow((1.0 + rate), 1.0 * credit_time);
    ld month_payment = sum * rate * res;
    month_payment /= (res - 1.0);
    printf("month_payment = %Lf\n", month_payment);
    ld all_payout = roundl(month_payment * 1.0 * credit_time);
    printf("calced_percents = %Lf\n", all_payout - 1.0 * sum);
    printf("all_payout = %Lf\n", all_payout);   
}

void calcDifferentiated(ld sum, int credit_time, ld rate) {
    rate /= 1200.0;
    ld sd = sum / credit_time;
    for (int i = 1; i <= credit_time; i++) {
        ld sp = sum * rate;
        ld month_pay = sd + sp;
        printf("Месяц %d: Основной долг: %.2Lf, Проценты: %.2Lf, Ежемесячный платеж: %.2Lf\n",
               i, sd, sp, month_pay);
        sum -= sd;
    }
}

int main() {

    setlocale(LC_ALL, "Russian");

    calcDifferentiated(2000000, 120, 13);

    return 0;
}