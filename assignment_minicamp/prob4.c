#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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
        pid_t r = waitpid(pid, &status, 0);  //子プロセスの終了待ち
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
    size_t length;
    char *ptr;

    if (fgets(buffer, 256, stdin) == NULL || buffer[0] == '\n') {
        return 0;
    }
    printf("buffer: %s\n", buffer);

    // 行末の改行文字を取り除く
    length = strlen(buffer);
    if (buffer[length - 1] == '\n') {
        buffer[--length] = '\0';
    }

    // 空白ごとに文字列を区切る
    int count = 0;
    ptr = buffer;
    for (int i = 0; i < length; i++) {
        if (i == length - 1)  // 行末
        {
            args[count] = ptr;
        } else if (buffer[i] == ' ' && buffer[i + 1] != ' ') {
            // 連続した空白の終わり
            buffer[i] = '\0';
            args[count] = ptr;
            ptr = &buffer[i] + sizeof(char);
            count++;
        }
    }
    args[++count] = NULL;

    for (int i = 0; i < count; i++) {
        printf("args[%d]: '%s'\n", i, args[i]);
    }

    return count;
}

// strの左側から文字sを削除した文字列へのアドレスを返す
char *triml(char *str, int len, char s) {
    int i = 0;
    while (str[i++] == s && i < len)
        ;

    return &str[i];
}

// strの右側から文字sを削除した文字列
char *trimr(char *str, int len, char s) {
    int i = 1;
    while (str[len - i] == s && i < len) {
        i++;
    }
    str[len - i] = '\0';

    return *str;
}