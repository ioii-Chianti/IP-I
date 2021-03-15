#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) (a > b ? a : b)

typedef struct {
	int num;
    char *name;
} Monkey;

Monkey *CreateMonkeyArray(int len) {
    return (Monkey *)malloc(len * sizeof(Monkey));
}

void FreeMonkeyArray(Monkey *arr, int len) {
    for (int i = 0; i < len; i++)
        free(arr[i].name);
    free(arr);
}

void SetVal(Monkey *arr, int index, int number, char Name[]) {
    arr[index].num = number;
    arr[index].name = (char *)malloc((strlen(Name) + 1) * sizeof(char));
    strcpy(arr[index].name, Name);
    // printf("%s\n", arr[index].name);
}

int Compare(Monkey *arr, int idx_x, int idx_y) {
    if (arr[idx_x].num == arr[idx_y].num)
        return strcmp(arr[idx_y].name, arr[idx_x].name);
    else
        return arr[idx_x].num < arr[idx_y].num;
}

void Swap(Monkey *arr, int x, int y) {
    Monkey temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
    // printf("%s, %s", arr[x].name, arr[y].name);
}

int main() {
	int n;
    scanf("%d\n", &n);
    Monkey *arr = CreateMonkeyArray(n);
    for (int i = 0; i < n; i++) {
        int num;
        char c[51];
        scanf("%d %s", &num, c);
		SetVal(arr, i, num, c);
    }

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (Compare(arr, i, j) > 0)
				Swap(arr, i, j);

    for(int i = 0; i < n; i++)
        printf("%d %s\n", arr[i].num, arr[i].name);

    FreeMonkeyArray(arr, n);
    return 0;
}
