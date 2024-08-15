/*
***== Получен Quest. На языке программирования Си разработать программу src/game_of_life.c, представляющую собой визуализацию 
«The Game of Life». Для отображения графики использовать только символьную (ASCII) графику (с выводом в терминал). 
Необходимо реализовать в игре Game of life интерактивный режим, c настройкой скорости игры. ==***
*/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define length 80
#define width 25
#define DIED ' '
#define LIVED '*'

void output(char **arr, int n, int m, int speed);  // вывод в терминал картинки
char **init_array(int M, int N);  // инициализация двумерного массива свободной памятью
void next_step(char **arr_prev, char **arr_next);  // следующий шаг в движении game of life
int live_or_die(char **arr, int i_target, int j_target,
                int died_or_lived);  // узнаем, будет ли жива МЕРТВАЯ или ЖИВАЯ клетка в следующий ход
int border_(int i, int j);  // для того чтобы не вылезать за поле зрения двойного массива
int border_after(int i, int j, char **arr);  // для того чтобы найти соседей для крайних клеток
void input_array(char **arr);  //  cчитывание файла в этот массив

int main() {
    char **arr_1 = (char **)init_array(width, length);
    char **arr_2 = (char **)init_array(width, length);
    input_array(arr_1);
    if (freopen("/dev/tty", "r", stdin)) {
        int speed = 5;
        char ch = 1;
        int counter = 0;
        initscr();
        cbreak();
        noecho();
        nodelay(stdscr, true);
        output(arr_1, width, length, speed);
        while (ch) {
            ch = getch();
            if (counter % 2 == 0) {
                clear();
                output(arr_1, width, length, speed);
                next_step(arr_1, arr_2);
            } else {
                clear();
                output(arr_2, width, length, speed);
                next_step(arr_2, arr_1);
            }
            counter++;
            counter %= 2;
            if (ch == 'q')  // exit
            {
                ch = 0;
            }
            if (ch == 'a') {
                if (speed != 20) {
                    speed++;
                }
            }
            if (ch == 'z') {
                if (speed != 1) {
                    speed--;
                }
            }
            usleep(100000 / speed);
            refresh();
        }
        clear();
        endwin();
    }
    printf("THE END OF GAME");
    free(arr_2);
    free(arr_1);
    return 0;
}

void input_array(char **arr) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            int ch;
            scanf("%d", &ch);
            arr[i][j] = (ch == 1 ? LIVED : DIED);
        }
    }
}

void output(char **arr, int n, int m, int speed) {  // вывод карты
    printw("speed: %d                             GAME OF LIFE\n", speed);
    for (int k = 0; k < 82; k++) {
        printw("-");
    }
    printw("\n");
    for (int i = 0; i < n; i++) {
        printw("|");
        for (int j = 0; j < m; j++) {
            printw("%c", arr[i][j]);
        }
        printw("|");
        printw("\n");
    }
    for (int k = 0; k < 82; k++) {
        printw("-");
    }
    printw("\nHotkeys:\nq - exit\na - increase speed\nz - dicrease speed");
}

char **init_array(int M, int N) {  // инициализация динамического массива
    char **seq = malloc(M * N * sizeof(char) + M * sizeof(char *));
    char *ptr = (char *)(seq + M);
    for (int i = 0; i < M; i++) {
        seq[i] = ptr + N * i;
    }
    return seq;
}

void next_step(char **arr_prev,
               char **arr_next)  // проходимся по всему массиву и заменяем на следующий ход элементы
{
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            if (arr_prev[i][j] == DIED) {
                arr_next[i][j] =
                    (live_or_die(arr_prev, i, j, DIED) ? LIVED
                                                       : DIED);  // определяю будет ли жива мертвая клетка
            } else {
                arr_next[i][j] =
                    (live_or_die(arr_prev, i, j, LIVED) ? LIVED
                                                        : DIED);  // определяем будет ли жива живая клетка
            }
        }
    }
}

int live_or_die(char **arr, int i_target, int j_target, int died_or_lived) {
    int output_died_or_lived;
    int counter = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0 && died_or_lived == LIVED) counter--;
            if (border_(i_target + i, j_target + j))  // если нет переходов за границы
            {
                if (arr[i_target + i][j_target + j] == LIVED) {
                    counter++;
                }
            }
            if (border_after(i_target + i, j_target + j, arr)) {
                counter++;
            }
        }
    }
    if ((counter == 3 || counter == 2) && died_or_lived == LIVED) {
        output_died_or_lived = 1;
    } else if (counter == 3 && died_or_lived == DIED) {
        output_died_or_lived = 1;
    } else {
        output_died_or_lived = 0;
    }

    return output_died_or_lived;
}

int border_(int i, int j) {
    int output_border = 0;
    if (i >= 0 && i < width && j >= 0 && j < length) output_border = 1;
    return output_border;
}

int border_after(int i, int j, char **arr) {
    int output_border = 0;

    if (j >= length && i < 0) {
        if (arr[width - 1][0] == LIVED) {
            output_border = 1;
        }
    } else if (i < 0 && j < 0) {
        if (arr[width - 1][length - 1] == LIVED) {
            output_border = 1;
        }
    } else if (i >= width && j >= length) {
        if (arr[0][0] == LIVED) {
            output_border = 1;
        }
    } else if (i >= width && j < 0) {
        if (arr[0][length - 1] == LIVED) {
            output_border = 1;
        }
    } else if (j >= 0 && j < length && i < 0) {
        if (arr[width - 1][j] == LIVED) {
            output_border = 1;
        }
    } else if (j >= 0 && j < length && i >= width) {
        if (arr[0][j] == LIVED) {
            output_border = 1;
        }
    } else if (i >= 0 && i < width && j < 0) {
        if (arr[i][length - 1] == LIVED) {
            output_border = 1;
        }
    } else if (i >= 0 && i < width && j >= length) {
        if (arr[i][0] == LIVED) {
            output_border = 1;
        }
    }

    return output_border;
}
