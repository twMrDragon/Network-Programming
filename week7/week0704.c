#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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

void *thread1Function(void)
{
    double *result = malloc(sizeof(double));
    *result = calculateNItemOfPI(9, 15);
    return (void *)result;
}

void *thread2Function(void)
{
    double *result = malloc(sizeof(double));
    *result = calculateNItemOfPI(17, 23);
    return (void *)result;
}

double calculatePIWithThread()
{
    int t1, t2;
    pthread_t thread1, thread2;
    t1 = pthread_create(&thread1, NULL, (void *)thread1Function, NULL);
    if (t1)
    {
        printf("Create pthread error!\n");
        exit(EXIT_FAILURE);
    }
    t2 = pthread_create(&thread2, NULL, (void *)thread2Function, NULL);
    if (t2)
    {
        printf("Create pthread error!\n");
        exit(EXIT_FAILURE);
    }
    double result = calculateNItemOfPI(1, 7);
    void *temp;
    pthread_join(thread1, &temp);
    result += *(double *)temp;
    free(temp);
    pthread_join(thread2, &temp);
    result += *(double *)temp;
    free(temp);
    return result;
}

int main()
{
    // 計算執行時間
    struct timespec startTime, endTime;

    // thread
    printf("With Thread:\n");
    clock_gettime(CLOCK_REALTIME, &startTime);
    calculatePIWithThread();
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
    With Thread:
    0.540671 ms
    Single Process:
    0.000197 ms */
}