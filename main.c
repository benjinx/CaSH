#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

int last_exit_code = 0;

enum {
    MAX_ARGS = 256,
};

typedef int(*cmd_func_t)(int, char**);

typedef struct {
    const char * cmd;
    cmd_func_t   func;
} cmd_t;

int cmd_pwd(int argc, char** argv) {
    printf("%s\n", getenv("PWD"));
    return 0;
}

int cmd_exit(int argc, char** argv) {
    exit(0);
    return 0;
}

int cmd_echo(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

const cmd_t builtin[] = {
    { "pwd", &cmd_pwd },
    { "exit", &cmd_exit },
    { "echo", &cmd_echo },
    { NULL, NULL },
};


int main(int argc, char** argv)
{
    char* line;
    while ((line = readline("$ ")) != NULL) {
        if (strlen(line) > 0) {
            add_history(line);
        }

        int cmd_argc = 0;
        char * cmd_argv[MAX_ARGS];

        char * c = strtok(line, " ");
        while (c && cmd_argc < MAX_ARGS) {
            cmd_argv[cmd_argc++] = c;
            c = strtok(NULL, " ");
        }

        const cmd_t * it;
        for (it = builtin; it->cmd; ++it) {
            if (strcmp(cmd_argv[0], it->cmd) == 0) {
                last_exit_code = it->func(cmd_argc, cmd_argv);
            }
        }

        free(line);
    }
    return 0;
}