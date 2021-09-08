#include <stdio.h>
#include <string.h>

char *triml(char *, char);
char *trimr(char *, char);
char *trim(char *, char);
int split(char *, char **, char);

int main(void) {
    char *args[10];
    char buffer[] = "/bin/ls    -l    -a      -b     -c";
    int length = strlen(buffer);

    printf("length: %d\n", length);

    int count = split(buffer, args, ' ');

    printf("count: %d\n", count);
    for (int i = 0; i < count; i++) {
        if (args[i] == NULL) {
            printf("args[%d]: NULL\n", i);
        } else {
            printf("args[%d]: '%s'\n", i, args[i]);
        }
    }

    return 0;
}

// sで両側をトリムされた文字列を文字sごとに区切る
int split(char *str, char **splited, char s) {
    int count = 0;
    int len = strlen(str);
    char *ptr = str;

    for (int i = 0; i < len; i++) {
        if (str[i] == s) {
            str[i] = '\0';
            splited[count++] = ptr;
            while (str[++i] == s)
                ; // 文字sの連続が終わるところまで読み飛ばす
            ptr = &str[i];
        }
    }
    splited[count] = ptr;
    splited[++count] = NULL;

    return count + 1;
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

// strの右側から文字sを削除した文字列へのアドレスを返す
char *trimr(char *str, char s) {
    int i = 1;
    int len = strlen(str);

    while (str[len - i] == s && i++ <= len)
        ;
    str[len - i + 1] = '\0';

    return str;
}