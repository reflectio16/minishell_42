/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:16:14 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 16:17:15 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*alloc_heredoc_buf(void)
{
	char	*buf;

	buf = malloc(HEREDOC_BUF);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	return (buf);
}

int	write_heredoc_line(int fd, char *line)
{
	if (!line)
		return (0);
	if (write(fd, line, ft_strlen(line)) == -1)
		error("write");
	free(line);
	return (1);
}
static void setup_pipes_child(t_cmd *cmd, int *prev_fd, int fd[2])
{
    if (*prev_fd != -1)          // This command receives input
    {
        dup2(*prev_fd, STDIN_FILENO);
        close(*prev_fd);
    }

    if (cmd->next)               // This command outputs into a pipe
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
}

void child_process(t_cmd *cmd, t_shell *sh, int *prev_fd, int fd[2])
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    setup_pipes_child(cmd, prev_fd, fd);
    if (apply_redirections(cmd, sh) == -1)
        exit(1);
    if (is_builtin(cmd->argv[0]))
        exit(exec_builtin_child(cmd, sh));
    execvp(cmd->argv[0], cmd->argv);
    perror(cmd->argv[0]);
    exit(127);
}

void	parent_process(t_cmd *cmd, int *prev_fd, int fd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
}
