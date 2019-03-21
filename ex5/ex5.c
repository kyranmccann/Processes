// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write
// the three messages to the parent and have the parent print out
// the messages.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MSGSIZE 16

char* msg1 = "hello world #1";
char* msg2 = "hello world #2";
char* msg3 = "hello world #3";

int main(void)
{
    // Your code here
    char buf[MSGSIZE];
    int p[2];
    if (pipe(p) < 0)
    {
      fprintf(stderr, "Nope. Pipe failed\n");
      exit(1);
    }
    int rc = fork();

    if (rc < 0)
    {
      printf("Nope. Fork failed\n");
      exit(2);
    }
    else if (rc == 0)
    {
      printf("child writing\n");

      write(p[1], msg1, MSGSIZE);
      write(p[1], msg2, MSGSIZE);
      write(p[1], msg3, MSGSIZE);

      printf("child done\n");
    }
    else
    {
      waitpid(rc, NULL, 0);;
      close(p[1]);
      printf("parent\n");

      while (read(p[0], buf, MSGSIZE) > 0)
      {
        printf("%s\n", buf);
      }
      printf("parent done\n");
    }
    return 0;
}
