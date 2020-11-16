/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:51 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/11 23:15:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int		has_redir(char **command, int pos)
{
	int i;

	i = -1;
	while (++i < pos && command[i])
	{
		if (!(ft_strcmp(command[i], ">")) || !(ft_strcmp(command[i], ">>")) ||
		!(ft_strcmp(command[i], "<")) || !(ft_strcmp(command[i], "|")))
			return (1);
	}
	return (0);
}

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
**renvoie toutes les commandes avant ou après i
**set_new_commands(echo "hey jude" > text.txt, 4, BEFORE) = echo "hey jude"
*/

char	**set_new_commands(char **commands, int i, int pos)
{
	int		j;
	char	**dest;
	int		k;

	k = (pos == AFTER) ? (i + 1) : 0;
	if (pos == BEFORE)
		if (!(dest = malloc((i + 1) * sizeof(char*))))
			ft_error("minishell", strerror(errno), ft_strdup(""), EXIT);
	if (pos == AFTER)
		if (!(dest = malloc((ft_strlen_vec(commands) - i) * sizeof(char*))))
			ft_error("minishell", strerror(errno), ft_strdup(""), EXIT);
	if (pos == BEFORE)
		j = 0;
	else
		j = i + 1;
	while ((pos == AFTER && (commands[j])) || j < i)
	{
		dest[j - k] = ft_strdup(commands[j]);
		j++;
	}
	dest[j - k] = NULL;
	ft_free_split(commands);
	return (dest);
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