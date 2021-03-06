#include <stdio.h>

#define SPACEWIDTH 8

int main() {
    int c, n;
    int ct, cs;
    
    n = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++n;
        } else {
            ct = n / SPACEWIDTH;
            cs = n - ct * SPACEWIDTH;
            n = 0;
            while (ct > 0) {
                putchar('\t');
                --ct;
            }
            while (cs > 0) {
                putchar(' ');
                --cs;
            }
            putchar(c);
        }
    }    

    return 0;
}