#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char** envp){
    //get current time
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    char *str = (char*)malloc(50 * sizeof(char));
    sprintf(str, "pid:%d, ppid:%d, time: %s",getpid(),getppid(),asctime(timeinfo));
    FILE *fp;
    if (access(argv[1], F_OK) == 0) {
     fp = fopen(argv[1],"a");//append
    
    } else {
     fp = fopen(argv[1],"w");//write
    }
    fputs(str,fp);
    fclose(fp);
      
    return 0;
}
