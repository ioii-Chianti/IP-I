#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXUSER 100001
#define MAXCHAR 101
#define MAXPROB 10

typedef struct {
    int subTimes[MAXPROB];   // 拿到AC前的上傳次數
    int acTime[MAXPROB];   // 拿到AC的時間
} Info;   // 每次的上傳資料

typedef struct {
    int id;       // user id
    int numofAC;   // 總AC次數
    int penalty;  // WA懲罰分數
} Score;

int attend[MAXUSER];
Info submit[MAXUSER];
Score scoreboard[MAXUSER];
char input[MAXCHAR];

void initialize() {
    for (int i = 0; i < MAXUSER; i++)
        for (int j = 0; j < MAXPROB; j++)
            submit[i].acTime[j] = -1;
    return;
}

int getTime (char *ch) {   // ch[0], *c is ':'
    int min = (ch[-2] - '0') * 60 * 10 \
            + (ch[-1] - '0') * 60 \
            + (ch[1] - '0') * 10 \
            + (ch[2] - '0');
    return min;
}

int getID (char *ch) {
    int pos = 0, id = 0;
    while ('0' <= ch[pos] && ch[pos] <= '9') {
        id = id * 10 + (ch[pos] - '0');
        pos++;   // *10後會多一個位數，再加上新的數字
    }
    return id;
}

int cmp(const void* a, const void* b) {
    Score sa = *(Score *)a, sb = *(Score *)b;
    if(sa.numofAC < sb.numofAC)
        return 1;
    else if (sa.numofAC > sb.numofAC)
        return -1;
    else {
        if (sa.penalty > sb.penalty)
            return 1;
        else if(sa.penalty < sb.penalty)
            return -1;
        else {
            if(sa.id > sb.id)
                return 1;
            else if(sa.id < sb.id)
                return -1;
            else
                return 0;
        }
    }
}

int main() {
    initialize();   // each user's each probs = -1
    int ignore = 10;
    while (ignore--)    // first 10 lines
        fgets(input, MAXCHAR, stdin);

    /* tr > time > ID > problem > result > /tr */
    while (fgets(input, MAXCHAR, stdin) != NULL) {   // <tr> or </tbody>
        int len = strlen(input), finish = 0;
        for (int i = 0; i < len; i++)
            if (input[i] == '/')
                finish = 1;
        if (finish) break;   // get </tbody>

        int user_id, prob_id, isAC, subTime;    // 4 items in each submission

        fgets(input, MAXCHAR, stdin);   // time in this line
        len = strlen(input);
        for (int i = 0; i < len; i++) {
            if (input[i] == ':') {
                subTime = getTime(input + i);
                break;
            }
        }
        fgets(input, MAXCHAR, stdin);   // user id in this line
        len = strlen(input);
        for (int i = 0; i < len; i++) {
            if ('0' <= input[i] && input[i] <= '9') {
                user_id = getID(input + i);   // id's start pos 
                attend[user_id] = 1;   // this id attends
                break;
            }
        }
        fgets(input, MAXCHAR, stdin); // problem id in this line
        len = strlen(input);
        for (int i = 0; i < len; i++) {
            if ('A' <= input[i] && input[i] <= 'J') {
                prob_id = input[i] - 'A';
                break;
            }
        }
        fgets(input, MAXCHAR, stdin); // result
        len = strlen(input);
        for (int i = 0; i < len; i++) {
            if (input[i] == 'A') {
                isAC = 1;
                break;
            } else if (input[i] == 'W') {
                isAC = 0;
                break;
            }
        }
        fgets(input, MAXCHAR, stdin);   // </tr>

        if (submit[user_id].acTime[prob_id] == -1) {    // this user doesn'y pass this prob
            submit[user_id].subTimes[prob_id]++;        // times of submit +1
            if (isAC)
                submit[user_id].acTime[prob_id] = subTime;   // 送出時間即為AC時間
        }
    } fgets(input, MAXCHAR, stdin); // </table>

    // scoreboard setting
    int num = 0;   // num of data in scoreboard
    for (int i = 0; i < MAXUSER; i++) {
        if (attend[i]) {   // check user attend or not
            scoreboard[num].id = i;   // insert id
            for (int j = 0; j < MAXPROB; j++)   // submit裡找此人的每題作答狀況
                if (submit[i].acTime[j] != -1) {    // Accepted
                    scoreboard[num].numofAC += 1;  // num of times of AC +1
                    scoreboard[num].penalty += submit[i].acTime[j] + 20 * submit[i].subTimes[j] - 20; // calculate penalty
                }
            num++;
        }
    }
    qsort(scoreboard, num, sizeof(Score), cmp);   // sort by: more acTimes > less penalty > less id
    for (int rank = 0; rank < num; rank++) {
        int user = scoreboard[rank].id;
        printf("%d", user);

        for (int prob = 0; prob < MAXPROB; prob++) {   // 印出作答狀況
            if (submit[user].subTimes[prob] > 0) {   // 有送出過
                if (submit[user].acTime[prob] != -1)   // 有過
                    printf(" %d/%d", submit[user].subTimes[prob], \
                                     submit[user].subTimes[prob] * 20 + submit[user].acTime[prob] - 20);
                else   // 有送出過但沒過
                    printf(" %d/-", submit[user].subTimes[prob]);
            } else   // 沒送出過
                printf(" -/-");
        }

        printf(" %d %d\n", scoreboard[rank].numofAC, scoreboard[rank].penalty);   // AC次數和懲罰分數
    }
    return 0;
}