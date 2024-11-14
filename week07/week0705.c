#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#define SHARED_MEMORY_KEY 12345

double calculatePIWithMultipleProcesses(int n, int C)
{
    int maxItem = 1;
    for (int i = 0; i < C; i++)
        maxItem *= 10;
    maxItem += 1;
    int step = 2 * n;
    int signChange = (n % 2 == 0 ? 1 : -1);

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

    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {

            double result = 0;
            int sign = (i % 2 == 0 ? 1 : -1);
            for (int j = (i * 2 + 1); j <= maxItem; j += step)
            {
                result += sign * (4.0 / j);
                sign *= signChange;
            }
            *sharedData += result;
            shmdt(sharedData);
            exit(0);
        }
    }
    // 主 process
    // 等待所有子程序
    while (wait(NULL) > 0);
    double result = *sharedData;

    // 解除共享記憶體
    shmdt(sharedData);
    shmctl(shmid, IPC_RMID, NULL);

    return result;
}

double calculateWithSingleProcess(int C)
{
    int maxItem = 1;
    for (int i = 0; i < C; i++)
        maxItem *= 10;
    maxItem += 1;

    double result = 0;
    int sign = 1;
    for (int i = 1; i <= maxItem; i += 2)
    {
        result += sign * (4.0 / i);
        sign *= -1;
    }
    return result;
}

int main()
{
    // 用戶輸入
    int n, C;
    scanf(" %d %d", &n, &C);

    // 計算執行時間
    struct timespec startTime, endTime;
    // 多進程
    printf("Multiple Processes:\n");
    clock_gettime(CLOCK_REALTIME, &startTime);
    double mProcess = calculatePIWithMultipleProcesses(n, C);
    clock_gettime(CLOCK_REALTIME, &endTime);
    printf("%lf ms\n", (endTime.tv_sec - startTime.tv_sec) * 1000.0 + (endTime.tv_nsec - startTime.tv_nsec) / 1000000.0); // 毫秒

    // 單進程
    printf("Single Process:\n");
    clock_gettime(CLOCK_REALTIME, &startTime);
    double sProcess = calculateWithSingleProcess(C);
    clock_gettime(CLOCK_REALTIME, &endTime);
    printf("%lf ms\n", (endTime.tv_sec - startTime.tv_sec) * 1000.0 + (endTime.tv_nsec - startTime.tv_nsec) / 1000000.0); // 毫秒

    return 0;

    /* last run
    6
    11
    Multiple Processes:
    1128.533377 ms
    Single Process:
    3586.998702 ms */
}