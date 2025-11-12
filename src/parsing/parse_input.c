#include "../include/minishell.h"

/*This function adds a word token to 
a command's argument list (argv array).
*/

void    handle_word_token(t_cmd *cmd, t_token *token)
{
    if (!cmd || !token)
        return ;
    add_arg(cmd, token->value);
}

/*This function processes redirection tokens (<, >, >>, <<) 
and creates redirection nodes in the command structure.*/

void    handle_redir_token(t_cmd *cmd, t_token **token)
{
    t_token  *t;
    
    t = *token;
    if (!cmd || !t || !t->next)
        return ;
    add_redir(cmd, t->type, t->next->value);
    *token = t->next;
}

/*This function handles pipe tokens (|) 
by creating a new command in the pipeline.*/

void    handle_pipe_token(t_cmd **current)
{
    t_cmd   *new;

    if (!current || !*current)
        return ;
    new = new_cmd();
    if (!new)
        return ;
    (*current)->next = new;
    *current = new;
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




