#include "../include/minishell.h"

// Handles the special characters identified by is_special():

bool	add_special_token(t_token **tokens, const char *input, int *i)
{
	char			*val;
	t_token_type	type;

	val = NULL;
	if (input[*i] == '|')
		val = ft_strdup("|"), type = T_PIPE, (*i)++;
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			val = ft_strdup("<<"), type = T_HEREDOC, (*i) += 2;
		else
			val = ft_strdup("<"), type = T_REDIR_IN, (*i)++;
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			val = ft_strdup(">>"), type = T_APPEND, (*i) += 2;
		else
			val = ft_strdup(">"), type = T_REDIR_OUT, (*i)++;
	}
	if (!val)
		return (false);
	if (!append_token(tokens, val, type))
		return (false);
	return (true);
}

// Extract a word token, respecting quotes
char	*extract_word(const char *input, int *i)
{
	int		start;
	int		in_quote;
	char	quote_char;

	start = *i;
	in_quote = 0;
	quote_char = 0;
	while (input[*i])
	{
		if (!in_quote && is_special_char(input[*i]))
			break ;
		if (!in_quote && is_space(input[*i]))
			break ;
		if (!in_quote && (input[*i] == '"' || input[*i] == '\''))
		{
			in_quote = 1;
			quote_char = input[*i];
		}
		else if (in_quote && input[*i] == quote_char)
			in_quote = 0;
		(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

// Main lexer function.This is the core state machine that processes the input character by character:
bool	lexer(t_token **tokens, char *input)
{
	int i;

	*tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (is_special_char(input[i]))
		{
			if (!add_special_token(tokens, input, &i))
			{
				free_tokens(*tokens);
				return (false);
			}
		}
		else
		{
			if (!add_word_token(tokens, input, &i))
			{
				free_tokens(*tokens);
				return (false);
			}
		}
	}
	return (true);
}