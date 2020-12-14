#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "shell.h"


int main(int argc, char **argv){

    int status;

    char cmdInput[32];

    int cmdNmb = 0;

    char **commands;

    getcwd(curDir, 100);

    //char *input = NULL;
    //int len = 0;

    while (1){

        int stdinFd = dup(STDIN_FILENO);
        int stdoutFd = dup(STDOUT_FILENO);

        printf("%s$ ", curDir);

        // skaitom ieities teksta
        fgets(cmdInput, 32, stdin);
        //getline(&input, &len, stdin);

        // padarom skirtingu komandu masyva
        commands = strtoks(cmdInput, "|", &cmdNmb);

        int fdin = dup(stdinFd); 
        int fdout;

        // apdorojam kiekviena komanda (pradedant nuo kairiausios)
        for ( int i = 0; i < cmdNmb; ++i ){

            dup2(fdin, STDIN_FILENO);
            close(fdin);

            if ( i == cmdNmb - 1 ){

                fdout = dup(stdoutFd);

                printf("paskutine");
            }

            else{

                int fd[2];
                pipe(fd);
                fdin = fd[STDIN_FILENO];
                fdout = fd[STDOUT_FILENO];
            }

            dup2(fdout, STDOUT_FILENO);
            close(fdout);

            pid_t pid;
            pid = fork();

            //printf("%d\n", cmdNmb);

            if (pid == 0){

                //if (buildInCmd(commands[i]) == 666)
                    //return 0;

                externalCmd(commands[i]);
            }

            //waitpid(pid, NULL);
          
            waitpid(pid, &status, WUNTRACED);

            dup2(stdinFd, STDIN_FILENO);
            dup2(stdoutFd, STDOUT_FILENO);
            close(stdinFd);
            close(stdoutFd);

                
            

            //waitpid(pid, NULL);
             
        }

        free(commands);

        cmdNmb = 0;

        //free(input);
    }

    //free(commands);

    return 0;
}