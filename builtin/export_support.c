/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:31:51 by user42            #+#    #+#             */
/*   Updated: 2020/11/20 19:19:16 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	ft_swap_db_char_ptr(char **ptr1, char **ptr2)
{
	char *tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

/* 
** Imprime la variable à la façon d'export
*/

void	write_export_msg_sub1(char *str)
{
	write(1, "declare -x ", 11);
	while (*str != '=' && *str)
		write(1, str++, 1);
	if (*str)
	{
		write(1, str++, 1);
		write(1, "\"", 1);
		while (*str)
			write(1, str++, 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

/*
** Print l'env en fonction de trie 1/0 -> export/env
** env ne print la variable que si elle a à minima été déclarée
** avec un '=' (ex:'a=')
*/

void	write_export_msg(char *str, int trie)
{
	int i;

	if (!(i = 0) && trie)
	{
		if (!(*str == '_' && *(str + 1) == '='))
			write_export_msg_sub1(str);
	}
	else
		while (str[i])
			if (str[i++] == '=')
			{
				write(1, str, ft_strlen(str));
				write(1, "\n", 1);
				break ;
			}
}
