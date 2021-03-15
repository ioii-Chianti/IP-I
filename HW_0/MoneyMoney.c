#include<stdio.h>

int main(){
    int Jay, Jolin, JJ, x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    Jolin = (x - z + y) / 2;
    Jay = x - Jolin;
    JJ = y - Jolin;
    printf("%d %d %d\n", Jay, Jolin, JJ);

    return 0;
}