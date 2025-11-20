/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:26:18 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 13:31:01 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*env_get(t_shell *sh, const char *key)
{
	return (get_env_value(sh->envp, key));
}

static int	env_set(t_shell *sh, const char *key, const char *value)
{
	return (set_env_var(&sh->envp, key, value));
}

static int	update_pwd_env(t_shell *sh)
{
	char	*cwd;
	char	*oldpwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		return (1);
	}
	oldpwd = env_get(sh, "PWD");
	if (oldpwd)
		env_set(sh, "OLDPWD", oldpwd);
	env_set(sh, "PWD", cwd);
	free(cwd);
	return (0);
}

static char	*resolve_cd_path(char **argv, t_shell *sh)
{
	char	*path;

	if (!argv[1] || ft_strncmp(argv[1], "~", 1) == 0)
	{
		path = env_get(sh, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (path);
	}
	if (ft_strncmp(argv[1], "-", 1) == 0)
	{
		path = env_get(sh, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		printf("%s\n", path);
		return (path);
	}
	return (argv[1]);
}

int	builtin_cd(char **argv, t_shell *sh)
{
	char	*path;

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = resolve_cd_path(argv, sh);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (update_pwd_env(sh));
}
