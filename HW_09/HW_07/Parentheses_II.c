#include <stdio.h>
#include <string.h>
#define MAX 100

int N;
char str[MAX];

unsigned long parentheses(int start) {
    for (int i = start; i < N; i++) {
        // Case 1 : ()
        if (str[i] == '(' && str[i + 1] == ')')
            return 1 + parentheses(i + 2);
        
        // Case 2: ((
        else if (str[i] == '(' && str[i + 1] == '(') {
            int breakpoint, leftCnt = 0, rightCnt = 0;
            for (int k = i; k < N; k++) {
                if (str[k] == '(')
                    ++leftCnt;
                else if (str[k] == ')')
                    ++rightCnt;
                if (leftCnt == rightCnt) {
                    breakpoint = k + 1;
                    break;
                }
            }
            unsigned long partA = 2 * parentheses(i + 1);   // 前段會停在*2的大括號
            unsigned long partB = parentheses(breakpoint);  // 從斷點開始遞迴
            return partA + partB;
        }
        
        // Case 3 : )
        else if (str[i] == ')')
            return 0;
    }
    return 0;   // 如果斷點超過範圍，也就是沒有partB，則回傳0
}

int main() {
    scanf("%d", &N);
    scanf("%s", str);
    printf("%lu\n", parentheses(0));

    return 0;
}