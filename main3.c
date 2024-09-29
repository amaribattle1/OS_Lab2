#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

//Both child processes will loop for some random number of iterations, but no more than 30,
void  ChildProcess(void); 
void  ParentProcess(void); 

void main(void){
  pid_t pid1, pid2;

//this is for the first child process
  pid1 = fork();
  if (pid1 == 0){
  ChildProcess();
  }
  else {
  ParentProcess();
  }
//this is for the second child process
  pid2 = fork();
  if (pid2 == 0){
    ChildProcess();
  }
  else {
  ParentProcess();
  }
}

void ChildProcess(void){
  srandom(getpid());
  int iterations = random() % 30 + 1;
  int i;

  for (i = 0; i< iterations; i++){
    printf("Child Pid: %d is going to sleep!\n", getpid());
    int sleep_time = random() % 10 + 1;
    sleep(sleep_time);
    printf("Child Pid: %d is awake! Where is my Parent: %d?\n", getpid(), getppid());
  }

  exit(0);

}

void  ParentProcess(void){
  int status;

  pid_t completed_pid = wait(&status);
  printf("Child Pid: %d has completed\n", completed_pid);
  completed_pid = wait(&status);
  printf("Child Pid: %d has completed\n", completed_pid);

}

