/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda_silva <ricardojustino@fastmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:52:16 by rda_silva         #+#    #+#             */
/*   Updated: 2022/02/19 10:08:36 by rda_silva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_mount_line(char *src, int fd) //#, 3
{
	char	*buffer;
	int		str_len;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free (buffer);
		return (NULL);
	}
	str_len = 1;
	while (!ft_strchr(src, '\n') && str_len != 0)
	{
		str_len = read(fd, buffer, BUFFER_SIZE);
		if (str_len == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[str_len] = '\0';
		src = ft_strjoin(src, buffer);
	}
	free (buffer);
	return (src);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved_line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	saved_line = ft_mount_line(saved_line, fd);
	if (saved_line == NULL)
		return (NULL);
	line = ft_read_line(saved_line);
	saved_line = ft_save_line(saved_line);
	if (line[0] == '\0')
	{
		free(saved_line);
		free(line);
		return (NULL);
	}
	return (line);
}