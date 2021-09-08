#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *triml(char *, char);
char *trimr(char *, char);
char *trim(char *, char);
int split(char *, char **, char);
int get_args(char *, size_t, char **);

int main(int argc, char const *argv[]) {
    char *args[100];
    char *buffer;
    size_t size = 256;

    while (1) {
        printf("Input: ");

        buffer = (char *)malloc(size);
        if (get_args(buffer, size, args) == 0) {
            printf("fail to get input\n");
            exit(1);
        }

        // 子プロセスを生成してexecを実行
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // 子プロセスで別プログラムを実行
            execv(args[0], args);
            perror("execv");
            exit(1);
        }

        // 親プロセス
        int status;
        pid_t r = waitpid(pid, &status, 0); //子プロセスの終了待ち
        if (r < 0) {
            perror("waitpid");
            exit(1);
        }

        if (!WIFEXITED(status)) {
            // 子プロセスが異常終了した場合
            printf("child status=%04x\n", status);
        }

        free(buffer);
    }

    return 0;
}

// 標準入力を読み取って空白ごとに切り分けた配列を返す関数
int get_args(char *buffer, size_t buf_size, char *args[]) {
    // 文字列が空の場合はエラー
    if (fgets(buffer, buf_size, stdin) == NULL || buffer[0] == '\n') {
        return 0;
    }

    // 行末の改行文字を取り除く
    size_t length = strlen(buffer);
    if (buffer[length - 1] == '\n') {
        buffer[--length] = '\0';
    }

    char space = ' ';
    return split(trim(buffer, space), args, space);
}

// sで両側をトリムされた文字列strを文字sごとに区切る関数
int split(char *str, char *splited[], char s) {
    int count = 0;
    size_t len = strlen(str);
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

// strの両側から文字sを削除した文字列を返す関数
char *trim(char *str, char s) { return triml(trimr(str, s), s); }

// strの左側から文字sを削除した文字列へのアドレスを返す関数
char *triml(char *str, char s) {
    int i = 0;
    size_t len = strlen(str);

    while (str[i] == s && i++ < len)
        ;

    return &str[i];
}

// strの右側から文字sを削除した文字列へのアドレスを返す関数
char *trimr(char *str, char s) {
    int i = 1;
    size_t len = strlen(str);

    while (str[len - i] == s && i++ <= len)
        ;
    str[len - i + 1] = '\0';

    return str;
}