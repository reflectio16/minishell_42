#include "../include/minishell.h"

// Adds a new command node

t_cmd   *new_cmd(void)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->redirs = NULL;
    cmd->next = NULL;
    return (cmd);
}

// Adds a new argument to a command structure

void    add_arg(t_cmd *cmd, char *arg)
{
    int     i;
    int     count;
    char    **new_argv;

    if (!cmd || !arg)
        return ;
    count = 0;
    if (cmd->argv)
    {
        while (cmd->argv[count])
            count++;
    }
    new_argv = malloc(sizeof(char *) * (count + 2));
    if (!new_argv)
        return ;
    i = 0;
    while (i < count)
    {
        new_argv[i] = cmd->argv[i];
        i++;
    }
    new_argv[count] = ft_strdup(arg);
    new_argv[count + 1] = NULL;
    free (cmd->argv);
    cmd->argv = new_argv;
}

// Links a new redirection (<, >, >>, or <<) to the command.

void    add_redir(t_cmd *cmd, t_token_type type, char *file)
{
    t_redir *r;
    t_redir *new;

    if (!cmd || !file)
        return ;
    new = malloc(sizeof(t_redir));
    if (!new)
        return ;
    new->type = type;
    new->filename = ft_strdup(file);
    new->next = NULL;
    if (!cmd->redirs)
        cmd->redirs = new;
    else
    {
        r = cmd->redirs;
        while (r->next)
            r = r->next;
        r->next = new;
    }
}

