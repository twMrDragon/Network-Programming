#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0);

void creat_daemon(void)
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
        ERR_EXIT("fork error");
    if (pid > 0)
        exit(EXIT_SUCCESS);
    if (setsid() == -1)
        ERR_EXIT("SETSID ERROR");
    chdir("/");
    int i;
    for (i = 0; i < 3; i++)
    {
        // 關閉標準輸入、標準輸出、錯誤輸入, fd=0, 1, 2
        close(i);
        // 重定向到/dev/null
        // dev/null 是黑洞
        open("dev/null", O_RDWR);
        // 將最小的fd=0指向0指向的檔案地址
        dup(0);
    }
    umask(0);
    return;
}

int main(void)
{
    time_t t;
    int fd;
    creat_daemon();
    while (1)
    {
        fd = open("time.log", O_WRONLY | O_CREAT | O_APPEND);
        if (fd == -1)
            ERR_EXIT("open error");
        t = time(0);
        char *buf = asctime(localtime(&t));
        write(fd, buf, strlen(buf));
        FILE *pipe = popen("cat /proc/meminfo", "r");
        if (pipe == NULL)
        {
            perror("Error opening pipe");
            return 1;
        }

        char line[256];
        while (fgets(line, sizeof(line), pipe))
        {
            if (strstr(line, "MemTotal"))
            {
                write(fd, line, strlen(line));
            }
            if (strstr(line, "MemAvailable"))
            {
                write(fd, line, strlen(line));
            }
            if (strstr(line, "MemFree"))
            {
                write(fd, line, strlen(line));
                break;
            }
        }
        fclose(pipe);
        close(fd);
        sleep(60);
    }
    return 0;
}