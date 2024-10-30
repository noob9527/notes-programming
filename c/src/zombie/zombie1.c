#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int print_process_state(pid_t pid) {
    char cmdstring[80];
    char *end = cmdstring;
    end += sprintf(end, "%s", "cat /proc/");
    end += sprintf(end, "%ld", (long) pid);
    sprintf(end, "%s", "/status | grep State");

    puts(cmdstring);
    system(cmdstring);
}

/**
 * produce a zombie process
 * 
 * Note that:
 * - For parent process: fork() returns the child's PID (Process ID, a positive number)
 * - For child process: fork() returns 0
 * - If creation fails: returns -1
 */
int main(void) {
    pid_t pid;

    if ((pid = fork()) > 0) {
        sleep(1); // let child terminates first

        // The parent process waits for 1 second and then prints the child's state
        // Since the parent doesn't call wait() or waitpid() to wait for the child, the child becomes a zombie process
        print_process_state(pid);
    } else if (pid == 0) {
        // The child process prints its own PID and then exits
        // 
        // it will become a zombie process after return statement
        printf("child process pid = %ld\n", (long) getpid());
    }

    return 0;
}

