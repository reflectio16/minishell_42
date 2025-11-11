#include "../include/minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		if (*input)
			add_history(input);
		tokens = lexer(input);
		print_tokens(tokens);
		free_tokens(tokens);
		free(input);
	}
	return (0);
}