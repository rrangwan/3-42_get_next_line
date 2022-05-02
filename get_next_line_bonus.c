/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:11:17 by rrangwan          #+#    #+#             */
/*   Updated: 2022/01/25 13:23:50 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*old_read[257];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (0);
	old_read[fd] = ft_read(fd, old_read[fd]);
	if (!old_read[fd])
		return (NULL);
	line = ft_line(old_read[fd]);
	old_read[fd] = ft_reread(old_read[fd]);
	return (line);
}

char	*ft_read(int fd, char *old_read)
{
	char	*buffer;
	int		read_bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!(ft_strchr(old_read, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		old_read = ft_strjoin(old_read, buffer);
	}
	free(buffer);
	return (old_read);
}

char	*ft_line(char	*old_read)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	if (!old_read[i])
		return (NULL);
	while (old_read[i] != '\0' && old_read[i] != '\n')
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 2));
	if (!temp)
		return (NULL);
	j = 0;
	while (j < i)
	{
		temp[j] = old_read[j];
		j++;
	}
	if (old_read[j] == '\n')
	{
		temp[j] = '\n';
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

char	*ft_reread(char	 *old_read)
{
	char	*read_update;
	int		i;
	int		j;

	i = 0;
	while (old_read[i] != '\0' && old_read[i] != '\n')
		i++;
	if (!old_read[i])
	{
		free(old_read);
		return (NULL);
	}
	read_update = (char *)malloc(sizeof(char) * ft_strlen(old_read) - i + 1);
	if (!read_update)
		return (NULL);
	i++;
	j = 0;
	while (old_read[i + j])
	{
		read_update[j] = old_read[j + i];
		j++;
	}
	read_update[j] = '\0';
	free(old_read);
	return (read_update);
}
