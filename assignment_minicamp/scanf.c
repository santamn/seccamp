#include <stdio.h>

int main(void)
{
    printf("文字列を入力してEnterボタンを押してください\n");

    char str[256];
    scanf("%s", str);

    printf("入力した文字列は：%s\n", str);

    return 0;
}