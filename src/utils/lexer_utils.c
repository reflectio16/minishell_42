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



