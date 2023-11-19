#include <stdlib.h>
#include <syslog.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAXFD 64
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
    int i = 10;
    daemon_init("TEST", 0);
    while (i)
    {
        syslog(LOG_INFO, "daemon example ... %d", i--);
        sleep(10);
    }
    exit(0);
}