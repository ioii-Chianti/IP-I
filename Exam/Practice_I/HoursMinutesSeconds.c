#include <stdio.h>

int main() {   /* 全換秒相減後再處理進位 */
    unsigned long long monA, dayA, hA, mA, sA, secA;
    unsigned long long monB, dayB, hB, mB, sB, secB;
    scanf("%llu/%llu %llu:%llu:%llu", &monA, &dayA, &hA, &mA, &sA);
    scanf("%llu/%llu %llu:%llu:%llu", &monB, &dayB, &hB, &mB, &sB);

    secA = sA + mA * 60 + hA * 3600 + dayA * 86400 + monA * 2592000;
    secB = sB + mB * 60 + hB * 3600 + dayB * 86400 + monB * 2592000;

    unsigned long long second, minute, hour, day, month;
    if (secA >= secB)
        second = secA - secB;
    else
        second = secB - secA;

    minute = second / 60;
    second %= 60;

    hour = minute / 60;
    minute %= 60;

    day = hour / 24;
    hour %= 24;

    month = day / 30;
    day %= 30;

    printf("%llu %llu\n", month, day);   // 共兩個位數，未滿補零
    printf("%02llu:%02llu:%02llu\n", hour, minute, second);

    return 0;
}