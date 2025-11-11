#include "../include/minishell.h"

// Prints all redirections in a linked list of redirection nodes.

void    print_redirs(t_redir *r)
{
    const char *type_str;

    type_str = "UNKNOWN";
    while (r)
    {
        if (r->type == T_REDIR_IN) type_str = "REDIR_IN";
		else if (r->type == T_REDIR_OUT) type_str = "REDIR_OUT"; 
		else if (r->type == T_APPEND) type_str = "APPEND";
		else if (r->type == T_HEREDOC) type_str = "HEREDOC";
        printf("    [REDIR] type=%s file=%s\n", type_str, r->filename);
        r = r->next;
    }
}

// Prints the entire command pipeline structure in a human readable format.

void    print_commands(t_cmd *cmd)
{
    int i;
    int j;

    i = 1;
    while (cmd)
    {
        printf("Command #%d:\n", i++);
        if (cmd->argv)
        {
            j = 0;
            while (cmd->argv[j])
            {
                printf("    argv[%d] = %s\n", j, cmd->argv[j]);
                j++;
            }
                
        }
        print_redirs(cmd->redirs);
        cmd = cmd->next;
    }
}

// Debug function to display the token list
void    print_tokens(t_token *tokens)
{
    static const char *type_str[]
        = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND", "HEREDOC"};
    while (tokens)
    {
        printf("[%s] \"%s\"\n", type_str[tokens->type], tokens->value);
        tokens = tokens->next;
    }
}