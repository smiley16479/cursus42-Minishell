/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:38:10 by adtheus           #+#    #+#             */
/*   Updated: 2021/02/25 21:01:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
** return **char pour une variable qui possède des espaces
** add : k est la taille de la variable
*/

void	get_variable_outside_quote_list(char typ,
		char *tmp, int k, t_parse **ls)
{
	char	**db;
	char	**split_db;
	int		l;
	int		m;

	l = -1;
	split_db = NULL;
	while (g_envv[++l] && (db = ft_cut_export_var(g_envv[l], '=')))
		if (!ft_strncmp(db[0], tmp, k))
		{
			split_db = ft_split_unless_quote(db[1], " \t");
			ft_free_split(db);
			free(tmp);
			m = -1;
			set_valid_chevron(ls, split_db);
			while (split_db[++m])
				*ls = t_parse_add(VAR_TYP, split_db[m], *ls);
			(*ls)->typ += typ;
			free(split_db);
			return ;
		}
		else
			ft_free_split(db);
	set_valid_chevron(ls, split_db);
	free(tmp);
}

int		get_allias_outside_quote_list(char **cmd, int *i, t_parse **ls)
{
	char	*tmp;
	char	typ;
	int		k;

	if (!(*cmd)[*i + 1] && ++*i)
		return (!(*ls = t_parse_add(0, ft_strdup(&(*cmd)[*i - 1]), *ls)));
	ft_get_rid(cmd, *i);
	if ((*cmd)[*i] == '?')
	{
		ft_get_rid(cmd, *i);
		*ls = t_parse_add(VAR_TYP,
		ft_strdup((tmp = ft_itoa(g_status >> 8))), *ls);
		free(tmp);
		return (0);
	}
	tmp = ft_strdup(&(*cmd)[*i]);
	k = 0;
	while (tmp[k] && !check_set(tmp[k], " \"\'$=/\\"))
		++k;
	tmp[k] = '\0';
	*i += k;
	typ = ((*cmd)[*i] && (*cmd)[*i] != ' ') ? STICKY_A : 0;
	get_variable_outside_quote_list(typ, tmp, k, ls);
	return (0);
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
		else if (check_set((*cmd)[*i], "\'\"$"))
			break ;
		else
			++*i;
	if ((*cmd)[*i])
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

	if ((*cmd)[*i + 1] && (*cmd)[*i + 1] == ' ')
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
