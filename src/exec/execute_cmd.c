/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:02:46 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 14:26:19 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_pipe_if_needed(t_cmd *cmd, int fd[2])
{
	if (cmd->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			return (0);
		}
	}
	return (1);
}

static pid_t	fork_child(int fd[2], t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (cmd->next)
		{
			close(fd[0]);
			close(fd[1]);
		}
	}
	return (pid);
}

static void	handle_parent(t_exec_ctx *ctx)
{
	parent_process(ctx->cmd, ctx->prev_fd, ctx->fd);
	waitpid(ctx->pid, &ctx->sh->last_status, 0);
	if (WIFEXITED(ctx->sh->last_status))
		ctx->sh->last_status = WEXITSTATUS(ctx->sh->last_status);
	else if (WIFSIGNALED(ctx->sh->last_status))
		ctx->sh->last_status = 128 + WTERMSIG(ctx->sh->last_status);
}

void    execute_command(t_cmd *cmd, t_shell *sh, int *prev_fd)
{
    t_exec_ctx ctx;

    ctx.cmd = cmd;
    ctx.sh = sh;
    ctx.prev_fd = prev_fd;

    if (!open_pipe_if_needed(cmd, ctx.fd))
        return;
    ctx.pid = fork_child(ctx.fd, cmd);
    if (ctx.pid == -1)
        return;

    if (ctx.pid == 0)
        child_process(cmd, sh, prev_fd, ctx.fd);
    else
        handle_parent(&ctx);
}