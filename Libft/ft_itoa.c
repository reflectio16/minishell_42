/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:43:21 by meelma            #+#    #+#             */
/*   Updated: 2025/05/06 11:45:44 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	get_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	num = (long)n;
	len = get_num_len(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (num < 0)
		num = -num;
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	while (num != 0)
	{
		len--;
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
