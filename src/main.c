#include "../include/minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		tokens = lexer(input);
		print_tokens(tokens);
		cmds = parse_tokens(tokens);
		print_commands(cmds);
		free_tokens(tokens);
		free(input);
	}
	return (0);
}