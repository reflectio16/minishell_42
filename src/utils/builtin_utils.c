/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:51:03 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 14:55:53 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
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

int	builtin_is_parent(char *cmd_name)
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

int	exec_builtin_child(t_cmd *cmd, t_shell *sh)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (builtin_pwd(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (builtin_env(cmd->argv, sh));
	return (127);
}

int	exec_builtin_parent(t_cmd *cmd, t_shell *sh)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (builtin_cd(cmd->argv, sh));
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (builtin_export(cmd->argv, sh));
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (builtin_unset(cmd->argv, sh));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (builtin_exit(cmd->argv, sh));
	return (127);
}
