#include "../../include/minishell.h"

static int	count_envp(char **envp)
{
	int	n;

	n = 0;
	while (envp[n])
		n++;
	return (n);
}

static char	**dup_env(char **envp)
{
	int		i;
	int		count;
	char	**copy;

	count = count_envp(envp);
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	init_shell(t_shell *sh, char **envp)
{
	sh->envp = dup_env(envp);
	if (!sh->envp)
		return (-1);
	sh->last_status = 0;
	return (0);
}

