/*
***== Получен Quest. Разработать программу src/pong.c, представляющую из себя игру для двух игроков, схожую с игрой «Pong».
 Для отображения графики использовать только символьную (ASCII) графику (с выводом в терминал). Тебе необходимо реализовать 
 пошаговый вариант исключительно в рамках уже изученного материала и стандартной библиотеки.*** 
*/

#include <stdio.h>

void mapPrint(int curLCos, int curRCpos, int curXBall, int curYBall, int lPl,
              int rPl);

void playerWin(int lPl, int rPl);
int currenLcrossPos(int curLCos, char ch);
int currenRcrossPos(int curRCpos, char ch);
int checkBallInEdges(int curYBall, int dirYBall, int curXBall, int dirXBall);
int rightRockBoard(int curYBall, int dirYBall, int curXBall, int dirXBall,
                   int curRCpos);
int leftRockBoard(int curYBall, int dirYBall, int curXBall, int dirXBall,
                  int curLCos);
int condRocketR(int curYBall, int dirYBall, int curRCpos, int curXBall);
int condRocketL(int curYBall, int dirYBall, int curLCos, int curXBall);

int main(void) {
  int curLCos = 12;  // current left cross position curLCos
  int curRCpos = 12; // current right cross position curRCpos
  int lPl = 0;       // left player score lPl
  int rPl = 0;       // right player score rPl
  int curXBall = 39; // current ball position by x curXBall
  int curYBall = 12; // current ball position by y
  int dirXBall = 1;  // ball direction by x
  int dirYBall = -1; // ball direction by y

  while (lPl != 21 || rPl != 21) {
    printf("\033[H"); // clear map
    mapPrint(curLCos, curRCpos, curXBall, curYBall, lPl, rPl);
    char ch;
    ch = getchar();
    if (ch == ' ')
      continue;

    curLCos = currenLcrossPos(curLCos, ch);

    curRCpos = currenRcrossPos(curRCpos, ch);

    if (checkBallInEdges(curYBall, dirYBall, curXBall, dirXBall) == 1) {
      curXBall += dirXBall;
      curYBall += dirYBall; // movetation of ball

    } else if (rightRockBoard(curYBall, dirYBall, curXBall, dirXBall,
                              curRCpos) == 1) {
      dirXBall *= -1;
      dirYBall *= -1;
      curXBall += dirXBall;
      curYBall += dirYBall; // right rocket with upper border
    } else if (leftRockBoard(curYBall, dirYBall, curXBall, dirXBall, curLCos)) {
      dirXBall *= -1;
      dirYBall *= -1;
      curXBall += dirXBall;
      curYBall += dirYBall; // left rocket with upper border
    } else if (curYBall + dirYBall == 0 || curYBall + dirYBall == 24) {
      dirYBall *= -1;
      curXBall += dirXBall;
      curYBall += dirYBall; // condition if upper or lower border
    } else if (condRocketR(curYBall, dirYBall, curRCpos, curXBall)) {
      dirXBall *= -1;
      curXBall += dirXBall;
      curYBall += dirYBall; // condition if rocket right
    } else if (condRocketL(curYBall, dirYBall, curLCos, curXBall)) {
      dirXBall *= -1;
      curXBall += dirXBall;
      curYBall += dirYBall; // condition if rocket left
    } else if (curXBall + dirXBall == 78) {
      lPl += 1;
      curXBall = 39;
      curYBall = 12;
      dirXBall = 1;
      dirYBall = -1; // if goal left player
      if (lPl == 21) {
        break;
      }
    } else if (curXBall + dirXBall == 1) {
      rPl += 1;
      curXBall = 39;
      curYBall = 12;
      dirXBall = 1;
      dirYBall = -1; // if goal rigth playes
      if (rPl == 21) {
        break;
      }
    }

    // mapPrint(curLCos, curRCpos, curXBall, curYBall, lPl, rPl);
  }

  playerWin(lPl, rPl);

  return 0;
}

void mapPrint(int curLCos, int curRCpos, int curXBall, int curYBall, int lPl,
              int rPl) {
  printf("Player left: %d                                                   %d "
         ":Player rigth\n",
         lPl, rPl);

  for (int y = 0; y <= 24; y++) {
    for (int x = 0; x <= 79; x++) {
      if (y == curYBall && x == curXBall)
        printf("o");
      else if (y == 0 || y == 24)
        printf("-");
      else if (x == 0 || x == 79)
        printf("|");
      else if (x == 1 && (y == curLCos || y == curLCos + 2 || y == curLCos + 1))
        printf("|");
      else if (x == 78 &&
               (y == curRCpos || y == curRCpos + 2 || y == curRCpos + 1))
        printf("|");
      else if (x == 39)
        printf("|");
      else
        printf(" ");
    }
    printf("\n");
  }
}

int currenLcrossPos(int curLCos, char ch) {
  if (curLCos >= 1 && curLCos <= 21) {
    if (ch == 'a' && curLCos != 1) {
      return --curLCos;
    } else if (ch == 'z' && curLCos != 21) {
      return ++curLCos;
    }
  }
  return curLCos;
}

int currenRcrossPos(int curRCpos, char ch) {
  if (curRCpos >= 1 && curRCpos <= 21) {
    if (ch == 'k' && curRCpos != 1) {
      return --curRCpos;
    } else if (ch == 'm' && curRCpos != 21) {
      return ++curRCpos;
    }
  }
  return curRCpos;
}

int checkBallInEdges(int curYBall, int dirYBall, int curXBall, int dirXBall) {
  if (curYBall + dirYBall != 0 && curYBall + dirYBall != 24 &&
      curXBall + dirXBall != 1 && curXBall + dirXBall != 78)
    return 1;
  else
    return 0;
}

int rightRockBoard(int curYBall, int dirYBall, int curXBall, int dirXBall,
                   int curRCpos) {
  if ((curYBall + dirYBall == 0 || curYBall + dirYBall == 24) &&
      (curXBall + dirXBall == curRCpos || curXBall + dirXBall == curRCpos + 1 ||
       curXBall + dirXBall == curRCpos + 2) &&
      curXBall == 77)
    return 1;
  else
    return 0;
}

int leftRockBoard(int curYBall, int dirYBall, int curXBall, int dirXBall,
                  int curLCos) {
  if ((curYBall + dirYBall == 0 || curYBall + dirYBall == 24) &&
      (curXBall + dirXBall == curLCos || curXBall + dirXBall == curLCos + 1 ||
       curXBall + dirXBall == curLCos + 2) &&
      curXBall == 2)
    return 1;
  else
    return 0;
}

int condRocketR(int curYBall, int dirYBall, int curRCpos, int curXBall) {
  if ((curYBall + dirYBall == curRCpos || curYBall + dirYBall == curRCpos + 1 ||
       curYBall + dirYBall == curRCpos + 2) &&
      curXBall == 77)
    return 1;
  else
    return 0;
}

int condRocketL(int curYBall, int dirYBall, int curLCos, int curXBall) {
  if ((curYBall + dirYBall == curLCos || curYBall + dirYBall == curLCos + 1 ||
       curYBall + dirYBall == curLCos + 2) &&
      curXBall == 2)
    return 1;
  else
    return 0;
}

void playerWin(int lPl, int rPl) {
  if (lPl == 21) {
    printf("\n\n                              LEFT PLAYER WON!!!");
  } else if (rPl == 21) {
    printf("\n\n                              RIGTH PLAYES WON!");
  }
}
