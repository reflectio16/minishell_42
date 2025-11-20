/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:10:34 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 15:23:07 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Add or update environment variable
static int	append_env_var(char ***envp, char *new_var)
{
	int		count;
	char	**new_env;
	int		i;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(new_var);
		return (-1);
	}
	i = 0;
	while (i < count)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}

int	set_env_var(char ***envp, const char *key, const char *value)
{
	int		i;
	size_t	key_len;
	char	*new_var;

	new_var = build_env_var(key, value);
	if (!new_var)
		return (-1);
	i = 0;
	key_len = ft_strlen(key);
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, key_len) && (*envp)[i][key_len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_var;
			return (0);
		}
		i++;
	}
	return (append_env_var(envp, new_var));
}

int	unset_env_var(char ***envp, const char *key)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, len) && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			j = i;
			while ((*envp)[j])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}
