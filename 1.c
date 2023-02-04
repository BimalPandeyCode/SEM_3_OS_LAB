#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
   pid_t pid;
   int status;
   pid = fork();

   if (pid == 0) {
      printf("Child process\n");
      exit(0);
   }
   else if (pid > 0) {
      waitpid(pid, &status, 0);
      printf("Process terminated with status %d\n", status);
   }
   else {
      perror("fork");
      exit(1);
   }
   return 0;
}