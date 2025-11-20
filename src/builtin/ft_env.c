/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:39:25 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 13:40:23 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_env(char **argv, t_shell *sh)
{
	int	i;

	fprintf(stderr, "[DEBUG] builtin env executed\n");
	(void)argv;
	i = 0;
	while (sh->envp[i])
	{
		printf("%s\n", sh->envp[i]);
		i++;
	}
	return (0);
}
