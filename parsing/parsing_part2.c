/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 03:56:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 11:18:29 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
** return **char pour une variable qui possède des espaces
** add : k est la taille de la variable
*/

char	**get_variable_outside_quote(char *tmp, int k)
{
	char	**db;
	char	**split_db;
	int		l;

	l = -1;
	while (g_envv[++l] && (db = ft_cut_export_var(g_envv[l], '=')))
		if (!ft_strncmp(db[0], tmp, k))
		{
			split_db = ft_split_unless_quote(db[1], " \t");
			ft_free_split(db);
			free(tmp);
			return (split_db);
		}
		else
			ft_free_split(db);
	free(tmp);
	return (NULL);
}

int		get_allias_outside_quote(char ***cmd, int *i, int *j)
{
	char	*tmp;
	char	**db_tmp;
	int		k;
	printf("ds get_alias_outside pos[%d][%d]\n", *i, *j);
	ft_get_rid(&(*cmd)[*i], *j);
	if ((*cmd)[*i][*j] == '?')
	{
		ft_get_rid(&(*cmd)[*i], *j);
		ft_add_inside(&(*cmd)[*i], (tmp = ft_itoa(g_status >> 8)), *j);
		free(tmp);
		return (0);
	}
	tmp = ft_strdup(&(*cmd)[*i][*j]);
	k = 0;
	while (tmp[k] && !check_set(tmp[k], " \"\'$=/\\"))
		++k;
	tmp[k] = '\0';
	if ((db_tmp = get_variable_outside_quote(tmp, k)))
	{
		while (k--)
			ft_get_rid(&(*cmd)[*i], *j);
		// if (*j)
		// 	ft_add_vec_to_another(i, db_tmp, cmd, 1);
		// (*cmd)[*i][*j] ? ft_add_vec_to_another(i, db_tmp, cmd, 0) :
		// ft_add_vec_to_another(i, db_tmp, cmd, 2);
		// for (int i = 0; (*cmd)[i]; ++i)
		// 	printf("ds get_alias_outside cmd[%d]:'%s'\n", i, (*cmd)[i]);
		
		free(db_tmp);
	}
	else
		while (k--)
			ft_get_rid(&(*cmd)[*i], *j);
	// printf("'%s'\n", *(cmd));
	// if (*(*cmd)[*i] == '\0')
	// 	return (get_rid_cmd(&(*cmd)[*i], 0, 0));
	return (1);
}

/*
** Insert la variable (tmp) dans la chaine (*cmd) à la position donnée (*i)
** add : j est la taille de la variable (on pourrait s'en passer)
*/

int		get_variable(char **cmd, char *tmp, int *i, int j)
{
	char	**db;
	int		k;

	k = -1;
	while (g_envv[++k] && (db = ft_cut_export_var(g_envv[k], '=')))
		if (!ft_strncmp(db[0], tmp, j))
		{
			while (j--)
				ft_get_rid(cmd, *i);
			ft_add_inside(cmd, db[1], *i);
			*i += ft_strlen(db[1]);
			ft_free_split(db);
			free(tmp);
			return (0);
		}
		else
			ft_free_split(db);
	free(tmp);
	return (1);
}

/*
**	Ajoute l'alias $MY_PROGRAM dans la chaine à la position du '$' => (i)
*/

int		get_allias(char **cmd, int *i)
{
	char	*tmp;
	int		j;

	ft_get_rid(cmd, *i);
	if ((*cmd)[*i] == '?')
	{
		ft_get_rid(cmd, *i);
		ft_add_inside(cmd, (tmp = ft_itoa(g_status >> 8)), *i);
		free(tmp);
		return (0);
	}
	tmp = ft_strdup(&(*cmd)[*i]);
	j = 0;
	while (tmp[j] && !check_set(tmp[j], " \"$=/\\"))
		++j;
	tmp[j] = '\0';
	if (get_variable(cmd, tmp, i, j))
		while (j--)
			ft_get_rid(cmd, *i);
	if (**cmd == '\0')
		return (get_rid_cmd(cmd, 0, 0));
	return (0);
}

/*
**	Analyse les quote simple ($, ", ` et \ perdent leur sens spécial)
**	seul le "'" suivant est à détecter
*/

void	process_simple_quote(char **cmd, int *i)
{
	t_bool trigger;

	ft_get_rid(cmd, *i);
	trigger = 1;
	while ((*cmd)[*i] && trigger)
		if ((*cmd)[*i] == '\'')
		{
			ft_get_rid(cmd, *i);
			trigger = 0;
		}
		else
			++*i;
}

/*
**	Analyse les double quote tous les charactères sauf $, ", ` et \
**	perdent leur sens spécial
*/

int		process_db_quote(char **cmd, int *i)
{
	t_bool trigger;

	ft_get_rid(cmd, *i);
	trigger = 1;
	while ((*cmd) && (*cmd)[*i] && (*cmd)[*i] != '\"' && trigger)
	{
		(*cmd)[*i] == '\\' && check_set((*cmd)[*i + 1], "$\\\"`") ?
		ft_get_rid(cmd, (*i)++) : 0;
		(*cmd)[*i] == '\\' ? ++*i : 0;
		if ((*cmd)[*i] == '$' && (*cmd)[*i + 1] && get_allias(cmd, i))
			return (1);
		while ((*cmd) && (((*cmd)[*i] >= ' ' && (*cmd)[*i] <= '~')
			|| ((*cmd)[*i] >= '\a' && (*cmd)[*i] <= '\r'))
			&& !check_set((*cmd)[*i], "$\\\"`"))
			++*i;
		if ((*cmd) && (*cmd)[*i] == '\"')
		{
			ft_get_rid(cmd, *i);
			trigger = 0;
		}
	}
	return (0);
}

/*
** Analyse la cmd à l'intérieur et à l'exterieur des quotes
** créer les expansions des $VAR, enlève les quotes (',"),
** les échapements \, etc..
*/

char 	**parse_cmd(char **cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd[i] && !(j = 0))
	{
		while (cmd[i][j])
			if (cmd[i][j] == '\'')
				process_simple_quote(&cmd[i], &j);
			else if (cmd[i][j] == '\"')
			{
				if (process_db_quote(&cmd[i], &j))
				{
					--i;
					break ;
				}	
			}
			else if (cmd[i][j] == '$' && cmd[i][j + 1]
				&& !check_set(cmd[i][j + 1], " \"\'"))
			{
				// printf("AVANT ds parse_cmd[%s]\n", *(cmd + i));
				// if (get_allias_outside_quote(&cmd, &i, &j))
				if (get_allias(&cmd[i], &j))
				{
					for (int i = 0; (*cmd)[i]; ++i)
						printf("ds parse_cmd cmd[%d]:'%s'\n", i, cmd[i]);
					// printf("APRES ds parse_cmd[%s]\n", *(cmd + i));
					// break ;
				}
			}
			else if (cmd[i][j] == '\\')
				ft_get_rid(&cmd[i], j++);
			else
				++j;
		++i;
	}
	return (cmd);
}
