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

// Extract a word token, respecting quotes

static char *extract_word(const char *input, int *i)
{
    int  start;
    int  in_quote = 0;
    char quote_char = 0;

    start = *i;
    while (input[*i])
    {
        if (!in_quote && is_special(input[*i]))
            break;
        if (!in_quote && (input[*i] == ' ' || input[*i] == '\t'))
            break;
        if (!in_quote && (input[*i] == '"' || input[*i] == '\''))
        {
            in_quote = 1;
            quote_char = input[*i];
            (*i)++; // skip opening quote
            continue;
        }
        else if (in_quote && input[*i] == quote_char)
        {
            in_quote = 0;
            (*i)++; // skip closing quote
            continue;
        }
        (*i)++;
    }
    return ft_substr(input, start, *i - start);
}


// Main lexer function.This is the core state machine that processes the input character by character:
t_token *lexer(char *input)
{
    t_token *tokens;
    int     i;
    char    *word;
    char    *clean;

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
            word = extract_word(input, &i);
            clean = remove_quotes(word);
            free(word);
            add_token(&tokens, new_token(clean, T_WORD));
        }
    }
    return (tokens);
}
