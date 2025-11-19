#include "../include/minishell.h"

void execute_pipeline(t_cmd *cmds, t_shell *sh)
{
    int prev_fd;
    int status;

    if (!cmds)
        return;
    prev_fd = -1;
    // Single command, parent-only builtin
    if (!cmds->next && is_builtin(cmds->argv[0])
        && builtin_is_parent(cmds->argv[0]))
    {
        if (apply_redirections(cmds, sh) == -1)
        {
            sh->last_status = 1;
            return ;
        }
        sh->last_status = exec_builtin_parent(cmds, sh);
        return ;
    }

    // Multiple commands / pipeline
    while (cmds)
    {
        execute_command(cmds, sh, &prev_fd);
        cmds = cmds->next;
    }
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            sh->last_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            sh->last_status = 128 + WTERMSIG(status);
    }
    // After pipeline, reset signals
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}
