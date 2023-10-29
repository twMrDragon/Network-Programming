// server
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SHM_SIZE 50

char *replaceAllSubstring(char *origin, char *target)
{
    size_t targetLen = strlen(target);
    char *p = strstr(origin, target);
    while (p != NULL)
    {
        for (size_t i = 0; i < targetLen; i++)
        {
            p[i] = '*';
        }
        p = strstr(origin, target);
    }
}

int main()
{
    // 字串處理
    char *sentence = (char *)malloc(sizeof(char) * SHM_SIZE);
    char *targetWord = (char *)malloc(sizeof(char) * SHM_SIZE);
    scanf(" %[^\n]s", sentence);
    scanf(" %[^\n]s", targetWord);
    size_t sentenceLen = strlen(sentence);
    replaceAllSubstring(sentence, targetWord);

    // 共享記憶體
    // 命名共享記憶體(shared memory segment) "567".
    key_t key = 567;
    // Create the segment.
    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    char *shm, *s;
    if (shm_id < 0)
    {
        perror("shmget");
        printf("shm create fail");
        exit(1);
    }
    // attach 共享記憶體到本 process的變數
    // 啟用訪問
    if ((shm = shmat(shm_id, NULL, 0)) == (char *)-1)
    {
        perror("shmat");
        printf("shm attach fail");
        exit(1);
    }

    // 寫入資料到共用記憶體,等待其他 process 讀取
    s = shm;
    *s++ = sentenceLen + 1;
    for (size_t i = 0; i < sentenceLen + 1; i++)
    {
        *s++ = sentence[i];
    }

    // 等待其他 process 修改記憶體第一個字元 '*',表示已經讀取本 process 寫入資料
    while (*shm != '*')
    {
        sleep(1);
    }
    return 0;
}