/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:57:28 by adtheus           #+#    #+#             */
/*   Updated: 2021/02/25 20:10:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_parse	*t_parse_add(char typ, char *cont, t_parse *prev)
{
	t_parse *to_return;

	to_return = malloc(sizeof(t_parse));
	if (!to_return)
		return (NULL);
	to_return->typ = typ;
	to_return->cont = cont;
	to_return->prev = prev;
	if (prev)
	{
		to_return->next = prev->next;
		if (prev->next)
			prev->next->prev = to_return;
	}
	else
		to_return->next = NULL;
	if (to_return->prev)
		to_return->prev->next = to_return;
	return (to_return);
}

/*
** retourne à la tête de la chaine
*/

void	list_rewind(t_parse **elem)
{
	if (*elem)
		while ((*elem)->prev)
			*elem = (*elem)->prev;
}

void	list_destroy(t_parse *to_destroy)
{
	t_parse *tmp;

	list_rewind(&to_destroy);
	while (to_destroy)
	{
		tmp = to_destroy;
		to_destroy = to_destroy->next;
		free(tmp->cont);
		free(tmp);
	}
}

t_parse	*list_elem_remove(t_parse *elem)
{
	t_parse *tmp;

	if (elem->prev)
	{
		tmp = elem->prev;
		elem->prev->next = elem->next;
	}
	else
	{
		if (elem->next)
			elem->next->prev = NULL;
	}
	if (elem->next)
	{
		tmp = elem->next;
		elem->next->prev = elem->prev;
	}
	else
	{
		if (elem->prev)
			elem->prev->next = NULL;
	}
	free(elem->cont);
	free(elem);
	return (tmp);
}

int		list_count(t_parse *to_count)
{
	int i;

	i = 0;
	while (to_count && ((to_count->typ & CMDEND) != CMDEND) && ++i)
		to_count = to_count->next;
	return (i);
}
