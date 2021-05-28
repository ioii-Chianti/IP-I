#include <stdio.h>
#include <stdlib.h>
// #include "function.h"
#pragma warning( disable : 4996 )

int **malloc_ptr(int array_size) {
    int **ptr_head = (int **)malloc(array_size * sizeof(int *));
    return ptr_head;
}

void malloc_array(int **array, int array_size) {
    *array = (int *)malloc(array_size * sizeof(int));
}
  // int **array = &array'
  // *array = *&array' = array' = head of original arr (int *)

void pointer_ptr_to_array(int *array, int **ptr, int N) {
    for (int i = 0; i < N; i++)
        *(ptr + i) = array + ((i + 1) * i / 2);   // int *
     /* ptr[i] = &(array[(i + 1) * i / 2]); */    // int *
}

int main() {
    int *array;
    int **ptr;
	int N;
	int offset;
    scanf("%d %d", &N, &offset);

    // array' (int *), &array' (int **)
    malloc_array(&array, (1 + N) * N / 2);
    ptr = malloc_ptr(N);

    for (int i = 0; i < (1 + N) * N / 2; i++)
        array[i] = i;
    pointer_ptr_to_array(array, ptr, N);
    for(int i = 0; i < N; i++)
        printf("%d\n", *(ptr[i]) + offset);
    
    free(ptr);
	free(array);
	return 0;
}