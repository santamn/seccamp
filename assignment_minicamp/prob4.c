#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *args[100];
    while (1)
    {
        printf("Input: ");
        if (get_args(args) == 0)
        {
            printf("読み取り不可");
            exit(1);
        }

        // 子プロセスを生成してexecを実行
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            // 子プロセスで別プログラムを実行
            execv(args[0], args);
            perror("execv");
            exit(1);
        }

        // 親プロセス
        int status;
        pid_t r = waitpid(pid, &status, 0); //子プロセスの終了待ち
        if (r < 0)
        {
            perror("waitpid");
            exit(1);
        }

        if (WIFEXITED(status))
        {
            // 子プロセスが正常終了の場合
            printf("child exit-code=%d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("child status=%04x\n", status);
        }
    }

    return 0;
}

// 標準入力を読み取って空白ごとに切り分けた配列を返す関数
int get_args(char *args[])
{
    char buffer[256];
    size_t length;
    char *ptr;

    if (fgets(buffer, 256, stdin) == NULL || buffer[0] == '\n')
    {
        return 0;
    }

    // 行末の改行文字を取り除く
    length = strlen(buffer);
    if (buffer[length - 1] == '\n')
    {
        buffer[--length] = '\0';
    }

    // 空白ごとに文字列を区切る
    int count = 0;
    ptr = buffer;
    for (int i = 0; i < length; i++)
    {
        if (i == length) // 行末
        {
            args[count] = ptr;
        }
        else if (buffer[i] == ' ' && buffer[i + 1] != ' ') // 連続した空白の終わり
        {
            buffer[i] = '\0';
            args[count] = ptr;
            ptr += sizeof(char) * (i + 1);
            count++;
        }
    }
    args[++count] = NULL;

    return count;
}