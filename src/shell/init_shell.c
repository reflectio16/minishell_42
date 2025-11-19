#include "../../include/minishell.h"

static int  count_envp(char **envp)
{
    int n = 0;
    while (envp[n])
        n++;
    return (n);
}

static char **dup_env(char **envp)
{
    int     i = 0;
    int     count = count_envp(envp);
    char    **copy = malloc(sizeof(char *) * (count + 1));

    if (!copy)
        return (NULL);
    while (i < count)
    {
        copy[i] = ft_strdup(envp[i]);
        if (!copy[i])
            return (NULL);
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

int init_shell(t_shell *sh, char **envp)
{
    sh->envp = dup_env(envp);
    if (!sh->envp)
        return (-1);
    sh->last_status = 0;
    return (0);
}
