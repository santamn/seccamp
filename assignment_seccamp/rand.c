#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int seed = 0x41414141;
    printf("size:%ld\n", sizeof(int));
    printf("seed:%ld\n", seed);
    srand(seed);
    for (int i = 0; i < 10; i++)
    {
        printf("%d dice:%d\n", i, rand() % 6 + 1);
    }

    return 0;
}
