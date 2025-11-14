#include "../include/minishell.h"

/* returns index of first non-option argument, 
sets *newline to 0 if -n found */

void    echo_print_args(char **argv, int i)
{
    while (argv[i])
    {
        write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
        if (argv[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
}

int builtin_echo(char **argv)
{
    int i;
    int j;
    int newline;

    i = 1;
    newline = 1;
    fprintf(stderr, "[DEBUG] builtin echo executed\n");
    while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
    {
        j = 1;
        while (argv[i][j] == 'n')
            j++;
        if (argv[i][j] != '\0')
            break ;
        newline = 0;
        i++;
    }
    echo_print_args(argv, i);
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}