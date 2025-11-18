#include "../include/minishell.h"

void execute_pipeline(t_cmd *cmds, char **envp)
{
    int     prev_fd;
    int     status;
    pid_t   wpid;

    prev_fd = -1;

    if (!g_shell)
        return ;
    if (cmds && !cmds->next && is_builtin(cmds->argv[0])
        && builtin_is_parent(cmds->argv[0]))
    {
        if (apply_redirections(cmds) == -1)
        {
            g_shell->exit_status = 1;
            return ;
        }
        g_shell->exit_status = exec_builtin_parent(cmds, envp);
        return ;
    }
    while (cmds)
    {
        execute_command(cmds, envp, &prev_fd);
        cmds = cmds->next;
    }
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    /* Wait for all children */
    while ((wpid = waitpid(-1, &status, 0)) > 0)
    {
        if (WIFEXITED(status))
            g_shell->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_shell->exit_status = 128 + WTERMSIG(status);
    }
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    if (prev_fd != -1)
        close(prev_fd);
}