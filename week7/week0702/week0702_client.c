// client
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SHM_SIZE 50

int main()
{
    // 取得共享記憶體名稱 "567", 由 server 造出
    key_t key = 567;
    int shm_id;
    char *shm, *s;
    int size = 0;

    // 連結到共享記憶體名稱.
    if ((shm_id = shmget(key, SHM_SIZE, 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }
    // attach 共享記憶體到本 process的變數
    if ((shm = shmat(shm_id, NULL, 0)) == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // 讀取 server 在共享記憶體寫入的資料
    s = shm;
    // 第一個字元表示server寫入資料 byte 個數
    size = *s++;
    printf("client:");
    for (int i = 0; i < size; i++)
    {
        printf("%c", *s++);
    }
    printf("\n");
    // 修改記憶體第一個字元 '*',表示已經讀取本 process 寫入資料
    *shm = '*';
    return 0;
}