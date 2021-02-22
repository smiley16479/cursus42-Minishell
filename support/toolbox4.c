/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:57:28 by adtheus           #+#    #+#             */
/*   Updated: 2021/02/20 19:38:49 by adtheus          ###   ########.fr       */
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

t_parse *list_elem_remove(t_parse *elem)
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

void	list_read(t_parse *to_read)
{
	list_rewind(&to_read);
	while (to_read)
	{
		printf("lst_read->typ ");
		if ((to_read->typ & STICKY_B) == STICKY_B)
			printf("STICKY_B ");
		if ((to_read->typ & STICKY_A) == STICKY_A)
			printf("STICKY_A ");
		if ((to_read->typ & SPQUOTE) == SPQUOTE)
			printf("SPQUOTE ");
		if ((to_read->typ & DBQUOTE) == DBQUOTE)
			printf("DBQUOTE ");
		if ((to_read->typ & CMDEND) == CMDEND)
			printf("CMDEND ");
		printf(", cont : %s\n" , to_read->cont);
		to_read = to_read->next;
	}
}

/* 
** Cherche si un des charactères de première chaine est ds l'autre
*/

int		ft_chr_char_of_str1_in_str2(char *str1, char *str2)
{
	int i;

	while (*str2 && !(i = 0))
	{
		while (str1[i])
		{
			if (str1[i] == *str2)
				return (1);
			++i;
		}
		++str2;
	}
	return (0);
}