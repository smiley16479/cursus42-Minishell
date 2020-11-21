/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:51 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/19 20:46:46 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"


/*
**free tous les pointeurs d'un array, puis cet array
*/

int		ft_free_split(char **commands)
{
	int i;

	i = 0;
	if (commands && *commands)
		while (commands[i])
			free(commands[i++]);
	if (commands)
		free(commands);
	return (0);
}

/*
**renvoie la taille d'un vecteur
*/

int		ft_strlen_vec(char **vec)
{
	int i;

	i = 0;
	if (vec && *vec)
		while (vec[i])
			i++;
	return (i);
}

/*
** Affiche un vecteur (char **) sur stdout
*/

void	print_2d_vec(char **vec)
{
	while (*vec)
		ft_printf("%s\n", *vec++);
}