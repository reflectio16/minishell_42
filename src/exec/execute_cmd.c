#include "../../include/minishell.h"

static void setup_pipes(t_cmd *cmd, int *prev_fd, int fd[2])
{
    if (*prev_fd != -1)
    {
        if (dup2(*prev_fd, STDIN_FILENO) == -1)
        {
            perror("dup2 prev_fd");
            exit(1);
        }
        close(*prev_fd);
    }

    if (cmd->next)
    {
        if (dup2(fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2 fd[1]");
            exit(1);
        }
        close(fd[0]);
        close(fd[1]);
    }
}

static void	child_process(t_cmd *cmd, t_shell *sh, int *prev_fd, int fd[2])
{
	int	status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
    	exit(1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	printf("[DEBUG] Executing command: %s\n", cmd->argv[0]);
	for (int i = 0; cmd->argv[i]; i++)
    printf("  argv[%d] = '%s'\n", i, cmd->argv[i]);
	fflush(stdout);

	setup_pipes(cmd, prev_fd, fd);
	if (apply_redirections(cmd, sh) == -1)
		exit(1);
	if (is_builtin(cmd->argv[0]))
	{
		status = exec_builtin_child(cmd, sh);
		exit(status);
	}
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

void	execute_command(t_cmd *cmd, t_shell *sh, int *prev_fd)
{
	int		fd[2];
	pid_t	pid;

	if (!cmd || !cmd->argv || !cmd->argv[0])
        return ;
	if (cmd->next && pipe(fd) == -1)
		return (perror("pipe"));
	pid = fork();
if (pid == -1)
    {
        perror("fork");
        if (cmd->next)
        {
            close(fd[0]);
            close(fd[1]);
        }
        return;
    }
	if (pid == 0)
		child_process(cmd, sh, prev_fd, fd);
	else
	{
		sh->last_status = 0;
        parent_process(cmd, prev_fd, fd);
        waitpid(pid, &sh->last_status, 0);
        if (WIFEXITED(sh->last_status))
            sh->last_status = WEXITSTATUS(sh->last_status);
        else if (WIFSIGNALED(sh->last_status))
            sh->last_status = 128 + WTERMSIG(sh->last_status);
	}
}
