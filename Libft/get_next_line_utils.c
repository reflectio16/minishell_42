/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:01:22 by meelma            #+#    #+#             */
/*   Updated: 2025/06/10 16:07:06 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_01(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin_01(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	new = malloc(ft_strlen_01(s1) + ft_strlen_01(s2) + 1);
	if (!new)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*extract_line(char	*str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_leftover(char *storage)
{
	char	*leftover;
	char	*newline_ptr;
	int		i;

	if (!storage)
		return (NULL);
	newline_ptr = ft_strchr(storage, '\n');
	if (!newline_ptr)
		return (free(storage), NULL);
	leftover = malloc(ft_strlen_01(newline_ptr + 1) + 1);
	if (!leftover)
		return (free(storage), NULL);
	i = 0;
	while (newline_ptr[1 + i])
	{
		leftover[i] = newline_ptr[1 + i];
		i++;
	}
	leftover[i] = '\0';
	free(storage);
	return (leftover);
}
