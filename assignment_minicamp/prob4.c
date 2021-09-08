#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *triml(char *, char);
char *trimr(char *, char);
char *trim(char *, char);
int split(char *, char **, char);
int get_args(char *, char **);

int main(int argc, char const *argv[]) {
    char *args[100];
    char *buffer;
    while (1) {
        printf("Input: ");

        buffer = (char *)malloc(256);
        if (get_args(buffer, args) == 0) {
            printf("読み取り不可");
            exit(1);
        }
        printf("Input確認: %s\n", args[0]);

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

        if (WIFEXITED(status)) {
            // 子プロセスが正常終了の場合
            printf("child exit-code=%d\n", WEXITSTATUS(status));
        } else {
            printf("child status=%04x\n", status);
        }
        free(buffer);
    }

    return 0;
}

// 標準入力を読み取って空白ごとに切り分けた配列を返す関数
int get_args(char *buffer, char *args[]) {
    if (fgets(buffer, 256, stdin) == NULL || buffer[0] == '\n') {
        return 0;
    }

    // 行末の改行文字を取り除く
    int length = strlen(buffer);
    if (buffer[length - 1] == '\n') {
        buffer[--length] = '\0';
    }

    char space = ' ';
    int count = split(trim(buffer, space), args, space);

    for (int i = 0; i < count; i++) {
        printf("args[%d]: '%s'\n", i, args[i]);
    }

    return count;
}

// sで両側をトリムされた文字列を文字sごとに区切る
int split(char *str, char *splited[], char s) {
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