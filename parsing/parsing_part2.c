/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 03:56:24 by user42            #+#    #+#             */
/*   Updated: 2020/11/14 05:47:22 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int		is_permited_char(int c)
{
	if (((c >= ' ' && c <= '~') || (c >= '\a' && c <= '\r'))
		&& c != '$' && c != '"' && c != '\\' && c != '`')
		return (1);
	return (0);
}

/* 
**	Ajoute l'alias $MY_PROGRAM dans la chaine à la position du '$' => (i)
*/

void	get_allias(char **cmd, int *i)
{
	int		j;
	char	**db;

	ft_get_rid(cmd, *i);
	j = -1;
	while (g_envv[++j] && (db = ft_split(g_envv[j], '=')))
		if (!ft_strncmp(db[0], &(*cmd)[*i], ft_strlen(db[0])))
		{
			j = ft_strlen(db[0]);
			while (j--)
				ft_get_rid(cmd, *i);
			ft_add_inside(cmd, db[1], *i);
			*i += ft_strlen(db[1]);
			ft_free_split(db);
			break ;
		}
		else
			ft_free_split(db);
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

void	process_db_quote(char **cmd, int *i)
{
	bool trigger;

	ft_get_rid(cmd, *i);
	trigger = 1;
	while ((*cmd)[*i] && (*cmd)[*i] != '\"' && trigger)
	{
		(*cmd)[*i] == '\\' && ((*cmd)[*i + 1] == '$' ||
		(*cmd)[*i + 1] == '\\' || (*cmd)[*i + 1] == '`' ||
		(*cmd)[*i + 1] == '\"') ? ft_get_rid(cmd, (*i)++) : 0;
		(*cmd)[*i] == '\\' ? ++*i : 0;
		(*cmd)[*i] == '$' ? get_allias(cmd, i) : 0;
		while (is_permited_char((*cmd)[*i]))
			++*i;
		(*cmd)[*i] == '\"' ? ft_get_rid(cmd, *i), (trigger = 0) : 0;
	}
}

/* 
** Analyse la cmd à l'intérieur et à l'exterieur des quotes
** créer les expansions des $VAR, enlève les quotes (',"), les échapements \, etc..
*/

void process_quote(char **cmd)
{
	int i;

	while (*cmd && !(i = 0))
	{
		while ((*cmd)[i])
		{
			if ((*cmd)[i] == '\'')
				process_simple_quote(cmd, &i);
			else if ((*cmd)[i] == '\"')
				process_db_quote(cmd, &i);
			else if ((*cmd)[i] == '$')
				get_allias(cmd, &i);
			else if ((*cmd)[i] == '\\')
				ft_get_rid(cmd, i++); 
			else
				++i;
		}
		++cmd;		
	}
}