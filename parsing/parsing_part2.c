/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 03:56:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/25 20:08:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
**	Analyse les quote simple ($, ", ` et \ perdent leur sens spécial)
**	seul le "'" suivant est à détecter
*/

void		process_simple_quote(char **cmd, int *i, t_parse **parse)
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
	if ((*cmd)[*i])
		typ |= STICKY_A;
	if (tmp != *i)
		*parse = t_parse_add(typ, ft_substr(*cmd, tmp, *i - tmp), *parse);
	else
		*parse = t_parse_add(typ, ft_strdup(""), *parse);
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

	tmp = *i;
	ft_get_rid(cmd, *i);
	trigger = 1;
	while ((*cmd) && (*cmd)[*i] && trigger)
	{
		if ((*cmd)[*i] == '\\' && check_set((*cmd)[*i + 1], "$\\\"`"))
			ft_get_rid(cmd, (*i)++);
		(*cmd)[*i] == '\\' ? ++*i : 0;
		if ((*cmd)[*i] == '$')
			get_allias(cmd, i);
		while ((*cmd) && (((*cmd)[*i] >= ' ' && (*cmd)[*i] <= '~') ||
		((*cmd)[*i] >= '\a' && (*cmd)[*i] <= '\r')) &&
		!check_set((*cmd)[*i], "$\\\"`"))
			++*i;
		if ((*cmd)[*i] == '\"' && !(trigger = 0))
			ft_get_rid(cmd, *i);
	}
	typ = (*cmd)[*i] ? (STICKY_A + 2) : 2;
	*parse = (tmp != *i) ? t_parse_add(typ, ft_substr(*cmd, tmp, *i - tmp),
	*parse) : t_parse_add(typ, ft_strdup(""), *parse);
}

/*
** Analyse la cmd à l'intérieur et à l'exterieur des quotes
** créer les expansions des $VAR, enlève les quotes (',"),
** les échapements \, etc..
*/

t_parse		*parse_cmd(char **cmd)
{
	int		i;
	int		j;
	t_parse	*parse;

	parse = NULL;
	i = 0;
	while (cmd[i] && !(j = 0))
	{
		while (cmd[i][j])
			if (cmd[i][j] == '\'')
				process_simple_quote(&cmd[i], &j, &parse);
			else if (cmd[i][j] == '\"')
				process_db_quote(&cmd[i], &j, &parse);
			else if (ft_isprint(cmd[i][j]) && !check_set(cmd[i][j], "\'\"$"))
				get_str(&cmd[i], &j, &parse);
			else if (cmd[i][j] == '$'
				&& !check_set(cmd[i][j + 1], " \"\'"))
				get_allias_outside_quote_list(&cmd[i], &j, &parse);
			else
				++j;
		++i;
	}
	parse = t_parse_add(FINAL_END, NULL, parse);
	return (parse);
}
