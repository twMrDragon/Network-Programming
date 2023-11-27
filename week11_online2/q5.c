#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

double getBN(int start, int end)
{
    double result = 0;
    int sign = (start % 2 == 1 ? 1 : -1);
    for (int i = start; i <= end; i++)
    {
        result += sign * (1.0 / i);
        sign *= -1;
    }
    return result;
}

double withSingleProcess()
{
    double result = getBN(1, 40);
    return result;
}

void *thread1Function(void)
{
    double *result = malloc(sizeof(double));
    *result = getBN(11, 25);
    return (void *)result;
}

void *thread2Function(void)
{
    double *result = malloc(sizeof(double));
    *result = getBN(26, 40);
    return (void *)result;
}

double withMultipleThread()
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
    double result = getBN(1, 10);
    ;
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
    // 多進程
    clock_gettime(CLOCK_REALTIME, &startTime);
    double result = withMultipleThread();
    clock_gettime(CLOCK_REALTIME, &endTime);
    printf("Result: %.9lf\n", result);
    printf("Total time of multiprocess: %.9lf seconds\n", (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_nsec - startTime.tv_nsec) / 10000000000.0); // 毫秒

    // 單進程
    clock_gettime(CLOCK_REALTIME, &startTime);
    withSingleProcess();
    clock_gettime(CLOCK_REALTIME, &endTime);
    printf("Total time of singleprocess: %.9lf seconds\n", (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_nsec - startTime.tv_nsec) / 1000000000.0); // 毫秒

    return 0;
}