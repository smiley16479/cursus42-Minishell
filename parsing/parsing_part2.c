/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 03:56:24 by user42            #+#    #+#             */
/*   Updated: 2020/11/21 18:54:48 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/* 
** deprecated
*/

int		is_permited_char(int c)
{
	if (((c >= ' ' && c <= '~') || (c >= '\a' && c <= '\r'))
		&& c != '$' && c != '"' && c != '\\' && c != '`')
		return (1);
	return (0);
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
	while (tmp[j] && tmp[j] != ' ' && tmp[j] != '"' && tmp[j] != '$'
			&& tmp[j] != '=' && tmp[j] != '/' && tmp[j] != '\\')
		++j;
	tmp[j] = '\0';
	if (get_variable(cmd, tmp, i, j))
		while (j--)
			ft_get_rid(cmd, *i);
	if (**cmd == '\0')
		return (get_rid_cmd_bis(cmd, 0, 0), 1);
	return (0);
}

/* 
**	Analyse les quote simple ($, ", ` et \ perdent leur sens spécial)
**	seul le "'" suivant est à détecter
*/

void	process_simple_quote(char **cmd, int *i)
{
	bool trigger;

	ft_get_rid(cmd, *i);
	trigger = 1;
	while ((*cmd)[*i] && trigger)
		(*cmd)[*i] == '\'' ? ft_get_rid(cmd, *i), (trigger = 0) : ++*i;
}

/* 
**	Analyse les double quote tous les charactères sauf $, ", ` et \ 
**	perdent leur sens spécial
*/

int		process_db_quote(char **cmd, int *i)
{
	bool trigger;

	ft_get_rid(cmd, *i);
	trigger = 1;
	while ((*cmd) && (*cmd)[*i] && (*cmd)[*i] != '\"' && trigger)
	{
		(*cmd)[*i] == '\\' && ((*cmd)[*i + 1] == '$' ||
		(*cmd)[*i + 1] == '\\' || (*cmd)[*i + 1] == '`' ||
		(*cmd)[*i + 1] == '\"') ? ft_get_rid(cmd, (*i)++) : 0;
		(*cmd)[*i] == '\\' ? ++*i : 0;
		if ((*cmd)[*i] == '$' && (*cmd)[*i + 1] && get_allias(cmd, i))
			return (1);
		while ((*cmd) && (((*cmd)[*i] >= ' ' && (*cmd)[*i] <= '~')
			|| ((*cmd)[*i] >= '\a' && (*cmd)[*i] <= '\r'))
			&& (*cmd)[*i] != '$' && (*cmd)[*i] != '"'
			&& (*cmd)[*i] != '\\' && (*cmd)[*i] != '`')
			++*i;
		(*cmd) && (*cmd)[*i] == '\"' ? ft_get_rid(cmd, *i), (trigger = 0) : 0;
	}
	return (0);
}

/* 
** Analyse la cmd à l'intérieur et à l'exterieur des quotes
** créer les expansions des $VAR, enlève les quotes (',"), les échapements \, etc..
*/

void parse_cmd(char **cmd)
{
	int i;

	while (*cmd && !(i = 0))
	{
		while ((*cmd)[i])
			if ((*cmd)[i] == '\'')
				process_simple_quote(cmd, &i);
			else if ((*cmd)[i] == '\"')
			{
				if (process_db_quote(cmd, &i) && --cmd)
					break ;
			}
			else if ((*cmd)[i] == '$' && (*cmd)[i + 1])
			{
				if (get_allias(cmd, &i) && --cmd)
					break ;
			}
			else if ((*cmd)[i] == '\\')
				ft_get_rid(cmd, i++); 
			else
				++i;
		++cmd;		
	}
}