/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:00:36 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 14:01:59 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_infile(t_redir *r)
{
	int	fd;

	fd = open(r->filename, O_RDONLY);
	if (fd == -1)
		perror(r->filename);
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (fd);
}

static int	open_outfile(t_redir *r, int flags)
{
	int	fd;

	fd = open(r->filename, flags, 0644);
	if (fd == -1)
		perror(r->filename);
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (fd);
}

int	apply_redirections(t_cmd *cmd, t_shell *sh)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		fd = 0;
		if (r->type == T_REDIR_IN)
			fd = open_infile(r);
		else if (r->type == T_HEREDOC)
			fd = open_heredoc(sh, r);
		else if (r->type == T_REDIR_OUT)
			fd = open_outfile(r, O_WRONLY | O_CREAT | O_TRUNC);
		else if (r->type == T_APPEND)
			fd = open_outfile(r, O_WRONLY | O_CREAT | O_APPEND);
		if (fd == -1)
			return (-1);
		r = r->next;
	}
	return (0);
}
