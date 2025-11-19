#include "../include/minishell.h"

int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

int is_space(char c)
{
    return (c == ' ' || c == '\t');
}

void free_shell(t_shell *sh)
{
    int i = 0;
    if (!sh || !sh->envp)
        return;
    while (sh->envp[i])
    {
        free(sh->envp[i]);
        i++;
    }
    free(sh->envp);
}

int  is_valid_key(const char *key)
{
    int i;

    if (!key || !key[0])
        return (0);
    if (!ft_isalpha(key[0]) && key[0] != '_')
        return (0);
    i = 1;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
        i++;
    }
    return (1);
}