#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status, i;
    if (fork() == 0)
    {
        // 計算 PI 的後四項，(4/9-4/11+4/13-4/15)\*1000
        double last4SumResult = 0;
        int sign = 1;
        for (int i = 9; i <= 15; i += 2)
        {
            last4SumResult += sign * 4 * (1.0 / i) * 1000;
            sign *= -1;
        }
        // 回傳給父程序
        exit(last4SumResult);
    }
    else
    {
        // 計算 PI 的前四項，(4-4/3+4/5-4/7)\*1000
        double front4SumResult = 0;
        int sign = 1;
        for (int i = 1; i <= 7; i += 2)
        {
            front4SumResult += sign * 4 * (1.0 / i) * 1000;
            sign *= -1;
        }
        // 如果有子程序，等到子程序銷毀並返回
        pid = wait(&status);
        // 獲得子程序回傳值
        i = WEXITSTATUS(status);
        double allSum = (front4SumResult + i) / 1000.0;
        printf("%lf\n", allSum);
    }
    return 0;
}