/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:31:04 by aschwere          #+#    #+#             */
/*   Updated: 2020/11/23 17:17:10 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
extern int g_cant_quit;

char	*readline(char *str, int fd)
{
	char	buff[BUFFER_SIZE + 1];
	ssize_t bytes_read;
	char	*tmp;

	bytes_read = read(fd, buff, BUFFER_SIZE);
	buff[bytes_read] = '\0';
	g_cant_quit = 1;
	while (!(isin('\n', buff, bytes_read)) && g_cant_quit && ft_strlen(buff))
	{
		if ((g_cant_quit = 1) && bytes_read)
		{
			buff[bytes_read] = '\0';
			tmp = str;
			str = ft_strjoin(str, buff);
			free(tmp);
		}
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (!g_cant_quit)
			str[0] = '\0';
	}
	buff[bytes_read] = '\0';
	tmp = str;
	str = ft_strjoin(str, buff);
	free(tmp);
	return (str);
}

int		isin(char c, const char *s, int len)
{
	int i;

	i = 0;
	while (s[i] && i < len)
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_advance(char **str, int i)
{
	char *tmp;

	tmp = *str;
	*str = ft_substr(*str, i, ft_strlen(*str) - i);
	free(tmp);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[10];
	int			i;
	int			res;
	char		*buff[BUFFER_SIZE];

	if (fd < 0 || BUFFER_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!str[fd])
		str[fd] = ft_strdup("");
	str[fd] = readline(str[fd], fd);
	if (str[fd][(i = 0)])
	{
		while ((str[fd][i]) && (str[fd][i] != '\n'))
			i++;
		res = (str[fd][i] == '\n') ? 1 : 0;
		if (i == 0)
			*line = ft_strdup("");
		else
			(*line) = ft_substr(str[fd], 0, i);
		ft_advance(&str[fd], i + 1);
		return (res);
	}
	(*line) = ft_strdup("");
	return (0);
}
