#include "../include/minishell.h"

int builtin_env(char **argv, char **envp)
{
    int         i;

    fprintf(stderr, "[DEBUG] builtin env executed\n");
    (void)argv;
    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return (0);
}