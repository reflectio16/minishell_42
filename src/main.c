#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
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
			continue ;
		}
		print_commands(cmds);
		
		execute_pipeline(cmds, envp);
		// Free all allocated memory
		free_tokens(tokens);
		free_cmds(cmds);
		free(input);
	}
	rl_clear_history();
	return (0);
}