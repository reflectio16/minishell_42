#include "../../include/minishell.h"

static void	setup_pipes(t_cmd *cmd, int *prev_fd, int fd[2])
{
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

static void	child_process(t_cmd *cmd, char **envp, int *prev_fd, int fd[2])
{
	(void)envp;
	
	setup_pipes(cmd, prev_fd, fd);
	if (apply_redirections(cmd) == -1)
		exit(1);
	execvp(cmd->argv[0], cmd->argv);
	perror(cmd->argv[0]);
	exit(127);
}

static void	parent_process(t_cmd *cmd, int *prev_fd, int fd[2])
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

void	execute_command(t_cmd *cmd, char **envp, int *prev_fd)
{
	int		fd[2];
	pid_t	pid;

	if (cmd->next && pipe(fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
		child_process(cmd, envp, prev_fd, fd);
	else
		parent_process(cmd, prev_fd, fd);
}
