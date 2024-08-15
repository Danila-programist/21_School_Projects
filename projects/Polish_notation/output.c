#include "output.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "algorithm.h"
#include "stack.h"

void output(char* postfix) {
    double ans[81];
    for (int k = 0; k < 81; k++) ans[k] = decoding(postfix, 4 * M_PI * (double)k / (double)80);

    for (int k = 0; k < 81; k++) {
        printf("step %d: %.2lf\n", k, ans[k]);
    }
    printf("                                     GRAPH\n");
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 81; j++) {
            if ((1.0 - 1.0 / 13.0 * (double)i >= ans[j] && 1.0 - 1.0 / 13.0 * (double)(i + 1) <= ans[j])) {
                printf("*");
            } else if (j == 0) {
                if (i == 0)
                    printf("^");
                else
                    printf("|");
            } else if (i == 13) {
                if (j == 80)
                    printf(">");
                else
                    printf("-");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}