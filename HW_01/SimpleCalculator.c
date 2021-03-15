#include<stdio.h>

int main(){
    double x, y, answer;
    char operator;
    scanf("%lf%c%lf", &x, &operator, &y);
    
    if (operator == '/' && y == 0)
        printf("Error\n");
    else
    {
        switch (operator){
        case '+':
            answer = x + y;
            break;
        case '-':
            answer = x - y;
            break;
        case '*':
            answer = x * y;
            break;
        case '/':
            answer = x / y;
            break;
        }
        printf("%.3f\n", answer);
    }

    return 0;
}