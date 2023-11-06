#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#define SHARED_MEMORY_KEY 12345

double calculateNItemOfPI(int start, int end)
{
    double result = 0;
    int sign = 1;
    for (int i = start; i <= end; i += 2)
    {
        result += sign * (1.0 / i);
        sign *= -1;
    }
    return 4 * result;
}

double calculatePIWithMultipleProcesses()
{
    // 共享記憶體設定
    int shmid = shmget(SHARED_MEMORY_KEY, sizeof(double), IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    double *sharedData = (double *)shmat(shmid, NULL, 0);
    if ((int)sharedData == -1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    *sharedData = 0;

    // 產生兩個子 process 並做對應的運算
    for (int i = 0; i < 2; i++)
    {
        pid_t childPid = fork();
        if (childPid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (childPid == 0)
        {
            int start = (i + 1) * 8 + 1;
            int end = start + (4 - 1) * 2;
            double result = calculateNItemOfPI(start, end);
            *sharedData += result;
            shmdt(sharedData);
            exit(0);
        }
    }

    // 主 process
    *sharedData += calculateNItemOfPI(1, 7);
    // 等待所有子程序
    while (wait(NULL) > 0)
        ;
    double result = *sharedData;

    // 解除共享記憶體
    shmdt(sharedData);
    shmctl(shmid, IPC_RMID, NULL);
    return result;
}

double calculatePIWithSingleProcess()
{
    double result = 0;
    int sign = 1;
    for (int i = 1; i <= 23; i += 2)
    {
        result += sign * (4.0 / i);
        sign *= -1;
    }
    return result;
}

int main()
{
    // 計算執行時間
    struct timespec startTime, endTime;

    // 多進程
    printf("Multiple Processes:\n");
    clock_gettime(CLOCK_REALTIME, &startTime);
    calculatePIWithMultipleProcesses();
    clock_gettime(CLOCK_REALTIME, &endTime);
    printf("%lf ms\n", (endTime.tv_sec - startTime.tv_sec) * 1000.0 + (endTime.tv_nsec - startTime.tv_nsec) / 1000000.0); // 毫秒

    // 單進程
    printf("Single Process:\n");
    clock_gettime(CLOCK_REALTIME, &startTime);
    calculatePIWithSingleProcess();
    clock_gettime(CLOCK_REALTIME, &endTime);
    printf("%lf ms\n", (endTime.tv_sec - startTime.tv_sec) * 1000.0 + (endTime.tv_nsec - startTime.tv_nsec) / 1000000.0); // 毫秒

    return 0;

    /* last run
    Multiple Processes:
    0.874855 ms
    Single Process:
    0.000329 ms */
}