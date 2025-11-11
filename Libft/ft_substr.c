/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:32:16 by meelma            #+#    #+#             */
/*   Updated: 2025/05/02 15:40:13 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	copy_len;
	size_t	str_len;
	char	*sub;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	copy_len = str_len - start;
	if (len < copy_len)
		copy_len = len;
	sub = (char *)malloc(sizeof(char) * (copy_len + 1));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, copy_len);
	sub[copy_len] = '\0';
	return (sub);
}
