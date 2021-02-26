/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:51 by alexandre         #+#    #+#             */
/*   Updated: 2021/02/25 20:46:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
**free tous les pointeurs d'un array, puis cet array
*/

int		ft_free_split(char **commands)
{
	int i;

	i = 0;
	if (commands && *commands)
		while (commands[i])
			free(commands[i++]);
	if (commands)
		free(commands);
	return (0);
}

/*
**renvoie la taille d'un vecteur
*/

int		ft_strlen_vec(char **vec)
{
	int i;

	i = 0;
	if (vec && *vec)
		while (vec[i])
			i++;
	return (i);
}

/*
** Indique les pos des chaines à détruire selon [beg - end] (inclus)
*/

int		get_rid_cmd(char **cmd, int beg, int end)
{
	int i;

	i = -1;
	while (++i + beg <= end)
		free(cmd[beg + i]);
	while (cmd[end])
		cmd[beg++] = cmd[++end];
	cmd[beg] = NULL;
	return (1);
}

/*
** Ajoute de(s) chaine(s) à la position (pos) ds un vecteur[**char]
*/

void	ft_add_vec_to_another(int *pos,
		char **to_add, char ***cmd, int join)
{
	char	*tmp;

	if (ft_isspace(to_add[ft_strlen_vec(to_add) - 1]
	[ft_strlen(to_add[ft_strlen_vec(to_add) - 1]) - 1]))
		write(1, "il y a de l'espace\n", 19);
	if (join == 1)
	{
		tmp = ft_strjoin((*cmd)[*pos], *to_add);
		get_rid_cmd(*cmd, *pos, *pos);
		free(*to_add++);
		ft_add_cmd(*pos, tmp, cmd);
	}
	while (*to_add)
		ft_add_cmd((*pos)++, *to_add++, cmd);
	if (join == 2)
	{
		tmp = ft_strjoin((*cmd)[*pos - 1], (*cmd)[*pos]);
		get_rid_cmd(*cmd, *pos - 1, *pos);
		ft_add_cmd(--*pos, tmp, cmd);
	}
}

/*
** Ajoute une chaine à la position (pos) ds un vecteur[**char]
*/

void	ft_add_cmd(int pos, char *to_add, char ***cmd)
{
	int		i;
	int		j;
	char	**tmp;

	if (!(tmp = malloc(sizeof(tmp) * (ft_strlen_vec(*cmd) + 2))))
		exit(-1);
	j = 0;
	i = -1;
	while ((*cmd)[++i])
	{
		if (i == pos)
			tmp[i + j++] = to_add;
		tmp[i + j] = (*cmd)[i];
	}
	if (i == pos)
		tmp[i + j++] = to_add;
	tmp[i + j] = NULL;
	free(*cmd);
	*cmd = tmp;
}
