/*
***== Получен Quest 2. Изменить программу src/det.c так, чтобы она подсчитывала и выводила определитель заданной квадратной матрицы с
 вещественными числами. Если определитель подсчитать невозможно, то выводить «n/a». Число вывести с точностью 6 знаков после запятой. ==***
*/

#include <stdio.h>
#include <stdlib.h>

double **matrix_init_second(int M, int N);
int matrix_input(double **arr, int M, int N);
void free_second(double **arr);
double det(double **matrix, int N);

int main() {
    int N, M;
    if (scanf("%d%d", &M, &N) == 2 && M > 0 && N > 0 && M == N) {
        double **seq = (double **)matrix_init_second(M, N);
        if (seq != NULL && matrix_input(seq, M, N)) {
            printf("%.6lf", det(seq, N));
        } else {
            printf("n/a");
        }
        free_second(seq);
    } else {
        printf("n/a");
    }
    return 0;
}

double **matrix_init_second(int M, int N) {
    double **seq = malloc(M * N * sizeof(double) + M * sizeof(double *));
    double *ptr = (double *)(seq + M);
    for (int i = 0; i < M; i++) {
        seq[i] = ptr + N * i;
    }
    return seq;
}

int matrix_input(double **arr, int M, int N) {
    int input = 1;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (scanf("%lf", &arr[i][j]) != 1) {
                input = 0;
                break;
            }
        }
    }
    return input;
}

void free_second(double **arr) { free(arr); }

double det(double **matrix, int N) {
    double ans = 0.0;
    if (N == 1) {
        ans = matrix[0][0];
    } else if (N == 2) {
        ans = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    } else {
        double **submatrix = (double **)matrix_init_second(N - 1, N - 1);
        for (int x = 0; x < N; x++) {
            int i_sub = 0;
            for (int i = 1; i < N; i++) {
                int j_sub = 0;
                for (int j = 0; j < N; j++) {
                    if (j == x) {
                        continue;
                    }
                    submatrix[i_sub][j_sub] = matrix[i][j];
                    j_sub++;
                }
                i_sub++;
            }
            ans += ((x % 2 == 0) ? 1 : -1) * matrix[0][x] * det(submatrix, N - 1);
        }
        free_second(submatrix);
    }
    return ans;
}