/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:53:44 by user42            #+#    #+#             */
/*   Updated: 2021/02/25 20:43:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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

/*
**Copie i caractères à partir du prev-ième caractère de line dans dest
*/

char	*copy_word(char *line, int prev, int i)
{
	char	*dest;

	if (prev == i)
		return (NULL);
	dest = malloc(i - prev + 1);
	ft_strlcpy(dest, line + prev, i - prev + 1);
	return (dest);
}

void	set_valid_chevron(t_parse **ls, char **split_db)
{
	int len;

	if ((len = ft_strlen_vec(split_db)) == 0 || len > 1)
		if ((*ls) &&
		(!ft_strcmp((*ls)->cont, ">") ||
		!ft_strcmp((*ls)->cont, ">>") ||
		!ft_strcmp((*ls)->cont, "<")) &&
		((*ls)->typ & 0x0F) == 0)
			(*ls)->prev->typ += BAD_CHEV;
}
