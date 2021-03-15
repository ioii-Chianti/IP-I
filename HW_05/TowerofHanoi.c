#include <stdio.h>

void hanoi(int disk, char A, char B, char C) {
    if (disk == 1)
        printf("move disk %d from rod %c to rod %c\n", disk, A, C);
    else {
        hanoi(disk - 1, A, C, B);
        printf("move disk %d from rod %c to rod %c\n", disk, A, C);
        hanoi(disk - 1, B, A, C);
    }
}

int main(){
    int disk;
    scanf("%d", &disk);
    hanoi(disk, 'A', 'B', 'C');

    return 0;
}