#include <stdio.h>
#include <stdlib.h>

void dump(char *target, int size)
{
    printf("[");
    for (int i = 0; i < size; i++)
    {
        printf("%d", target[i]);
        if (i != (size - 1))
        {
            printf(", ");
        }
    }
    printf("]\n");
}

void decode(char *addr, int size, long data, char *text, int text_len)
{
    long lVar1;
    long local_res18;
    // 追加
    long access;

    local_res18 = data;

    for (int i = 0; i < size; i++)
    {
        // 謎の値を設定
        lVar1 = local_res18 * 5 + 0x2365f703;
        // .rsrcからメモリにロードした値(= リソースデータ)を前から順番にアクセスするためのアドレス値
        access = (long)addr + (long)i;

        // 謎の値との排他的論理和を計算
        *(char *)access ^= (char)lVar1;
        // 謎のアドレスを謎に2bit右にシフトして謎の値を減算
        local_res18 = (lVar1 >> 2) - 0x1ca9;

        // 謎のbit演算と足し算
        *(char *)access = *(char *)access ^ text[i % text_len] + text[i % text_len] + (char)local_res18;
    }
    return;
}

// 9d cb 1e a7 65 ed 5f 4d 01 d6 49 4a 55 bd d7 83 52 07 30 40
// a1より大きい値を1引いた数
// {0x9d, 0xca, 0x1e, 0xa6, 0x65, 0xec, 0x5f, 0x4d, 0x01, 0xd5, 0x49, 0x4a, 0x55, 0xbc, 0xd6, 0x83, 0x52, 0x07, 0x30, 0x40}
// 元の配列
// {0x9d, 0xcb, 0x1e, 0xa7, 0x65, 0xed, 0x5f, 0x4d, 0x01, 0xd6, 0x49, 0x4a, 0x55, 0xbd, 0xd7, 0x83, 0x52, 0x07, 0x30, 0x40}
// 問題の配列
//　{0x8d,0x93,0x13,0x8a,0x43,0xb6,0x59,0x4d,0x41,0x80,0x1b,0x53,0x02,0x86,0xf2,0xed,0x55,0x55,0x78,0x59,0x8b,0x77,0x35,0x17,0x56}

int main(int argc, char const *argv[])
{
    unsigned char resource[25] = {0x8d, 0x93, 0x13, 0x8a, 0x43, 0xb6, 0x59, 0x4d, 0x41, 0x80, 0x1b, 0x53, 0x02, 0x86, 0xf2, 0xed, 0x55, 0x55, 0x78, 0x59, 0x8b, 0x77, 0x35, 0x17, 0x56};
    for (int i = 0; i < 25; i++)
    {
        if (resource[i] > 0xa1)
        {
            resource[i]--;
        }
    }

    printf("元のリソースデータ:");
    dump(resource, 25);
    printf("\n");

    decode(resource, 25, 0x89192712, "SECCAMP2021", 11);

    printf("decoded:%s\n", resource);
    dump(resource, 25);

    return 0;
}