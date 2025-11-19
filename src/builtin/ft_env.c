#include "../include/minishell.h"

int builtin_env(char **argv, t_shell *sh)
{
    int         i;

    fprintf(stderr, "[DEBUG] builtin env executed\n");
    (void)argv;
    i = 0;
    while (sh->envp[i])
    {
        printf("%s\n", sh->envp[i]);
        i++;
    }
    return (0);
}