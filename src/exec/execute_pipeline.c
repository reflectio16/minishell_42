/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:27:11 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 14:28:37 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	wait_pipeline(t_shell *sh)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			sh->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			sh->last_status = 128 + WTERMSIG(status);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static int	run_parent_builtin(t_cmd *cmd, t_shell *sh)
{
	if (!cmd || cmd->next)
		return (0);
	if (!is_builtin(cmd->argv[0]) || !builtin_is_parent(cmd->argv[0]))
		return (0);
	if (apply_redirections(cmd, sh) == -1)
	{
		sh->last_status = 1;
		return (1);
	}
	sh->last_status = exec_builtin_parent(cmd, sh);
	return (1);
}

void	execute_pipeline(t_cmd *cmds, t_shell *sh)
{
	int	prev_fd;

	if (!cmds)
		return ;
	if (run_parent_builtin(cmds, sh))
		return ;
	prev_fd = -1;
	while (cmds)
	{
		execute_command(cmds, sh, &prev_fd);
		cmds = cmds->next;
	}
	wait_pipeline(sh);
}
