/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:57:50 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 13:59:12 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_unset(char **argv, t_shell *sh)
{
	int	i;
	int	status;

	if (!argv[1])
		return (0);
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (!is_valid_key(argv[i]))
		{
			fprintf(stderr, "minishell: unset: `%s`: not a valid identifier\n",
				argv[i]);
			status = 1;
		}
		else
			unset_env_var(&sh->envp, argv[i]);
		i++;
	}
	return (status);
}
