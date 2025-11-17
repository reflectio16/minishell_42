#include "../include/minishell.h"

void execute_pipeline(t_cmd *cmds, char **envp)
{
    int     prev_fd;
    int     status;
    
    prev_fd= -1;
    while (cmds)
    {
        execute_command(cmds, envp, &prev_fd);
        cmds = cmds->next;
    }
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    /* Wait for all children */
    while (wait(&status) > 0)
    {
        /* update global exit status */
        if (WIFEXITED(status))
            g_exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_exit_status = 128 + WTERMSIG(status);
    }
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}