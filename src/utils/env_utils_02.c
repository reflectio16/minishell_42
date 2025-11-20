/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:23:50 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 15:25:14 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Find an environment variable by key
char	*get_env_value(char **envp, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

// Count environment variables
int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	*build_env_var(const char *key, const char *value)
{
	size_t	len;
	char	*str;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, key, ft_strlen(key) + 1);
	ft_strlcat(str, "=", len);
	ft_strlcat(str, value, len);
	return (str);
}
