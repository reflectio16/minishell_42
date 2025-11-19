#include "../include/minishell.h"

static char *read_heredoc_line(void)
{
    char    *buf;
    int     i;
    int     r;
    char    c;

    buf = malloc(HEREDOC_BUF);
    if (!buf)
        return (NULL);
    i = 0;
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
            break ;
        }
        buf[i++] = c;
        if (c == '\n')
            break ;
    }
    buf[i] = '\0';
    return (buf);
}

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
		line = read_heredoc_line();
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

static int start_heredoc(t_shell *sh, char *limiter)
{
    int     fd[2];
    pid_t   pid;
    int     status;

    (void)sh;
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
        g_signal = SIGINT;
        close(fd[0]);
        return (-2); // special code meaning "heredoc interrupted"
    }
    return (fd[0]); // return readable fd
}

int open_heredoc(t_shell *sh, t_redir *r)
{
    int fd;
    
    fd = start_heredoc(sh, r->filename);
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