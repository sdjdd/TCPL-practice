#include <stdio.h>

int bitcount(unsigned x);

int main() {
    printf("%d", bitcount(15));

    return 0;
}

int bitcount(unsigned x) {
    int b;
    for (b = 0; x != 0; x &= (x - 1))
        if (x) ++b;
    return b;
}