/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 11:16:19 by alorain           #+#    #+#             */
/*   Updated: 2021/11/29 21:59:22 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
char	*get_next_line(int fd);
	/* get_next_line_utils.c */


size_t	ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*concat(char *s1, char *s2);
int		ft_isin(char *str, char c);
char	*ft_dupton(char *str);
size_t	optilen(char *str);
int		actualise(char **excess, char *str_read, char *line);


#endif
