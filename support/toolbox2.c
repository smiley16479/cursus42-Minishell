/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:51 by alexandre         #+#    #+#             */
/*   Updated: 2021/02/04 21:20:50 by adtheus          ###   ########.fr       */
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

	// for (int i = 0; cmd[i]; ++i)
	// 	printf("ds get_rid{%s}\n", cmd[i]);
	// printf("ds get_rid{%s}\n", cmd[beg]);
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

void		ft_add_vec_to_another(int *pos, char **to_add, char ***cmd, int join)
{
	char *tmp;
	// printf("ds ft_add_vec_to_another pos:%d\n", *pos);
	if (ft_isspace(to_add[ft_strlen_vec(to_add) - 1][ft_strlen(to_add[ft_strlen_vec(to_add) - 1]) - 1]))
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
	// for (int i = 0; (*cmd)[i]; ++i) // les quotes sont misent ds le désordres
	// 	printf("ds ft_add_vec_to_another cmd[%d]:'%s'\n", i, (*cmd)[i]);
}

/*
** Ajoute une chaine à la position (pos) ds un vecteur[**char]
*/

void	ft_add_cmd(int pos, char *to_add, char ***cmd)
{
	int	 i;
	int	 j;
	char **tmp;
	// printf("ds ft_add_cmd pos:%d\n", pos);

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
	// for (int i = 0; (*cmd)[i]; ++i)
	// 	printf("ds ft_add_cmd[%d]:'%s'\n", i, (*cmd)[i]);
}

/*
**	Return respectivement 1, 2 ,3 ou 4 pour >, >>, < ou | sinon return (0)
*/

t_bool	which_redir(char *str)
{
	if (!(str))
		return (0);
	else if (!ft_strcmp(str, ">"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (2);
	else if (!ft_strcmp(str, "<"))
		return (3);
	else if (!ft_strcmp(str, "|"))
		return (4);
	return (0);
}
