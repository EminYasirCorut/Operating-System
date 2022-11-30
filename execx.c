#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[], char** envp){
    
    int numberOfTurns= atoi(argv[1]);//kac kere tekrarlanacak
    
    if (strcmp("ls",argv[2])== 0)
    {
        for(int i=0;i<numberOfTurns;i++){
            int pid, status;
            pid = fork();
            if (pid > 0) {
                    wait(&status);
            } else {
                status=system("ls");
                exit(1);
            }
        }
        printf("myshell>> ");
        
    }

    if (strcmp("clear",argv[2])== 0)
    {
        for(int i=0;i<numberOfTurns;i++){
            int pid, status;
            pid = fork();
            if (pid > 0) {
                    wait(&status);
            } else {
                status=system("clear");
                exit(1);
            }
        }
        printf("myshell>> ");
        
    }
    
    
    if(strcmp("writef",argv[2]) == 0){
        char* newargv[3];
        newargv[0]=argv[3];
        newargv[1]=argv[4];
        newargv[2]=NULL;
        for(int i=0;i<numberOfTurns;i++){
            int pid, status;
            pid = fork();
            if (pid > 0) {
                    wait(&status);
            } else {
                if(strcmp("-f",newargv[0]) != 0){
                    printf("'%s' writef ten sonra -f inputu kullanilmali. \n",newargv[0]);
                    printf("myshell>> ");
                    exit(1);
                }
                status=execve("writef", newargv, envp);
                perror("error\n");
                exit(1);
            }
        }
    }
}
