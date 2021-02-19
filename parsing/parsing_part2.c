/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 03:56:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/19 17:33:46 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
** return **char pour une variable qui possède des espaces
** add : k est la taille de la variable
*/

void	get_variable_outside_quote_list(char *tmp, int k, t_parse **ls)
{
	char	**db;
	char	**split_db;
	int		l;
	int		m;

	l = -1;
	while (g_envv[++l] && (db = ft_cut_export_var(g_envv[l], '=')))
		if (!ft_strncmp(db[0], tmp, k))
		{
			split_db = ft_split_unless_quote(db[1], " \t");
			ft_free_split(db);
			free(tmp);
			m = -1;
			while (split_db[++m])
				*ls = t_parse_add(4, split_db[m], *ls);
			free(split_db);
			return ;
		}
		else
			ft_free_split(db);
	free(tmp);
}

int		get_allias_outside_quote_list(char **cmd, int *i, t_parse **ls)
{
	char	*tmp;
	int		k;

	if (!(*cmd)[*i + 1]) // si $ est isolé on le garde tel quel
		return (++*i, !(*ls = t_parse_add(4, ft_strdup(&(*cmd)[*i]), *ls)));
	ft_get_rid(cmd, *i);
	if ((*cmd)[*i] == '?')
	{
		ft_get_rid(cmd, *i);
		*ls = t_parse_add(4, ft_strdup((tmp = ft_itoa(g_status >> 8))), *ls);
		free(tmp);
		return (0);
	}
	tmp = ft_strdup(&(*cmd)[*i]);
	k = 0;
	while (tmp[k] && !check_set(tmp[k], " \"\'$=/\\"))
		++k;
	tmp[k] = '\0';
	*i += k;
	get_variable_outside_quote_list(tmp, k, ls);
	return (1);
}

/* 
** Get the string or a portion of it if text embed quote
*/

void	get_str(char **cmd, int *i, t_parse **parse)
{
	int tmp;
	int typ;

	tmp = *i;
	typ ^= typ;
	while (ft_isprint((*cmd)[*i]))
		if ((*cmd)[*i] == '\\')
		{
			ft_get_rid(cmd, *i);
			++*i;
		}
		else if (check_set((*cmd)[*i], "\'\"$")) //surement les mauvais char
			break ;
		else
			++*i;
	if ((*cmd)[*i]/*  && !check_set((*cmd)[*i], " \'\"\\$") */)
		typ |= STICKY_A; 
	*parse = t_parse_add(typ, ft_substr(*cmd, tmp, *i - tmp), *parse);
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

	if ((*cmd)[*i + 1]  && (*cmd)[*i + 1] == ' ')
		return (++*i);
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

void	process_simple_quote(char **cmd, int *i, t_parse **parse)
{
	int		tmp;
	t_bool	typ;
	t_bool	trigger;

	typ = 1;
	tmp = *i;
	ft_get_rid(cmd, *i);
	trigger = 1;
	while ((*cmd)[*i] && trigger)
		if ((*cmd)[*i] == '\'' && !(trigger = 0))
			ft_get_rid(cmd, *i);
		else
			++*i;
	if (*i > tmp && (*cmd)[*i])
		typ |= STICKY_A;
	if (tmp != *i)
		*parse = t_parse_add(typ, ft_substr(*cmd, tmp, *i - tmp), *parse);
}

/*
**	Analyse les double quote tous les charactères sauf $, ", ` et \
**	perdent leur sens spécial
*/

void		process_db_quote(char **cmd, int *i, t_parse **parse)
{
	int		tmp;
	t_bool	typ;
	t_bool	trigger;

	typ = 2;
	tmp = *i;
	ft_get_rid(cmd, *i);
	trigger = 1;
	while ((*cmd) && (*cmd)[*i] && (*cmd)[*i] != '\"' && trigger)
	{
		if ((*cmd)[*i] == '\\' && check_set((*cmd)[*i + 1], "$\\\"`"))
			ft_get_rid(cmd, (*i)++);
		(*cmd)[*i] == '\\' ? ++*i : 0;
		if ((*cmd)[*i] == '$'/*  && (*cmd)[*i + 1] && (*cmd)[*i + 1] != ' ' */)
			get_allias(cmd, i) ;
		while ((*cmd) && (((*cmd)[*i] >= ' ' && (*cmd)[*i] <= '~')
			|| ((*cmd)[*i] >= '\a' && (*cmd)[*i] <= '\r'))
			&& !check_set((*cmd)[*i], "$\\\"`"))
			++*i;
		if ((*cmd) && (*cmd)[*i] == '\"' && !(trigger = 0))
			ft_get_rid(cmd, *i);
	}
	if (*i > tmp && (*cmd)[*i])
		typ |= STICKY_A;
	if (tmp != *i)
		*parse = t_parse_add(typ, ft_substr(*cmd, tmp, *i - tmp), *parse);
}

/*
** Analyse la cmd à l'intérieur et à l'exterieur des quotes
** créer les expansions des $VAR, enlève les quotes (',"),
** les échapements \, etc..
*/

t_parse	*parse_cmd(char **cmd)
{
	int i;
	int j;
	t_parse *parse;

	parse = NULL;
	i = 0;
	// printf("%d\n", ft_strlen_vec(cmd));
	while (cmd[i] && !(j = 0))
	{
		while (cmd[i][j])
/* 			if (cmd[i][j] == '\\')
				ft_get_rid(&cmd[i], j++);
			else  */if (cmd[i][j] == '\'')
				process_simple_quote(&cmd[i], &j, &parse);
			else if (cmd[i][j] == '\"')
				process_db_quote(&cmd[i], &j, &parse);
			else if (ft_isprint(cmd[i][j]) && !check_set(cmd[i][j], "\'\"$")) //surement d'autre char à ajouter ?
				get_str(&cmd[i], &j, &parse);
			else if (cmd[i][j] == '$' /* && cmd[i][j + 1]
				&& !check_set(cmd[i][j + 1], " \"\'") */)
			{
				if (get_allias_outside_quote_list(&cmd[i], &j, &parse))
					for (int i = 0; cmd[i]; ++i)
						printf("ds parse_cmd cmd[%d]:'%s'\n", i, cmd[i]);
			}
			else
				++j;
		++i;
	}
	list_read(parse);
	return (parse);
}
