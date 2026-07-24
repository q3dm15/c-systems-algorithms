/*
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int m;
    if (scanf("%d", &m) != 1 || m <= 0) return 0;

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    return 0;
}
