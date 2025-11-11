/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:43:57 by meelma            #+#    #+#             */
/*   Updated: 2025/05/01 21:09:57 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;
	size_t	total;

	total = count * size;
	if (size != 0 && total / size != count)
		return (NULL);
	arr = malloc(total);
	if (!arr)
		return (NULL);
	ft_bzero(arr, total);
	return (arr);
}
