#include "../include/minishell.h"    

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*tok;

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
void	add_token(t_token **lst, t_token *new)
{
	t_token	*tmp;

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
char *strip_outer_quotes(const char *str)
{
    int len;
    char *out;

    len = ft_strlen(str);
    if ((str[0] == '"' && str[len - 1] == '"')
        || (str[0] == '\'' && str[len - 1] == '\''))
    {
        out = ft_substr(str, 1, len - 2);
        return (out);
    }
    return (ft_strdup(str));
}

bool	append_token(t_token **tokens, char *value, t_token_type type)
{
	t_token	*tok;

	tok = new_token(value, type);
	if (!tok)
		return (false);
	add_token(tokens, tok);
	return (true);
}

bool add_word_token(t_token **tokens, const char *input, int *i)
{
    char *raw;
    char *clean;

    raw = extract_word(input, i);
    if (!raw)
        return (false);
    clean = strip_outer_quotes(raw);
    free(raw);
    if (!clean)
        return (false);
    if (!append_token(tokens, clean, T_WORD))
    {
        free(clean);
        return (false);
    }
    return (true);
}
