#include "../include/minishell.h"

static char	*read_here_doc(void)
{
	char	*buff;
	char	c;
	int		i;
	int		rd;

	i = 0;
	buff = malloc(10000);
	if (!buff)
		return (NULL);
	rd = read(0, &c, 1);
	while (rd > 0 && i < 9999)
	{
		buff[i++] = c;
		if (c == '\n')
			break ;
		rd = read(0, &c, 1);
	}
	if (rd <= 0 && i == 0)
		return (free(buff), NULL);
	buff[i] = '\0';
	return (buff);
}

static void	heredoc_child(int fd[2], char *limiter)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = read_here_doc();
		if (!line)
		{
			write(STDERR_FILENO, "Warning: EOF before limiter\n", 27);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& (line[ft_strlen(limiter)] == '\n'
				|| line[ft_strlen(limiter)] == '0'))
		{
			free(line);
			break ;
		}
		if (write(fd[1], line, ft_strlen(line)) == -1)
			error("write");
		free(line);
	}
	close(fd[1]);
	exit(0);
}

static int handle_here_doc(char *limiter)
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
        error("pipe");

    pid = fork();
    if (pid == -1)
        error("fork");

    if (pid == 0)
        heredoc_child(fd, limiter);
    else
    {
        close(fd[1]);
        waitpid(pid, NULL, 0);
        return fd[0];
    }
    return -1; // should never reach here
}

int	open_heredoc(t_redir *r)
{
	int	fd = handle_here_doc(r->filename);
	if (fd == -1)
		perror("heredoc");
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (fd);
}