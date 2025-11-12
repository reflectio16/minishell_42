#include "../include/minishell.h"

/*This function adds a word token to 
a command's argument list (argv array).
*/

void    handle_word_token(t_cmd *cmd, t_token *token)
{
    int     argc;
    char    **new_argv;

    argc = 0;
    while (cmd->argv && cmd->argv[argc])
        argc++;
    new_argv = malloc(sizeof(char *) * (argc + 2));
    if (!new_argv)
        return ;
    if (cmd->argv)
    {
        ft_memcpy(new_argv, cmd->argv, sizeof(char *) * argc);
        free(cmd->argv);
    }
    new_argv[argc] = ft_strdup(token->value);
    new_argv[argc + 1] = NULL;
    cmd->argv = new_argv;
}

/*This function processes redirection tokens (<, >, >>, <<) 
and creates redirection nodes in the command structure.*/

void    handle_redir_token(t_cmd *cmd, t_token **token)
{
    t_redir *new;

    new = ft_calloc(1, sizeof(t_redir));
    if (!new)
        return ;
    new->type = (*token)->type;
    if ((*token)->next && (*token)->next->type == T_WORD)
        new->filename = ft_strdup((*token)->next->value);
    else
        printf("syntax error: redirection without filename\n");
    new->next = cmd->redirs;
    cmd->redirs = new;
    *token = (*token)->next;
}

/*This function handles pipe tokens (|) 
by creating a new command in the pipeline.*/

void    handle_pipe_token(t_cmd **current)
{
    (*current)-> next = ft_calloc(1, sizeof(t_cmd));
    *current = (*current)->next;
}

/*This function initializes a new command node when needed, 
ensuring we always have a current command to work with.
* This function is called at the start of every token processing 
loop in parse_tokens():*/

void    init_cmd(t_cmd **cmd_head, t_cmd **current)
{
    if (!*cmd_head)
    {
        *cmd_head = new_cmd();
        *current = *cmd_head;
    }
    else if (!*current)
    {
        *current = new_cmd();
    }
}




