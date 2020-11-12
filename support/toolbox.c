/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:41 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/08 23:28:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
**transfère le contenu d'un fd vers un autre
*/

int		file_transfer(int fds, int fdd)
{
	int		ret;
	char	buf[65];

	while ((ret = read(fds, buf, 64)) > 0)
	{
		buf[ret] = '\0';
		if (write(fdd, buf, ft_strlen(buf)) == -1)
			return (!ft_error("minishell",
			ft_strdup("<"), strerror(errno), STAY));
	}
	return (0);
}

/*
**renvoie str1+sep+str2
*/

char	*ft_strjoin_sep(char *str1, char *str2, char *sep)
{
	char *tmp;
	char *dest;

	tmp = ft_strjoin(str1, sep);
	dest = ft_strjoin(tmp, str2);
	free(tmp);
	free(str1);
	return (dest);
}

/*
**enlève un caractère d'une string
*/

void	ft_get_rid(char **src, int pos)
{
	char *dest;
	char *tmp;

	tmp = ft_strdup(*src + pos + 1);
	(*src)[pos] = '\0';
	dest = ft_strjoin(*src, tmp);
	free(*src);
	free(tmp);
	*src = dest;
}
