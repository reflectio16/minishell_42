#include "../include/minishell.h"

// Find an environment variable by key

char    *get_env_value(char **envp, const char *name)
{
    int     i;
    int     len;

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

int count_env_vars(char **envp)
{
    int count;

    count = 0;
    while (envp[count])
        count++;
    return (count);
}

// Add or update environment variable

int set_env_var(char ***envp, const char *key, const char *value)
{
    int     i;
    size_t  key_len;
    char    *new_var;
    char    **new_envp;
    int     count;

    key_len = ft_strlen(key);
    new_var = malloc(key_len + ft_strlen(value) + 2);
    if (!new_var)
        return (-1);
    ft_strlcpy(new_var, key, key_len + 1);
    ft_strlcat(new_var, "=", key_len + 2);
    ft_strlcat(new_var, value, key_len + ft_strlen(value) + 2);

    // Look for existing variable
    i = 0;
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], key, key_len) == 0 && (*envp)[i][key_len] == '=')
        {
            free((*envp)[i]);
            (*envp)[i] = new_var;
            return (0);

        }
        i++;
    }
    count = count_env_vars(*envp);
    new_envp = malloc(sizeof(char *) * (count + 2));
    if (!new_envp)
    {
        free(new_var);
        return (-1);
    }
    i = 0;
    while (i < count)
    {
        new_envp[i] = (*envp)[i];
        i++;
    }
    new_envp[count] = new_var;
    new_envp[count + 1] = NULL;
    free(*envp);
    *envp = new_envp; 

    return (0);
}

int unset_env_var(char ***envp, const char *key)
{
    int     i = 0;
    int     j;
    size_t  len = ft_strlen(key);

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