/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:08:25 by meelma            #+#    #+#             */
/*   Updated: 2025/05/02 18:08:22 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_words(const char *s, char c)
{
	int	count;
	int	word;

	count = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && !word)
		{
			word = 1;
			count++;
		}
		else if (*s == c)
			word = 0;
		s++;
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	free_result(char **result, int i)
{
	while (i-- > 0)
		free(result[i]);
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (*s == c)
			s++;
		len = word_len(s, c);
		result[i] = ft_substr(s, 0, len);
		if (!result[i])
			return (free_result(result, i), NULL);
		s += len;
		i++;
	}
	result[i] = NULL;
	return (result);
}
