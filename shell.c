#include "shell.h"

#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

char curDir[100];

char BuildInCommands[BUILD_IN_COMMANDS_NUMBER][10] = {
    "cd",     // 0
    "echo",   // 1
    "exit",   // 2
    "help"   // 3
    // clear
};

char ExternalCommands[EXTERNAL_COMMANDS_NUMBER][10] = {
    "pwd",   // 0
    "rm",    // 1
    "ls",    // 2
    "more"   // 3
};

char ExternalCommandsPath[EXTERNAL_COMMANDS_NUMBER][30] = {
    "/bin/pwd",   // 0
    "/bin/rm",    // 1
    "/bin/ls"     // 2
};


// padarom skirtingu komandu masyva
char **strtoks(char *string, char *delimeters, int *tokenNmb){

    char **tokens = malloc(MAX_COMMANDS_NUMBER);

    //char *tokens[10];

    //cmds answ[10]; 

    char *token = strtok(string, delimeters);

    int i = 0;

    for ( ; token != NULL; ++i){

        tokens[i] = token;

        token = strtok(NULL, delimeters);
    }

    // komandu skaicius
    *tokenNmb = i;

    return tokens;
}

int buildInCmd(char *command){

    char cmd[32];

    strcpy(cmd, command);

    // isvalom tarpus ir is visko kas tarp ju buvo padarom masyva
    char **args = malloc(10);

    char *arg = strtok(cmd, " \n");

    int i = 0;

    for (; arg != NULL; ++i ){

        args[i] = arg;

        arg = strtok(NULL, " \n");
    }

    args[i] = NULL;

    // ziurim ar pirmas musu input zodis yra komanda

    i = 0;

    for (; i < BUILD_IN_COMMANDS_NUMBER; ++i ){

        if ( strcmp(args[0], BuildInCommands[i]) == 0 ){

            // radus komanda ja vykdome
            return executeBuildInCmd(i, args);
        }
    }

    return -1;
}

int externalCmd(char *command){

    char cmd[32];

    strcpy(cmd, command);

    // isvalom tarpus ir is visko kas tarp ju buvo padarom masyva
    //char **args = malloc(10);
    char *args[10];

    char *arg = strtok(cmd, " \n");

    int i = 0;

    for (; arg != NULL; ++i ){

        args[i] = arg;

        arg = strtok(NULL, " \n");
    }

    args[i] = NULL;

    // ziurim ar pirmas musu input zodis yra komanda

    i = 0;

    for (; i < EXTERNAL_COMMANDS_NUMBER; ++i ){

        if ( strcmp(args[0], ExternalCommands[i]) == 0 ){

            // radus komanda ja vykdome
            executeExternalCmd(args);

            return 0;
        }
    }

    return -1;
}

int executeBuildInCmd(int cmdNmb, char **args){

    switch ( cmdNmb ) {

        case 0: // cd
            /* code */
            break;

        case 1: // echo 
            /* code */
            break;
            
        case 2: // exit
            /* code */
                free(args);

                return 666;
            break;

        case 3: // help
            /* code */
            break;
        
        default:

            break;
    }

    //free(args);

    return 0;
}

int executeExternalCmd(char **args){

    //pid_t pid;

    //int status;

    //pid = fork();

    //if ( pid == 0 ){
 
        if ( execvp(args[0], args) < 0 ){

            return -1;
        }
    //}

    //else if (pid != -1 ) {

        //waitpid(pid, &status, WUNTRACED);
    //}

    //free(args);

    return 0;
}