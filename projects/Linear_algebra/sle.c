/*
***== Получен Quest 4. Изменить программу src/sle.c так, чтобы она производила решение СЛАУ либо методом Крамера, 
либо методом Гаусса по твоему выбору. Реализации одного метода достаточно. Коэффициенты уравнения вводятся в виде матрицы через stdin. 
Необходимо также оформить вывод ответа в stdout. Не забывать про декомпозицию: функции не должны получаться громоздкими и должны хорошо 
читаться. В случае ошибки выводить «n/a». Числа выводить через пробел с точностью 6 знаков после запятой. В конце вывода не должно 
присутствовать пробела. ==***
*/

#include <stdio.h>
#include <stdlib.h>

void sle(double **matrix, int n, int m, double *roots, double det_);
double det(double **matrix, int n, int m);
double **init_matrix(int *M, int *N);
void input(double ***matrix, int *n, int *m);
void output(double **matrix, int n, int m);
void output_roots(double *roots, int n);

int main() {
    double **matrix;
    int n, m;
    input(&matrix, &n, &m);
    if (n != -1 && n > 0 && m > 0 && n == m - 1) {
        int n_new = n;
        int m_new = m - 1;
        double **additional_matrix = init_matrix(&n_new, &m_new);
        for (int i = 0; i < n_new; i++) {
            for (int j = 0; j < m_new; j++) {
                additional_matrix[i][j] = matrix[i][j];
            }
        }
        double determinant = det(additional_matrix, n_new, m_new);
        double *roots;
        if (determinant != 0) {
            roots = malloc(n * sizeof(double));
            sle(matrix, n, m, roots, determinant);
            output_roots(roots, n);
            free(roots);
        } else {
            printf("n/a");
        }
        free(matrix);
        free(additional_matrix);
    } else {
        printf("n/a");
    }
    return 0;
}

double **init_matrix(int *M, int *N) {
    double **single_array_matrix = malloc((*M) * sizeof(double *) + (*M) * (*N) * sizeof(double));
    double *ptr = (double *)(single_array_matrix + *M);
    for (int i = 0; i < *M; i++) {
        single_array_matrix[i] = ptr + (*N) * i;
    }
    return single_array_matrix;
}

void input(double ***matrix, int *n, int *m) {
    if (scanf("%d", n) == 1 && *n > 0 && scanf("%d", m) == 1 && *m > 0 && (*n) == ((*m) - 1)) {
        int error = 0;
        *matrix = init_matrix(n, m);
        for (int i = 0; i < *n; i++) {
            if (!error) {
                for (int j = 0; j < *m; j++) {
                    if (scanf("%lf", &(*matrix)[i][j]) == 0) {
                        error = 1;
                        break;
                    }
                }
            }
        }
        if (error == 1) {
            free(*matrix);
            *n = -1;
        }
    } else {
        *n = -1;
    }
}

double det(double **matrix, int n, int m) {
    double ans = 0.0;
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double **submatrix = (double **)malloc((n - 1) * sizeof(double *));
    for (int i = 0; i < n - 1; i++) {
        submatrix[i] = (double *)malloc((n - 1) * sizeof(double));
    }

    for (int x = 0; x < n; x++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x) {
                    continue;
                }
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        ans += (x % 2 == 0 ? 1 : -1) * matrix[0][x] * det(submatrix, n - 1, m - 1);
    }
    for (int i = 0; i < n - 1; i++) {
        free(submatrix[i]);
    }
    free(submatrix);

    return ans;
}

void sle(double **matrix, int n, int m, double *roots, double det_) {
    int cnt = 0;
    for (int x = 0; x < n; x++) {
        int m_ = m - 1;
        double **dop_matrix = init_matrix(&n, &m_);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m_; j++) {
                if (j == x) {
                    dop_matrix[i][j] = matrix[i][m - 1];
                } else {
                    dop_matrix[i][j] = matrix[i][j];
                }
            }
        }
        roots[cnt++] = det(dop_matrix, n, m_) / det_;
        free(dop_matrix);
    }
}

void output_roots(double *roots, int n) {
    for (int i = 0; i < n; i++) {
        if (i + 1 < n) {
            printf("%.6lf ", roots[i]);
        } else {
            printf("%.6lf", roots[i]);
        }
    }
}

void output(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j + 1 < m) {
                printf("%lf ", matrix[i][j]);
            } else {
                printf("%lf", matrix[i][j]);
            }
        }
        if (i + 1 < n) {
            printf("\n");
        }
    }
}