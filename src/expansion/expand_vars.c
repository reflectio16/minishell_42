/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:44:57 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 14:49:25 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*reverse_str(char *buf, int len)
{
	int		i;
	char	tmp;

	i = 0;
	while (i < len / 2)
	{
		tmp = buf[i];
		buf[i] = buf[len - i - 1];
		buf[len - i - 1] = tmp;
		i++;
	}
	return (buf);
}

// Convert integer to string (simple version for $? expansion)
static char	*itoa_exit_status(int status)
{
	int		n;
	int		len;
	char	buf[12];

	if (status == 0)
		return (ft_strdup("0"));
	n = status;
	len = 0;
	while (n)
	{
		buf[len++] = '0' + (n % 10);
		n /= 10;
	}
	buf[len] = '\0';
	reverse_str(buf, len);
	return (ft_strdup(buf));
}

// Expand one argument (replace $VAR or $?)
static char	*expand_arg(char *arg, t_shell *sh)
{
	char	*val;

	if (!arg)
		return (NULL);
	if (ft_strncmp(arg, "$?", 2) == 0)
		return (itoa_exit_status(sh->last_status));
    // Variable $VAR
	if (arg[0] == '$')
	{
		val = get_env_value(sh->envp, arg + 1);
		if (val)
			return (ft_strdup(val));
		else
			return (ft_strdup("")); // undefined variable -> empty string
	}
	return (ft_strdup(arg));
}

void	expand_variables(t_cmd *cmd, t_shell *sh)
{
	int		i;
	char	*expanded;
	char	*old;

	if (!cmd || !cmd->argv)
		return;
	i = 0;
	while (cmd->argv[i])
	{
		expanded = expand_arg(cmd->argv[i], sh);
		old = cmd->argv[i];
		cmd->argv[i] = expanded;
		free(old);
		i++;
	}
}
