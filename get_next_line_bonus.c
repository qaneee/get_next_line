/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:54:09 by arvardan          #+#    #+#             */
/*   Updated: 2025/09/23 21:18:05 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*join_buffer_b(char *buffer, char *temp)
{
	char	*new_buffer;

	if (!buffer)
		return (ft_strdup_b(temp));
	new_buffer = ft_strjoin_b(buffer, temp);
	free(buffer);
	return (new_buffer);
}

static char	*read_file_b(int fd, char *buffer)
{
	char	*temp;
	ssize_t	count;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (free(buffer), NULL);
	count = read(fd, temp, BUFFER_SIZE);
	while (count > 0)
	{
		temp[count] = '\0';
		buffer = join_buffer_b(buffer, temp);
		if (!buffer)
			return (free(temp), NULL);
		if (!buffer || ft_strchr_b(buffer, '\n'))
			break ;
		count = read(fd, temp, BUFFER_SIZE);
	}
	free(temp);
	if (count < 0)
		return (free(buffer), NULL);
	return (buffer);
}

static char	*get_line_b(char *s)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!s || !s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		line = malloc(i + 1);
	else
		line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*free_s_b(char *s)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	if (!s[i++])
		return (free(s), NULL);
	new = malloc(ft_strlen_b(s) - i + 1);
	if (!new)
		return (free(s), NULL);
	j = 0;
	while (s[i])
		new[j++] = s[i++];
	new[j] = '\0';
	return (free(s), new);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	buffer[fd] = read_file_b(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	if (buffer[fd] && !ft_strchr_b(buffer[fd], '\n'))
	{
		line = get_line_b(buffer[fd]);
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (line);
	}
	line = get_line_b(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = free_s_b(buffer[fd]);
	return (line);
}
