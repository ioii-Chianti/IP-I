#include <stdio.h>
#include <stdlib.h>
// #include "function.h"

unsigned random_seed = 7122;

unsigned Random() {
	return random_seed = random_seed * 0xdefaced + 1;
}

unsigned ***new_3d_array(unsigned n, unsigned m, unsigned k) {
	unsigned ***arr_head = NULL;
	unsigned **row_head = NULL;
	unsigned *col_head = NULL;

	arr_head = (unsigned ***)malloc(n * sizeof(unsigned **));
	row_head = (unsigned **)malloc(n * m * sizeof(unsigned *));
	col_head = (unsigned *)malloc(n * m * k * sizeof(unsigned));

	for (int i = 0; i < n; i++)
		arr_head[i] = &(row_head[i * m]);
	for (int i = 0; i < n * m; i++)
		row_head[i] = &(col_head[i * k]);
	for (int i = 0; i < n * m * k; i++)
		col_head[i] = 0;

	return arr_head;
}

void delete_3d_array(unsigned ***arr) {
	free(arr[0][0]);
	free(arr[0]);
	free(arr);
	arr = 0;
}

int main() {
	int n, m, k, _;
	scanf("%d %d %d %d %u", &_, &n, &m, &k, &random_seed);
	while(_--) {
		unsigned ***arr = new_3d_array(n, m, k);
		int i, j, l;
		for(i = 0; i < n; ++i)
			for(j = 0; j < m; ++j)
				for(l = 0; l < k; ++l)
					arr[i][j][l] = Random();
		for(i = 0; i < 5; ++i) {
			unsigned a, b, c;
			a = Random() % n;
			b = Random() % m;
			c = Random() % k;
			if(i)
				putchar(' ');
			printf("%u", arr[a][b][c]);
		}
		puts("");
		delete_3d_array(arr);
	}
	return 0;
}