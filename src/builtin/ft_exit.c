#include "../include/minishell.h"

static int  is_numeric(const char *s)
{
    int i;

    i = 0;
    if (s[i] == '+' || s[i] == '-')
        i++;
    if (!s[i])
        return (0);
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);
        i++;
    }
    return (1);
}

int builtin_exit(char **argv, t_shell *sh)
{
    printf("exit\n");
    if (!argv[1])
        exit(sh->last_status);
    if (!is_numeric(argv[1]))
    {
        fprintf(stderr,
           "minishell: exit: %s: numeric required\n", argv[1]);
        exit(255);
    }
    if (argv[2])
    {
        fprintf(stderr, "minishell: exit: too many arguments\n");
        return (1);
    }
    exit(ft_atoi(argv[1]));
}

