/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:15:20 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 13:23:48 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	char	*read_and_validate_input(t_shell *sh)
{
	char	*input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_signal = 0;
	set_shell_ptr(sh); // let handler access the shell
	input = readline("minishell> ");
	if (!input)
		return (NULL);
	if (g_signal == SIGINT)
	{
		sh->last_status = 130;
		free(input);
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}

static t_cmd	*tokenize_and_parse(char *input)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = NULL;
	if (!lexer(&tokens, input))
	{
		fprintf(stderr, "Error: memory allocation failed in lexer\n");
		return (NULL);
	}
	cmds = parse_tokens(tokens);
	free_tokens(tokens);
	if (!cmds)
		fprintf(stderr, "Error: failed to parse tokens\n");
	return (cmds);
}

static void	process_and_execute(t_cmd *cmds, t_shell *sh)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		expand_variables(tmp, sh);
		tmp = tmp->next;
	}
	execute_pipeline(cmds, sh);
	free_cmds(cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmds;
	t_shell	sh;

	(void)argc;
	(void)argv;
	if (init_shell(&sh, envp) < 0)
		return (perror("init_shell"), 1);
	while (1)
	{
		input = read_and_validate_input(&sh);
		if (!input)
			break ;
		cmds = tokenize_and_parse(input);
		free(input);
		if (cmds)
			process_and_execute(cmds, &sh);
	}
	rl_clear_history();
	free_shell(&sh);
	return (sh.last_status);
}
