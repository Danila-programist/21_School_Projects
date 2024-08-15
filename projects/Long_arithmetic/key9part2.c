/* ***== Получен Quest 5. Изменить программу src/key9part2.c так, чтобы она вернула результат сложения и разности двух очень больших чисел, 
переданных программе на вход в виде массивов. Максимальная длина числа - 100 элементов типа int. Вводимые целые числа представляют собой 
десятичные цифры. В случае если вычитаемое больше уменьшаемого, в разности выводится "n/a". Необходимо придерживаться декомпозиции, как и в 
прошлых квестах. Использовать stdlib.h нельзя. Передача массива в функцию только по указателю. В случае ошибки выводить «n/a». ==***
*/

#include <stdio.h>
#define LEN 100

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
int input(int *seq, int *len);
void output(int *seq, int n);
int max(int a, int b);
void swap(int *a, int *b);
void copy_seq(int *seq, int *copy_seq, int n);
void seq_convertion(int *seq, int *seq_copy, int n, int c);
void meaning_len(int *seq, int *length);

int main() {
    int buff1[LEN] = {0}, buff2[LEN] = {0}, len1 = 0, len2 = 0;
    if (input(buff1, &len1) && input(buff2, &len2)) {
        int result_length_sum = 0;
        int result_sum[LEN] = {0};
        int result_length_sub = 0;
        int result_sub[LEN] = {0};

        sum(buff1, len1, buff2, len2, result_sum, &result_length_sum);
        sub(buff1, len1, buff2, len2, result_sub, &result_length_sub);

        if (result_length_sum != -1 && result_length_sub != -1 && result_length_sub != -2) {
            output(result_sum, result_length_sum);
            printf("\n");
            output(result_sub, LEN);
        } else if (result_length_sum != -1 && result_length_sub == -2) {
            output(result_sum, result_length_sum);
            printf("\n");
            printf("0");
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *seq, int *len) {
    int input = 1;
    char ch;
    for (int i = 0; i < LEN; i++) {
        (*len)++;
        char check = scanf("%d%c", &seq[i], &ch);
        if (check == 2 && (ch == '\n' || ch == EOF) && seq[i] >= 0 && seq[i] < 10) {
            break;
        }
        if (check != 2 || seq[i] >= 10 || seq[i] < 0) {
            input = 0;
            break;
        }
    }
    if (ch != '\n') {
        input = 0;
    }
    return input;
}

void output(int *seq, int n) {
    int flag = 0;
    for (int i = 0; i < n - 1; i++) {
        if (seq[i]) {
            flag = 1;
        }
        if (flag) {
            printf("%d ", seq[i]);
        }
    }
    if (seq[n - 1]) {
        flag = 1;
    }
    if (flag) {
        printf("%d", seq[n - 1]);
    }
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int len = max(len1, len2);
    int counter = 0;
    int buff1_copy[LEN] = {0}, buff2_copy[LEN] = {0};
    if (len1 > len2) {
        copy_seq(buff2, buff2_copy, LEN);
        seq_convertion(buff2, buff2_copy, LEN, -len1 + len2);
    } else if (len1 < len2) {
        copy_seq(buff1, buff1_copy, LEN);
        seq_convertion(buff1, buff1_copy, LEN, -len2 + len1);
    }
    for (int i = len - 1; i >= 0; i--) {
        result[i] = buff1[i] + buff2[i] + counter;
        counter = 0;
        if (result[i] > 9 && i == 0 && len == LEN) {
            *result_length = -1;
            return;
        }
        if (result[i] > 9 && i == 0) {
            int result_copy[LEN] = {0};
            copy_seq(result, result_copy, LEN);
            seq_convertion(result, result_copy, LEN, -1);
            result[1] %= 10;
            result[0] = 1;
            *result_length = len + 1;
            return;
        }
        if (result[i] > 9) {
            result[i] %= 10;
            counter = 1;
        }
    }
    *result_length = len;
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int len = max(len1, len2);
    int counter_len = 0;
    int counter = 0;
    if (len1 < len2) {
        *result_length = -1;
        return;
    }
    if (len1 == len2) {
        for (int i = 0; i < len; i++) {
            counter_len++;
            if (buff1[i] > buff2[i]) {
                break;
            }
            if (buff1[i] < buff2[i]) {
                *result_length = -1;
                return;
            }
        }
    }
    *result_length = len;
    for (int i = len - 1; i >= 0; i--) {
        result[LEN - len + i] = buff1[i] - buff2[i] - counter;
        counter = 0;
        if (result[LEN - len + i] < 0) {
            result[LEN - len + i] = 10 + result[LEN - len + i];
            counter = 1;
        }
    }
}

int max(int a, int b) { return a > b ? a : b; }

void swap(int *a, int *b) { *a = *b; }

void copy_seq(int *seq, int *seq_copy, int n) {
    for (int i = 0; i < n; i++) {
        seq_copy[i] = seq[i];
    }
}

void seq_convertion(int *seq, int *seq_copy, int n, int c) {
    for (int i = 0; i < n; i++) {
        if (c >= 0) {
            swap(&seq[i], &seq_copy[(i + c) % n]);
        } else {
            swap(&seq[i], &seq_copy[(i + (c % n) + n) % n]);
        }
    }
}

void meaning_len(int *seq, int *length) {
    for (int i = 0; i < *length; i--) {
        if (seq[i] == 0) {
            *length -= 1;
        } else if (seq[i] != 0) {
            break;
        }
    }
}