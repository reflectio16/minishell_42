/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:59:21 by meelma            #+#    #+#             */
/*   Updated: 2025/06/12 10:15:58 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_storage(int fd, char *storage)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin_01(storage, buffer);
		if (!temp)
			return (free(buffer), free(storage), NULL);
		storage = temp;
	}
	free (buffer);
	if (bytes_read == -1)
		return (NULL);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = read_to_storage(fd, storage);
	if (!temp)
	{
		if (storage)
			free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = temp;
	line = extract_line(storage);
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	temp = get_leftover(storage);
	storage = temp;
	return (line);
}
