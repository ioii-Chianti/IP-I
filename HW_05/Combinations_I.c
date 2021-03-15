#include <stdio.h>

int N, M;
int seq[25], combined[25];

void combination(int choose_idx, int seq_idx) {
	if (choose_idx == M) {
		for (int i = 0; i < M; i++)
            printf("%d%c", combined[i], i == M - 1 ? '\n' : ' ');
        return;
    }
    if (seq_idx == N)
        return;

    combined[choose_idx] = seq[seq_idx];
    choose(choose_idx + 1, seq_idx + 1);
    choose(choose_idx, seq_idx + 1);
}

int main() {
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; i++)
        scanf("%d", seq + i);
    choose(0, 0);
    return 0;
}