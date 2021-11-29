/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:23:22 by alorain           #+#    #+#             */
/*   Updated: 2021/11/29 22:23:24 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char    *ft_strjoin(char *s1, char *s2)
{
        size_t  len;
        size_t  i;
        size_t  j;
        char    *str;

        if (!s1)
                return (NULL);
        len = ft_strlen(s1) + ft_strlen(s2);
        i = 0;
        j = 0;
        str = malloc(sizeof(char) * (len + 1));
        if (!str)
                return (NULL);
        while (s1[i])
        {
                str[i] = s1[i];
                i++;
        }
        while (s2[j])
        {
                str[j + i] = s2[j];
                j++;
        }
        str[i + j] = '\0';
        return (str);
}

static size_t   sub_len(char *s, unsigned int start, size_t len)
{
        size_t  i;

        i = 0;
        while (s[start + i])
                i++;
        if (i < len)
                return (i);
        return (len);
}

char    *ft_substr(char *s, unsigned int start, size_t len)
{
        size_t  i;
        char    *str;

        if (!s)
                return (NULL);
        i = 0;
        if (start >= ft_strlen(s))
        {
                str = malloc(sizeof(char) * 1);
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

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

char	*parse(char	**excess)
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

char	*read_file(int fd)
{
	ssize_t		bytes_read;
	char		*buffer;
	char		*line;
	char		*temp;
	static char	*excess = NULL;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!excess)
	{
		excess = malloc(sizeof(char));
		excess[0] = '\0';
	}
	bytes_read = BUFFER_SIZE;	
	while(bytes_read && !ft_isin(excess, '\n'))
	{
		bytes_read = read(fd, buffer,BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		temp = excess;
		excess = ft_strjoin(excess, buffer);
		free(temp);
	}
	free(buffer);
	line = parse(&excess);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	
	line = read_file(fd);
	return (line);
}

/* int main()
{
	int	fd;

	fd = open("./test_get_next_line.txt", O_RDONLY);
	if (fd < 0)
		return(0);
	for (int i = 0; i < 6; i++)
	{
		char *str = get_next_line(fd);
		if (!str)
		{
			printf("error");
			return (0);
		}	
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);	
} */