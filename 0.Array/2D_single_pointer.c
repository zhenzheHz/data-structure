#include <stdio.h>
#include <stdlib.h>

void input_matrix(int **mat, int Row, int Col) {
    *mat = malloc(Row * Col * sizeof(int));
    for(int i = 0; i < Row; i++) {
        for(int j = 0; j < Col; j++) {
            scanf("%d", &(*mat)[i*Row+j]);
        }
    }
}

int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    int *arr = NULL;
    input_matrix(&arr, n, m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%d ", arr[i*n+j]);
        }
        printf("\n");
    }
    free(arr);
    return 0;
}