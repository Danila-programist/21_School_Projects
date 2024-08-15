/*
***== Получен Quest. Необходимо реализовать Pong в интерактивном режиме (режим игры в реальном времени), используя 
дополнительные библиотеки для упрощения обработки действий игроков и отображения символьной графики. Код интерактивного режима должен
 находиться в файле src/pong_interactive.c. Для реализации бонусной части обязательна реализация базовой части сначала. ==*** 
*/


#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void mapPrint(int current_Lcross_pos, int current_Rcross_pos,
              int current_xBall_pos, int current_yBall_pos, int lPlayerScore,
              int rPlayerScore);

int direction_random(void);

int main(void) {
  srand(time(NULL));
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, true);
  int current_Lcross_pos = 12;
  int current_Rcross_pos = 12;
  int lPlayerScore = 0;
  int rPlayerScore = 0;
  int current_xBall_pos = 39;
  int current_yBall_pos = 12;
  int direction_xBall = direction_random();
  int direction_yBall = direction_random();

  while (lPlayerScore != 21 || rPlayerScore != 21) {
    clear();
    mapPrint(current_Lcross_pos, current_Rcross_pos, current_xBall_pos,
             current_yBall_pos, lPlayerScore, rPlayerScore);
    char ch;
    ch = getch();
    if (current_Lcross_pos >= 1 && current_Lcross_pos <= 21) {
      if (ch == 'a' && current_Lcross_pos != 1) {
        current_Lcross_pos--;
      } else if (ch == 'z' && current_Lcross_pos != 21) {
        current_Lcross_pos++;
      }
    }

    if (current_Rcross_pos >= 1 && current_Rcross_pos <= 21) {
      if (ch == 'k' && current_Rcross_pos != 1) {
        current_Rcross_pos--;
      } else if (ch == 'm' && current_Rcross_pos != 21) {
        current_Rcross_pos++;
      }
    }

    if (current_yBall_pos + direction_yBall != 0 &&
        current_yBall_pos + direction_yBall != 24 &&
        current_xBall_pos + direction_xBall != 1 &&
        current_xBall_pos + direction_xBall != 78) {
      current_xBall_pos += direction_xBall;
      current_yBall_pos += direction_yBall; // movetation of ball
    } else if ((current_yBall_pos + direction_yBall == 0 ||
                current_yBall_pos + direction_yBall == 24) &&
               (current_xBall_pos + direction_xBall == current_Rcross_pos ||
                current_xBall_pos + direction_xBall == current_Rcross_pos + 1 ||
                current_xBall_pos + direction_xBall ==
                    current_Rcross_pos + 2) &&
               current_xBall_pos == 77) {
      direction_xBall *= -1;
      direction_yBall *= -1;
      current_xBall_pos += direction_xBall;
      current_yBall_pos += direction_yBall; // right rocket with upper border
    } else if ((current_yBall_pos + direction_yBall == 0 ||
                current_yBall_pos + direction_yBall == 24) &&
               (current_xBall_pos + direction_xBall == current_Lcross_pos ||
                current_xBall_pos + direction_xBall == current_Lcross_pos + 1 ||
                current_xBall_pos + direction_xBall ==
                    current_Lcross_pos + 2) &&
               current_xBall_pos == 2) {
      direction_xBall *= -1;
      direction_yBall *= -1;
      current_xBall_pos += direction_xBall;
      current_yBall_pos += direction_yBall; // left rocket with upper border
    } else if (current_yBall_pos + direction_yBall == 0 ||
               current_yBall_pos + direction_yBall == 24) {
      direction_yBall *= -1;
      current_xBall_pos += direction_xBall;
      current_yBall_pos +=
          direction_yBall; // condition if upper or lower border
    } else if ((current_yBall_pos + direction_yBall == current_Rcross_pos ||
                current_yBall_pos + direction_yBall == current_Rcross_pos + 1 ||
                current_yBall_pos + direction_yBall ==
                    current_Rcross_pos + 2) &&
               current_xBall_pos == 77) {
      direction_xBall *= -1;
      current_xBall_pos += direction_xBall;
      current_yBall_pos += direction_yBall; // condition if rocket right
    } else if ((current_yBall_pos + direction_yBall == current_Lcross_pos ||
                current_yBall_pos + direction_yBall == current_Lcross_pos + 1 ||
                current_yBall_pos + direction_yBall ==
                    current_Lcross_pos + 2) &&
               current_xBall_pos == 2) {
      direction_xBall *= -1;
      current_xBall_pos += direction_xBall;
      current_yBall_pos += direction_yBall; // condition if rocket left
    } else if (current_xBall_pos + direction_xBall == 78) {
      lPlayerScore += 1;
      current_xBall_pos = 39;
      current_yBall_pos = 12;
      direction_xBall = direction_random();
      direction_yBall = direction_random(); // if goal left player
      if (lPlayerScore == 21) {
        break;
      }
    } else if (current_xBall_pos + direction_xBall == 1) {
      rPlayerScore += 1;
      current_xBall_pos = 39;
      current_yBall_pos = 12;
      direction_xBall = direction_random();
      direction_yBall = direction_random(); // if goal rigth playes
      if (rPlayerScore == 21) {
        break;
      }
    }
    usleep(100000);
    refresh();

    mapPrint(current_Lcross_pos, current_Rcross_pos, current_xBall_pos,
             current_yBall_pos, lPlayerScore, rPlayerScore);
  }
  endwin();
  if (lPlayerScore == 21) {
    printf("\n\n                              LEFT PLAYER WON!!!");
  } else if (rPlayerScore == 21) {
    printf("\n\n                              RIGTH PLAYES WON!");
  }

  return 0;
}

void mapPrint(int current_Lcross_pos, int current_Rcross_pos,
              int current_xBall_pos, int current_yBall_pos, int lPlayerScore,
              int rPlayerScore) {

  printw("Player left: %d                                                   %d "
         ":Player rigth\n",
         lPlayerScore, rPlayerScore);

  for (int y = 0; y <= 24; y++) {
    for (int x = 0; x <= 79; x++) {
      if (y == current_yBall_pos && x == current_xBall_pos) {
        printw("o");
      } else if (y == 0 || y == 24) {
        printw("-");
      } else if (x == 0 || x == 79) {
        printw("|");
      } else if (x == 1 &&
                 (y == current_Lcross_pos || y == current_Lcross_pos + 2 ||
                  y == current_Lcross_pos + 1)) {
        printw("|");
      } else if (x == 78 &&
                 (y == current_Rcross_pos || y == current_Rcross_pos + 2 ||
                  y == current_Rcross_pos + 1)) {
        printw("|");

      } else if (x == 39) {
        printw("|");
      } else {
        printw(" ");
      }
    }
    printw("\n");
  }
}

int direction_random(void) {
  int random = rand() % 2;
  if (random == 1) {
    return 1;
  } else {
    return -1;
  }
}
