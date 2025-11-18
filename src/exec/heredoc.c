#include "../include/minishell.h"

static char *read_line_hd(void)
{
    char    *buf;
    int     i = 0;
    int     r;
    char    c;

    buf = malloc(HEREDOC_BUF);
    if (!buf)
        return (NULL);

    while (i < HEREDOC_BUF - 1)
    {
        r = read(0, &c, 1);
        if (r <= 0)
        {
            if (i == 0)
            {
                free(buf);
                return (NULL);
            }
            break;
        }
        buf[i++] = c;
        if (c == '\n')
            break;
    }
    buf[i] = '\0';
    return (buf);
}

/*static char	*read_here_doc(void)
{
	char	*buff;
	char	c;
	int		i;
	int		rd;

	i = 0;
	buff = malloc(HEREDOC_BUF);
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
}*/

static void	heredoc_child(int fd[2], char *limiter)
{
	char	*line;
	size_t	len;

	len = ft_strlen(limiter);

	signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	while (1)
	{
		line = read_line_hd();
		if (!line)
		{
			write(STDERR_FILENO,
				"warning: here-document delimited by end-of-file\n", 50);
			break ;
		}
		if (ft_strncmp(line, limiter, len) == 0
			&& (line[len] == '\n'))
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

static int start_heredoc(char *limiter)
{
    int     fd[2];
    pid_t   pid;
    int     status;

    if (pipe(fd) == -1)
        return (-1);

    pid = fork();
    if (pid < 0)
        return (close(fd[0]), close(fd[1]), -1);

    if (pid == 0)
        heredoc_child(fd, limiter);

    /* parent */
    close(fd[1]); // parent reads only
    waitpid(pid, &status, 0);

    /* If child was interrupted by SIGINT */
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        g_shell->exit_status = 130;
        close(fd[0]);
        return (-2); // special code meaning "heredoc interrupted"
    }

    return (fd[0]); // return readable fd
}
/*static int handle_here_doc(char *limiter)
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
}*/

int open_heredoc(t_redir *r)
{
    int fd = start_heredoc(r->filename);

    if (fd == -1)
        perror("heredoc");

    /* heredoc was interrupted by CTRL-C */
    if (fd == -2)
        return (-1);

    /* connect heredoc pipe to STDIN */
    if (fd >= 0)
    {
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    return (0);
}

/*int	open_heredoc(t_redir *r)
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
}*/