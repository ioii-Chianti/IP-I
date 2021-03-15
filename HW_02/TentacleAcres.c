#include<stdio.h>

int main() {
	int n, m;
    int a[100][100];
    scanf("%d %d", &n, &m);     // Matrix

    for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			scanf("%d", &a[i][j]);      // fill in the matrix

	int q;
	scanf("%d", &q);      // helping times
	for(int t = 1; t <= q; t++) {
		int u, d, l, r;
		scanf("%d %d %d %d", &u, &d, &l, &r);
		int ans = 0;

        for (int i = u - 1; i < d; i++)
            for (int j = l - 1; j < r; j++)
                if (a[i][j] > ans)
                    ans = a[i][j];

        printf("%d\n", ans);    // output the answer immedialety
	}
	return 0;
}