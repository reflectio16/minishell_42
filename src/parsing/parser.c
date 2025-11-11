#include "../include/minishell.h"

/*This is the main parsing engine that converts a linked list 
of tokens into a linked list of commands with their arguments 
and redirections.*/

t_cmd   *parse_tokens(t_token *tokens)
{
    t_cmd   *cmd_head;
    t_cmd   *current;
    t_token *t;

    cmd_head = NULL;
    current = NULL;
    t = tokens;
    while (t)
    {
        init_cmd(&cmd_head, &current);
        if (t->type == T_WORD)
            handle_word_token(current, t);
        else if (t->type == T_REDIR_IN || t->type == T_REDIR_OUT
                || t->type == T_APPEND || t->type == T_HEREDOC)
            handle_redir_token(current, &t);
        else if (t->type == T_PIPE)
            handle_pipe_token(&current);
        t = t->next;
    }
    return (cmd_head);
}