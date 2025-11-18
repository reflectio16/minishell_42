#include "../include/minishell.h"

static int update_pwd_env(char **envp)
{
    char    *cwd;
    char    *oldpwd;
    int     i;

    oldpwd = getenv("PWD");
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("cd");
        return (0);
    }
    if (oldpwd)
    {
        i = 0;
        while (envp[i])
        {
            if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
            {
                envp[i] = ft_strjoin("OLDPWD=", oldpwd); // no free
                break  ;
            }
            i++;
        }
    }
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PWD=", 4) == 0)
        {
            envp[i] = ft_strjoin("PWD=", cwd);
            break;
        }
        i++;
    }
    free(cwd);
    return (0);
}

static char *get_cd_path(char **argv)
{
    char    *path;

    if (!argv[1] || ft_strncmp(argv[1], "~", 1) == 0)
    {
        path = getenv("HOME");
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (NULL);
        }
    }
    else if (ft_strncmp(argv[1], "-", 2) == 0)
    {
        path = getenv("OLDPWD");
        if (!path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            return (NULL);
        }
        printf("%s\n", path);
    }
    else
        path = argv[1];
    if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (NULL);
	}
    return (path);
}

int builtin_cd(char **argv, char **envp)
{
    char    *path;

    fprintf(stderr, "[DEBUG] builtin cd executed\n");
    if (argv[1] && argv[2])
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        return (1);
    }
    path = get_cd_path(argv);
    if (!path)
        return (1);
    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        return (1);
    }
    return (update_pwd_env(envp));
}

