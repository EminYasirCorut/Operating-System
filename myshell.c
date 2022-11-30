#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int controlpanel(char**, int,char**);
char** split(char*,char*,int);

int main(int argc, char *argv[], char** envp){
    int exitSystem;
    char str[30];
    printf("myshell>> ");
    while(scanf("%[^\n]",str)==1){  

        int counter=1;
        for(int i=0;i<strlen(str);i++){
            if(*(str+i) == ' '){
                counter +=1;
            }
        }

        char **words=split(str, " ",counter);
        exitSystem=controlpanel(words, counter, envp);
        if(exitSystem){
           break;        
        }
        printf("myshell>> ");
        scanf("%[^\n]",str);
        getchar();
    }
    
    return 0;

}

char** split(char* str,char* c,int wordCount){
    char **words = (char**) malloc(wordCount* sizeof(char *));
    char *token = strtok(str, c);
    int counter =0;
    while (token != NULL){   
        *(words+counter++)=token;
        token = strtok(NULL, c);
    }
    return words;
}


int controlpanel(char** words, int count, char** envp){
    char* newArgv[5];
    int NumberOfCommands = 7;
	int indicator = 0;
	char* ListOfCommands[NumberOfCommands];

	ListOfCommands[0] = "exit";
	ListOfCommands[1] = "clear";
	ListOfCommands[2] = "ls";
	ListOfCommands[3] = "cat";
	ListOfCommands[4] = "execx";
	ListOfCommands[5] = "bash";
	ListOfCommands[6] = "writef";

	for (int i = 0; i < NumberOfCommands; i++) {
		if (strcmp(words[0], ListOfCommands[i]) == 0) {
			indicator = i + 1;
			break;
		}
	}

	switch (indicator) {
	case 1:
		return 1;
        break;
	case 2:
		system("clear");
        break;
	case 3:
		system("ls");
        break;
	case 4:
		printf("cat: ");
        for(int i=1;i<count;i++){
            printf("%s ", words[i]);
        }
        printf("\n");
        break;
	case 5:
		int pidOfExecx;

        pidOfExecx = fork();
        if (pidOfExecx == 0) {
        int j;
        for(int i=1;i<count;i++){
		    newArgv[i-1]=*(words+i);
	    }
        if(strcmp("-t",newArgv[0]) != 0){
            printf("'%s' tanimli degildir -t girmeniz gerekiyor.\n",newArgv[0]);
            return 0;
        }
        if(newArgv[1][0]<48 || newArgv[1][0]>57){
            printf("'%s' tanimli degildir sayi girmeniz gerekiyor.\n",newArgv[1]);
            return 0;
        }
        newArgv[count-1]=NULL;
        j=execve("execx", newArgv, envp);
                perror("error\n");
                exit(1);
        }
        break;
	case 6:
		int pidOfBash, statusOfBash;

        pidOfBash = fork();

        if (pidOfBash > 0) {
            wait(&statusOfBash);
        } else {
            newArgv[0]="bash>>";
            newArgv[1]=NULL;
            statusOfBash=execve("/bin/bash", newArgv, envp);
            perror("error\n");
            exit(1);
        }
        break;
	case 7:
		int pidOfWritef, statusOfWritef;
        pidOfWritef = fork();

        if (pidOfWritef > 0) {
                wait(&statusOfWritef);
        } else {
            newArgv[0]=*(words+1);
            newArgv[1]=*(words+2);
            newArgv[2]=NULL;
            if(strcmp("-f",newArgv[0]) != 0){
                printf("'%s' writef ten sonra -f inputu kullanilmali. \n",newArgv[0]);
                return 0;
            }
            statusOfWritef=execve("writef", newArgv, envp);
            perror("error\n");
            exit(1);
        }
        break;
	default:
		puts("Invalid Command");
        printf( "You can use following parameters\n"
                "->exit\n"
	            "->clear\n"
	            "->ls\n"
	            "->cat\n"
	            "->execx\n"
	            "->bash\n"
	            "->writef\n");
		break;
	}

	return 0;
}

