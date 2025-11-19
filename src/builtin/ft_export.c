#include "../include/minishell.h"

static int print_export_list(t_shell *sh)
{
    int i;

    i = 0;
    while (sh->envp[i])
    {
        printf("declare -x %s\n", sh->envp[i]);
        i++;
    }
    return (0);
}

static int export_single_arg(t_shell *sh, char *arg)
{
    char *eq;
    char *key;
    char *value;

    eq = ft_strchr(arg, '=');
    if (!eq)
    {
        key = arg;
        value = "";
    }
    else
    {
        *eq = '\0';
        key = arg;
        value = eq + 1;
    }

    if (!is_valid_key(key))
    {
        fprintf(stderr,
            "minishell: export: `%s`: not a valid identifier\n", key);
        if (eq)
            *eq = '=';
        return (1);
    }

    set_env_var(&sh->envp, key, value);

    if (eq)
        *eq = '=';
    return (0);
}

int builtin_export(char **argv, t_shell *sh)
{
    int i;
    int status;

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

