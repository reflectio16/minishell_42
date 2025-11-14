#include "../include/minishell.h"

void execute_pipeline(t_cmd *cmds, char **envp)
{
    int prev_fd;
    
    prev_fd= -1;
    while (cmds)
    {
        execute_command(cmds, envp, &prev_fd);
        cmds = cmds->next;
    }

    /* Wait for all children */
    while (wait(NULL) > 0)
        ;
}