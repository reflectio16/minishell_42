#include "../include/minishell.h"

/* This function creates a new token node 
but doesn't automatically add it to a list. 
It's a constructor function */          

t_token *new_token(char *value, t_token_type type)
{
    t_token *tok;

    tok = malloc(sizeof(t_token));
    if (!tok)
	{
		free(value);
		return (NULL);
	}
    tok->value = value;
    tok->type = type;
    tok->next = NULL;
    return (tok);
}

// This function adds new token node to the list

void    add_token(t_token **lst, t_token *new)
{
    t_token *tmp;

    if (!lst || !new)
        return ;
    if (*lst == NULL)
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

// Removes surrounding and inner quotes from a token value
char *remove_quotes(char *str)
{
    char *res;
    int i = 0, j = 0;
    char quote = 0;

    res = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!res)
    {
        free(str);
        return NULL;
    }
    while (str[i])
    {
        if (!quote && (str[i] == '"' || str[i] == '\''))
            quote = str[i++];
        else if (quote && str[i] == quote)
            quote = 0, i++;
        else
            res[j++] = str[i++];
    }
    res[j] = 0;
    free(str);
    return res;
}

bool append_token(t_token **tokens, char *value, t_token_type type)
{
    t_token *tok = new_token(value, type);
    if (!tok)
        return false;
    add_token(tokens, tok);
    return true;
}

bool add_word_token(t_token **tokens, const char *input, int *i)
{
    char *word = extract_word(input, i);
    if (!word)
        return false;
    char *clean = remove_quotes(word);
    if (!clean)
        return false;
    if (!append_token(tokens, clean, T_WORD))
        return false;
    return true;
}
