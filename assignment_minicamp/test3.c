#include <stdio.h>

int main(int argc, char const* argv[]) {
    int i = 0;
    if (i++ <= 0) {
        printf("0のまま: %d\n", i);
    } else {
        printf("1になる: %d\n", i);
    }
    return 0;
}
