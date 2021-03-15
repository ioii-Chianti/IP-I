#include <stdio.h>
#include <math.h>

int main(){
    double a, n, r, an, sum;
    scanf("%lf %lf %lf", &a, &n, &r);
    an = a * pow(r, n - 1);
    sum = a * (1 - pow(r, n)) / (1 - r);
    printf("%lf %lf\n", an, sum);
}
