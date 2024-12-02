#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

// Both child processes will loop for some random number of iterations, but no more than 30
void ChildProcess(void);
void ParentProcess(void);

int main(void) {
    pid_t pid1, pid2;

    // Fork for the first child process
    pid1 = fork();
    if (pid1 == 0) {
        // This is the first child process
        ChildProcess();
        exit(0);  // Ensure the first child exits after completing its task
    }

    // Fork for the second child process (only the parent does this)
    pid2 = fork();
    if (pid2 == 0) {
        // This is the second child process
        ChildProcess();
        exit(0);  // Ensure the second child exits after completing its task
    }

    // Parent process (wait for both children)
    ParentProcess();

    return 0;
}

void ChildProcess(void) {
    srandom(getpid());
    int iterations = random() % 30 + 1;
    int i;

    for (i = 0; i < iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        int sleep_time = random() % 10 + 1;
        sleep(sleep_time);
        printf("Child Pid: %d is awake! Where is my Parent: %d?\n", getpid(), getppid());
    }

    exit(0);  // Ensure the child process exits after completing its work
}

void ParentProcess(void) {
    int status;

    // Wait for the first child to complete
    pid_t completed_pid = wait(&status);
    printf("Child Pid: %d has completed\n", completed_pid);

    // Wait for the second child to complete
    completed_pid = wait(&status);
    printf("Child Pid: %d has completed\n", completed_pid);
}
