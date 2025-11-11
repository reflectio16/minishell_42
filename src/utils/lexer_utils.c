#include "../include/minishell.h"

/* This function creates a new token node 
but doesn't automatically add it to a list. 
It's a constructor function */          

t_token *new_token(char *val, t_token_type type)
{
    t_token *tok;

    tok = malloc(sizeof(t_token));
    if (!tok)
        return (NULL);
    tok->value = val;
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
char	*remove_quotes(const char *str)
{
	char	*result;
	int		i = 0;
	int		j = 0;
	char	quote = 0;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i]; // entering quote
		else if (quote && str[i] == quote)
			quote = 0; // exiting quote
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}


