#include "../include/minishell.h"

/*void test_echo_builtin(void)
{
    char *args1[] = {"echo", NULL};
    char *args2[] = {"echo", "-n", "no newline", NULL};
    char *args3[] = {"echo", "hello", "world", NULL};
    char *args4[] = {"echo", "-n", "-n", "multiple n", NULL};
    char *args5[] = {"echo", "\"quoted\"", "arg", NULL};
    char *args6[] = {"echo", "-nnnn", "edgecase", NULL};
    char *args7[] = {"echo", "-nfoo", "tricky", NULL};

    printf("Test 1:\n");
    builtin_echo(args1);
    printf("\nTest 2:\n");
    builtin_echo(args2);
    printf("\nTest 3:\n");
    builtin_echo(args3);
    printf("\nTest 4:\n");
    builtin_echo(args4);
    printf("\nTest 5:\n");
    builtin_echo(args5);
    printf("\nTest 6:\n");
    builtin_echo(args6);
    printf("\nTest 7:\n");
    builtin_echo(args7);
    printf("\n");
}*/

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	//test_echo_builtin();
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
		//print_commands(cmds);
		
		execute_pipeline(cmds, envp);
		// Free all allocated memory
		free_tokens(tokens);
		free_cmds(cmds);
		free(input);
	}
	rl_clear_history();
	if (g_shell)
		free(g_shell);
	return (0);
}