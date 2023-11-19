#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 256
#define MAXFD 64

double getSystemMemoryUsageRate()
{
    unsigned long memTotal;
    unsigned long memAvailable;

    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL)
    {
        perror("Error opening /proc/meminfo");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "MemTotal"))
        {
            if (sscanf(line, "MemTotal: %lu kB", &memTotal) != 1)
                fprintf(stderr, "Error parsing MemTotal value\n");
            continue;
        }
        if (strstr(line, "MemAvailable"))
        {
            if (sscanf(line, "MemAvailable: %lu kB", &memAvailable) != 1)
                fprintf(stderr, "Error parsing MemAvailable value\n");
            break;
        }
    }
    fclose(file);
    double memUsage = (double)(memTotal - memAvailable);
    return memUsage / memTotal;
}

void daemon_init(const char *pname, int facility)
{
    int i;
    pid_t pid;
    if ((pid = fork()) != 0)
        exit(0); // parent terminates
    setsid();    // 1st child continues, become session leader
    signal(SIGHUP, SIG_IGN);
    if ((pid = fork()) != 0)
        exit(0); // 1st child terminates
    // 2nd child continues
    chdir("/"); // change working directory
    umask(0);   // clear our file mode creation mask
    for (i = 0; i < MAXFD; i++)
        close(i);
    openlog(pname, LOG_PID, facility);
}

int main()
{
    daemon_init("memory usage", 0);
    while (1)
    {
        double memorySystemUsage = getSystemMemoryUsageRate();
        syslog(LOG_INFO, "Memory usage rate : %lf%%", memorySystemUsage*100);
        sleep(60);
    }
    return 0;
}