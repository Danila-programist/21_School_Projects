/*
***== Получен Quest 3. Изменить программу src/invert.c так, чтобы она подсчитывала и выводила обратную матрицу для данной 
квадратной матрицы с вещественными числами. В случае ошибки выводить «n/a». В конце каждой строки НЕ должны присутствовать пробелы. 
После вывода последней строки матрицы знак '\n' не требуется. Числа выводить через пробел с точностью 6 знаков после запятой. ==***
*/

#include <stdio.h>
#include <stdlib.h>

double **matrix_init_second(int M, int N);
int matrix_input(double **arr, int M, int N);
void free_second(double **arr);
double det(double **matrix, int N);
double **matrix_init_special(double **arr, int M, int N);
double minor(double **arr, int target_i, int target_j, int M, int N);
void matrix_output(double **arr, int M, int N);
void trans(double **arr, double **res, int M, int N);

int main() {
    int N, M;
    if (scanf("%d%d", &M, &N) == 2 && M > 0 && N > 0 && M == N) {
        double **seq = (double **)matrix_init_second(M, N);
        if (seq != NULL && matrix_input(seq, M, N)) {
            if (M == 1) {
                printf("%.6lf", seq[0][0]);
            } else if (det(seq, N) >= 1e-6 || det(seq, N) <= -1e-6) {
                double **seq_c = (double **)matrix_init_special(seq, M, N);
                double **seq_result = (double **)matrix_init_second(M, N);
                trans(seq_c, seq_result, M, N);
                matrix_output(seq_result, M, N);

                free(seq_result);
                free(seq_c);
            } else {
                printf("n/a");
            }
        } else {
            printf("n/a");
        }
        free(seq);
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

double **matrix_init_special(double **arr, int M, int N) {
    double **seq_c = (double **)matrix_init_second(M, N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            seq_c[i][j] = (((i + j) % 2 == 0) ? 1 : -1) * minor(arr, i, j, M, N) / det(arr, M);
        }
    }
    return seq_c;
}

double minor(double **arr, int target_i, int target_j, int M, int N) {
    double **MINOR = (double **)matrix_init_second(M - 1, N - 1);
    int i_sub = 0;
    for (int i = 0; i < M; i++) {
        if (target_i == i) {
            continue;
        }
        int j_sub = 0;
        for (int j = 0; j < N; j++) {
            if (target_j == j) {
                continue;
            } else {
                MINOR[i_sub][j_sub] = arr[i][j];
                j_sub++;
            }
        }
        i_sub++;
    }
    double value_minor = det(MINOR, N - 1);
    free(MINOR);
    return value_minor;
}

void matrix_output(double **arr, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N - 1; j++) {
            printf("%lf ", arr[i][j]);
        }
        if (i != M - 1) {
            printf("%lf\n", arr[i][N - 1]);
        } else {
            printf("%lf", arr[M - 1][N - 1]);
        }
    }
}

void trans(double **arr, double **res, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            res[j][i] = arr[i][j];
        }
    }
}