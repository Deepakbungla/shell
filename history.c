#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void  main(void)
{
     char  line[1024];             
     char  *argv[64];            
     char  *history[64];

     while (1) {                   
          printf("Shell -> ");    
          gets(line);              
          printf("\n");
          parse(line, argv);
          if (strcmp(argv[0], "exit") == 0) 
               exit(0);
          checkDoubleExclmt(argv, history);
          execute(argv);


     }
}
void copyArr(char** des, char** source)
{
   int i = 0;
   for(i; i < sizeof(source)/4; i++)
   {
        des[i] = source[i];
   }
}
void checkDoubleExclmt(char** argv, char** history)
{
    if(strcmp(argv[0], "!!") == 0)
    {
        if(history[0] == NULL)
        {
           printf("\nNo Command in history\n");
        }
        else
        {
           copyArr(argv, history);
        }
    }
    
    else
    {   
        copyArr(history, argv);
    }

}
void execute(char **argv)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {                
          if (execvp(*argv, argv) < 0) {    
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                
          while (wait(&status) != pid)     
               ;
     }
}
void parse(char *line, char **argv)
{
     while (*line != '\0') {     
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     
          *argv++ = line;         
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;            
     }
     *argv = '\0';                 
}