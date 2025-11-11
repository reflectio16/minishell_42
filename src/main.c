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
			break ;

		if (*input)
			add_history(input); // store nonempty commands
		tokens = NULL;
		if (!lexer(&tokens, input))
		{
			fprintf(stderr, "Error: memory allocation failed in lexer\n");
			free(input);
			continue ;
		}
		print_tokens(tokens);
		cmds = parse_tokens(tokens); // implement a memory safe parser similarly
		if (!cmds)
		{
			fprintf(stderr, "Error: failed to parse tokens\n");
			free_tokens(tokens);
			free(input);
			continue;
		}
		print_commands(cmds);
		// Free all allocated memory
		free_tokens(tokens);
		//free_commands(cmds); // TO DO. we need a function to free t_cmd + redirs
		free(input);
	}
	return (0);
}