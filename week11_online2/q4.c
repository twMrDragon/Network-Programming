#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

double getCN(int start, int end)
{
    double result = 0;
    for (int i = start; i <= end; i++)
    {
        result += ((double)(i - 1)) / i;
    }
    return result;
}

void withMultipleProcesses()
{
    if (fork() == 0)
    {
        double result = getCN(1, 15);
        printf("Child result:%.9lf\n", result);
        exit(0);
    }
    else
    {
        double result = getCN(16, 40);
        // 如果有子程序，等到子程序銷毀並返回
        wait(NULL);
        printf("Parent result:%.9lf\n", result);
    }
}

void withSingleProcess()
{
    double result = getCN(1, 40);
}

int main()
{

    // 計算執行時間
    struct timespec startTime, endTime;
    // 多進程
    clock_gettime(CLOCK_REALTIME, &startTime);
    withMultipleProcesses();
    clock_gettime(CLOCK_REALTIME, &endTime);
    printf("Total time of multiprocess: %.9lf seconds\n", (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_nsec - startTime.tv_nsec) / 10000000000.0); // 毫秒

    // 單進程
    clock_gettime(CLOCK_REALTIME, &startTime);
    withSingleProcess();
    clock_gettime(CLOCK_REALTIME, &endTime);
    printf("Total time of singleprocess: %.9lf seconds\n", (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_nsec - startTime.tv_nsec) / 1000000000.0); // 毫秒

    return 0;
}