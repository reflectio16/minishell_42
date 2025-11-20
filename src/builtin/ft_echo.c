/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:32:26 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 13:34:15 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* returns index of first non-option argument, 
sets *newline to 0 if -n found */

void	echo_print_args(char **argv, int i)
{
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
}

int	builtin_echo(char **argv)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	fprintf(stderr, "[DEBUG] builtin echo executed\n");
	if (!argv[1])
	{
		printf("\n");
		return (0);
	}
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		if (ft_strncmp(argv[i], "-n", 2) == 0)
		{
			n_flag = 1;
			i++;
		}
		else
			break ;
	}
	echo_print_args(argv, i);
	if (!n_flag)
		printf("\n");
	return (0);
}
