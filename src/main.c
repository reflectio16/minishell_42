#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	g_shell = malloc(sizeof(t_shell));
	if (!g_shell)
		return (1);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);

		g_signal = 0;
		input = readline("minishell> ");
		if (g_signal == SIGINT)
		{
    		g_shell->exit_status = 130;
			if (input)
				free(input);
    		continue ; // ignore input and redisplay prompt
		}
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

		free_tokens(tokens);
		free_cmds(cmds);
		free(input);
	}
	rl_clear_history();
	if (g_shell)
		free(g_shell);
	return (0);
}