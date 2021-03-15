#include <stdio.h>
#include <string.h>
#define max_target 500005
#define max_type 1000005

/* NOTE :
    1. strlen會算進\n為一個字元，\0不會
    2. 如果curType[3]，輸入\b\n時換行會自動變成\0 */

char target[max_target], monkey[max_type], curType[5];
int prefix[max_type];

int main() { 
    fgets(target, max_target, stdin);    // input target str 
    target[strlen(target) - 1] = '\0';  // set \0 to fgets' \n

    int index = 0;    // cur checking
    prefix[0] = 1;      // no enter

    while (fgets(curType, 5, stdin) != NULL) {   // monkey stops typing -> NULL
        curType[strlen(curType) - 1] = '\0';  // set \0 to fgets' \n
        if (!strcmp(curType, "\\b")) {
            if (index > 0)
                monkey[--index] = '\0';
        } else {
            monkey[index++] = curType[0];
            prefix[index] = (monkey[index - 1] == target[index - 1] && (index == 0 || prefix[index - 1])) ? 1 : 0;
        }
        printf("%d\n", prefix[index]);
    }
    printf("%s\n", strcmp(target, monkey) == 0 ? "Correct" : "Incorrect");
    
    return 0;