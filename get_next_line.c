/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:49:31 by alorain           #+#    #+#             */
/*   Updated: 2021/11/30 12:55:47 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static size_t	sub_len(char *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[start + i])
		i++;
	if (i < len)
		return (i);
	return (len);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (sub_len(s, start, len) + 1));
	if (!str)
		return (NULL);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*parse(char **excess)
{
	char	*line;
	char	*temp;
	size_t	line_len;
	size_t	excess_len;

	excess_len = 0;
	line_len = 0;
	while ((*excess)[line_len] && (*excess)[line_len] != '\n')
		line_len++;
	if ((*excess)[line_len] == '\n')
		line_len++;
	line = ft_substr(*excess, 0, line_len);
	excess_len = ft_strlen((*excess));
	temp = *excess;
	*excess = ft_substr(*excess, line_len, excess_len - line_len);
	free(temp);
	return (line);
}

char	*read_file(int fd, char **excess)
{
	ssize_t		bytes_read;
	char		*buffer;
	char		*line;
	char		*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	while (bytes_read && !ft_isin(*excess, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = *excess;
		*excess = ft_strjoin(*excess, buffer);
		free(temp);
	}
	free(buffer);
	line = parse(excess);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*excess = NULL;

	if (fd == -1 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!excess)
	{
		excess = malloc(sizeof(char));
		excess[0] = '\0';
	}
	line = read_file(fd, &excess);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
