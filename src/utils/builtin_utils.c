#include "../include/minishell.h"

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strncmp(cmd, "echo", 5) == 0)
        return (1);
    if (ft_strncmp(cmd, "pwd", 4) == 0)
        return (1);
    if (ft_strncmp(cmd, "cd", 3) == 0)
        return (1);
    if (ft_strncmp(cmd, "exit", 5) == 0)
        return (1);
    if (ft_strncmp(cmd, "env", 4) == 0)
        return (1);
    if (ft_strncmp(cmd, "export", 7) == 0)
        return (1);
    if (ft_strncmp(cmd, "unset", 6) == 0)
        return (1);
    return (0);
}

int builtin_is_parent(char *cmd_name)
{
    if (!cmd_name)
        return (0);
    if (ft_strncmp(cmd_name, "cd", 3) == 0)
        return (1);
    if (ft_strncmp(cmd_name, "export", 7) == 0)
        return (1);
    if (ft_strncmp(cmd_name, "unset", 6) == 0)
        return (1);
    if (ft_strncmp(cmd_name, "exit", 5) == 0)
        return (1);
    return (0);
}

/* run builtin inside a child process (returns status) */

int exec_builtin_child(t_cmd *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (1);
    if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
        return (builtin_echo(cmd->argv));
    /*if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
        return (builtin_pwd(cmd->argv)); // TO DO: implement builtin_pwd similarly
    if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
        return (builtin_env(cmd->argv)); // TO DO: * for parent-only builtins, fallback here if executed in child
    if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
        return (builtin_cd(cmd->argv)); // TO DO: optional: implement fallback */
    return (127); // not found as builtin
}

