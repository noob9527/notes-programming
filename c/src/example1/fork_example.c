#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * 操作系统实践
 */
int main() {
    pid_t pid;

    if((pid = fork()) == 0) {
        printf("son process pid = %ld\n", (long) getpid());
        printf("son process ppid = %ld\n", (long) getppid());
        puts("son");
        exit(0);
    }

    if((pid = fork()) == 0) {
        printf("daughter process pid = %ld\n", (long) getpid());
        printf("daughter process ppid = %ld\n", (long) getppid());
        puts("daughter");
        exit(0);
    }

    printf("father process pid = %ld\n", (long) pid);
    puts("father");
    sleep(1);
    return 0;

}
