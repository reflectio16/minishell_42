/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:43:53 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 13:55:32 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	split_key_value(char *arg, char **eq, char **key, char **value)
{
	*eq = ft_strchr(arg, '=');
	if (!(*eq))
	{
		*key = arg;
		*value = "";
	}
	else
	{
		**eq = '\0';
		*key = arg;
		*value = *eq + 1;
	}
}

static int	export_invalid_identifier(char *key, char *eq)
{
	fprintf(stderr,
		"minishell: export: `%s`: not a valid identifier\n", key);
	if (eq)
		*eq = '=';
	return (1);
}

static int	print_export_list(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->envp[i])
	{
		printf("declare -x %s\n", sh->envp[i]);
		i++;
	}
	return (0);
}

static int	export_single_arg(t_shell *sh, char *arg)
{
	char	*eq;
	char	*key;
	char	*value;

	split_key_value(arg, &eq, &key, &value);
	if (!is_valid_key(key))
		return (export_invalid_identifier(key, eq));
	set_env_var(&sh->envp, key, value);
	if (eq)
		*eq = '=';
	return (0);
}

int	builtin_export(char **argv, t_shell *sh)
{
	int	i;
	int	status;

	if (!argv[1])
		return (print_export_list(sh));
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (export_single_arg(sh, argv[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
