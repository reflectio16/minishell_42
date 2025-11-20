/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:39:17 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 14:39:37 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*read_heredoc_line(void)
{
	char	c;
	char	*buf;
	int		i;
	int		r;

	buf = alloc_heredoc_buf();
	if (!buf)
		return (NULL);
	i = 0;
	while (i < HEREDOC_BUF - 1)
	{
		r = read(0, &c, 1);
		if (r <= 0)
			break ;
		buf[i++] = c;
		if (c == '\n')
			break ;
	}
	if (i == 0)
		return (free(buf), NULL);
	buf[i] = '\0';
	return (buf);
}

static void	heredoc_child_loop(int fd, char *limiter)
{
	char	*line;
	size_t	len;

	len = ft_strlen(limiter);
	while (1)
	{
		line = read_heredoc_line();
		if (!line)
		{
			write(STDERR_FILENO,
				"warning: here-document delimited by end-of-file\n", 50);
			break ;
		}
		if (ft_strncmp(line, limiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			break ;
		}
		write_heredoc_line(fd, line);
	}
}

static void	heredoc_child(int fd[2], char *limiter)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	heredoc_child_loop(fd[1], limiter);
	close(fd[1]);
	exit(0);
}

int	start_heredoc(t_shell *sh, char *limiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	(void)sh;
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (close(fd[0]), close(fd[1]), -1);
	if (pid == 0)
		heredoc_child(fd, limiter);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (g_signal = SIGINT, close(fd[0]), -2);
	return (fd[0]);
}

int	open_heredoc(t_shell *sh, t_redir *r)
{
	int	fd;

	fd = start_heredoc(sh, r->filename);
	if (fd == -1)
		perror("heredoc");
	if (fd == -2)
		return (-1);
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}
