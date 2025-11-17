#include "../include/minishell.h"

int builtin_pwd(char **argv)
{
    char    *cwd;

    fprintf(stderr, "[DEBUG] builtin pwd executed\n");
    (void)argv;
    cwd = getcwd(NULL, 0);
    if (cwd != NULL)
    {
        printf("%s\n", cwd);
        free(cwd);
        return (0);
    }
    else
    {
        perror("pwd");
        return (1);
    }
}