/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:41 by alexandre         #+#    #+#             */
/*   Updated: 2021/02/25 20:18:49 by user42           ###   ########.fr       */
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

char	*ft_strjoin_sep(char *str1, char *sep, char *str2)
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

/*
** Ajoute une chaine à l'intérieur d'une autre, à la position voulu
*/

void	ft_add_inside(char **dest, char *sep, int pos)
{
	int		i;
	char	*tmp;

	if (!(tmp = malloc(ft_strlen(*dest) + ft_strlen(sep) + 1)))
		return ;
	i = -1;
	while (++i < pos)
		tmp[i] = (*dest)[i];
	while (*sep)
		tmp[i++] = *sep++;
	while ((*dest)[pos])
		tmp[i++] = (*dest)[pos++];
	tmp[i] = '\0';
	free(*dest);
	*dest = tmp;
}

char	**construct_tab_from_ls(t_parse **ls, int i)
{
	char	**cmd;
	char	*tmp;

	cmd = malloc(sizeof(cmd) * (list_count(*ls) + 1));
	if (!cmd)
		return (NULL);
	while (*ls && !((*ls)->typ & CMDEND) && !((*ls)->typ & FINAL_END))
	{
		if ((*ls)->prev && (((*ls)->prev->typ & STICKY_A) == STICKY_A))
		{
			tmp = cmd[i];
			cmd[i] = ft_strjoin(cmd[i], (*ls)->cont);
			free(tmp);
			*ls = (*ls)->next;
		}
		else
		{
			cmd[++i] = ft_strdup((*ls)->cont);
			*ls = (*ls)->next;
		}
	}
	if (*ls && (((*ls)->typ & CMDEND) == CMDEND))
		*ls = list_elem_remove(*ls);
	cmd[++i] = NULL;
	return (cmd);
}
