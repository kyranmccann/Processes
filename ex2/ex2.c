// Write a program that opens the text.txt file (with the `fopen()` library call) located in this directory
// and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor
// returned by `fopen()`? What happens when they are written to the file concurrently?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Your code here
    FILE *txt = fopen("./text.txt", "w");
    int child = fork();

     if (child < 0)
     {
       fprintf(stderr, "Nope. fork failed");
       exit(1);
     }
     else if (child == 0)
     {
       char *str1 = "The truth is out there\n";
       fwrite(str1, sizeof(char), strlen(str1), txt);
       // txt = fopen("text.txt", "a");
       // fprintf(txt, "The truth is out there\n" );
       // fclose(txt);
       printf("child\n");
     }
     else
     {
       // txt = fopen("text.txt", "a");
       // fprintf(txt, "Shut up Mulder\n");
       // fclose(txt);
       char *str2 = "Shut up Mulder\n";
       fwrite(str2, sizeof(char), strlen(str2), txt);
       printf("parent\n");
     }
     fclose(txt);

    return 0;
}
