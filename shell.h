#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMANDS_NUMBER 100
#define BUILD_IN_COMMANDS_NUMBER 4
#define EXTERNAL_COMMANDS_NUMBER 4


typedef struct _cmds{

    char *args[10][10];

    char *arg[10];

} cmds;

extern char curDir[100];

extern char BuildInCommands[BUILD_IN_COMMANDS_NUMBER][10];

extern char ExternalCommands[EXTERNAL_COMMANDS_NUMBER][10];

extern char ExternalCommandsPath[EXTERNAL_COMMANDS_NUMBER][30];



// pagal delimeters dinamiskai padalina simboliu eilute i atskiras eilutes
char **strtoks(char *string, char *delimeters, int *tokenNmb);

int buildInCmd(char *command);

int externalCmd(char *command);

int executeBuildInCmd(int cmdNmb, char **args);

int executeExternalCmd(char **args);


#endif