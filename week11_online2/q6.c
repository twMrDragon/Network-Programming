#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#define SHARED_MEMORY_KEY 12345

double getNLevel(int n)
{
    if (n == 0)
        return 1;
    double result = 1;
    for (int i = 2; i <= n; i++)
    {
        result = result / ((double)(i));
    }
    return result;
}

double getE(int start, int end)
{
    double result = 0;
    for (int i = start; i <= end; i++)
    {
        result += getNLevel(i);
    }
    return result;
}

int main()
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

    if (fork() == 0)
    {
        double result = getE(0, 2);
        *sharedData += result;
        printf("Child result: %.9lf\n", result);
        exit(0);
    }
    else
    {
        double result = getE(3, 10);
        *sharedData += result;
        // 如果有子程序，等到子程序銷毀並返回
        wait(NULL);
        printf("Parent result: %.9lf\n", result);
    }
    printf("Total result: %.9lf\n", *sharedData);

    // 解除共享記憶體
    shmdt(sharedData);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}