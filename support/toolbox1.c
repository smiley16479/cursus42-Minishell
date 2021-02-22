/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:41 by alexandre         #+#    #+#             */
/*   Updated: 2021/02/20 16:54:56 by adtheus          ###   ########.fr       */
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

/*
** Construit un char **tab depuis une list(->cont)
*/

/* char **construct_tab_from_ls(t_parse **ls)
{
	char	**cmd;
	int		i;

	cmd = malloc(sizeof(cmd) * (list_count(*ls) + 1));
	if (!cmd)
		return NULL;
	i = -1;
	while (*ls && (((*ls)->typ & CMDEND) != CMDEND))
	{
		cmd[++i] = (*ls)->cont;
		*ls = (*ls)->next;
	}
	if (*ls && (((*ls)->typ & CMDEND) == CMDEND))
		*ls = list_elem_remove(*ls);
	cmd[++i] = NULL;
	return (cmd);
}
 */


char **construct_tab_from_ls(t_parse **ls)
{
	char	**cmd;
	char	*tmp;
	int		i;

	// printf("ds contruct_tab\n");
	cmd = malloc(sizeof(cmd) * (list_count(*ls) + 1));
	if (!cmd)
		return NULL;
	i = -1;
	while (*ls && (((*ls)->typ & CMDEND) != CMDEND))
	{
		// printf("cont : %s, typ : %d\n", (*ls)->cont, (*ls)->typ);
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
	{
		// printf("cont : %s\n", (*ls)->cont);
		*ls = list_elem_remove(*ls);
	}
	cmd[++i] = NULL;
	return (cmd);
}

