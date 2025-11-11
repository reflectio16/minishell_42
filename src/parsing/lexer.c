#include "../include/minishell.h"

/*Whole page is a lexer (lexical analyzer). It breaks input strings 
into tokens that represent the basic syntactic 
elements of shell commands.*/

/*The lexer takes a raw input string like "ls -l > file.txt" 
and converts it into a linked list of tokens with specific types.*/


// Helper function
static int is_special(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

// Handles the special characters identified by is_special():
static void add_special_token(t_token **tokens, const char *input, int *i)
{
    if (input[*i] == '|')
        add_token(tokens, new_token(ft_strdup("|"), T_PIPE));
    else if (input[*i] == '<')
    {
        if (input[*i + 1] == '<')
        {
            add_token(tokens, new_token(ft_strdup("<<"), T_HEREDOC));
            (*i)++;
        }
        else
            add_token(tokens, new_token(strdup("<"), T_REDIR_IN));
    }
    else if (input[*i] == '>')
    {
        if (input[*i + 1] == '>')
        {
            add_token(tokens, new_token(ft_strdup(">>"), T_APPEND));
            (*i)++;
        }
        else
            add_token(tokens, new_token(ft_strdup(">"), T_REDIR_OUT));
    }
    (*i)++;
}

// Main lexer function.This is the core state machine that processes the input character by character:
t_token *lexer(char *input)
{
    t_token *tokens;
    int     i;
    int     start;

    tokens = NULL;
    i = 0;
    while (input[i])
    {
        if (input[i] == ' ' || input[i] == '\t')
            i++;
        else if (is_special(input[i]))
            add_special_token(&tokens, input, &i);
        else
        {
            start = i;
            while (input[i] && !is_special(input[i]) && input[i] != ' ' && input[i] != '\t')
                i++;
            add_token(&tokens, new_token(ft_substr(input, start, i), T_WORD));
        }
    }
    return (tokens);
}

// Debug function to display the token list
void    print_tokens(t_token *tokens)
{
    while (tokens)
    {
        const char *type_str[]
        = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND", "HEREDOC"};
        printf("[%s] \"%s\"\n", type_str[tokens->type], tokens->value);
        tokens = tokens->next;
    }
}

// Clean up allocated memory for the token list
void    free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens->next;
        free (tokens->value);
        free (tokens);
        tokens = tmp;
    }
}