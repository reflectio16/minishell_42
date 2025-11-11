/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:00:40 by meelma            #+#    #+#             */
/*   Updated: 2025/05/01 17:22:30 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	j;

	if (*small == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (small[j] && big[i + j] && (i + j) < len)
		{
			if (big[i + j] != small[j])
				break ;
			j++;
		}
		if (small[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
