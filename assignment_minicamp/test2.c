#include <stdio.h>
#include <string.h>

char *triml(char *, char);
char *trimr(char *, char);
char *trim(char *, char);

int main(int argc, char const *argv[]) {
    char str[] = "   sadfas     ";
    char *s = trim(str, ' ');
    printf("'%s'\n", s);
    return 0;
}

// strの両側から文字sを削除した文字列を返す
char *trim(char *str, char s) { return triml(trimr(str, s), s); }

// strの左側から文字sを削除した文字列へのアドレスを返す
char *triml(char *str, char s) {
    int i = 0;
    int len = strlen(str);

    while (str[i] == s && i++ < len)
        ;

    return &str[i];
}

// strの右側から文字sを削除した文字列
char *trimr(char *str, char s) {
    int i = 1;
    int len = strlen(str);

    while (str[len - i] == s && i++ <= len)
        ;
    str[len - i + 1] = '\0';

    return str;
}