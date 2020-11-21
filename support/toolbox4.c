/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 00:42:28 by adrien            #+#    #+#             */
/*   Updated: 2020/11/21 22:05:14 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int is_token(int c)
{
	char *token = "|><;";

	while (*token)
		if (c == *token++)
			return (1);
	return (0);
}

/* 
** is_spaces_inbetween_token
*/

int	is_two_token(char **cmdl)
{
	if (is_token(**cmdl))
	{
		++*cmdl;
		if (**cmdl == '>')
			++*cmdl;
		while (ft_isspace(**cmdl))
			++*cmdl;
		if (is_token(**cmdl))
			return (1);
	}
	return (0);
}

int	skip_apostrophy(char **cmdl)
{
	if (**cmdl == '\"' || **cmdl == '\'')
	{
		if (**cmdl == '\"' && ++*cmdl)
			while (**cmdl && **cmdl != '\"')
				++*cmdl;
		if (**cmdl == '\'' && ++*cmdl)
			while (**cmdl && **cmdl != '\'')
				++*cmdl;
		if (**cmdl == '\'' || **cmdl == '\"')
		{
			++*cmdl;
			return (0);
		}
		else if (**cmdl == '\0')
			return (0);		
		return (1);
	}
	return (0);
}

int	verify_duplicate_token_in_cmdl(char *cmdl)
{
	while (*cmdl)
	{
		if (skip_apostrophy(&cmdl) || is_two_token(&cmdl))
			return ((g_status = 
			(2 + ft_error("Bash", "Token", "bad syntaxt", STAY)) << 8));
		if (*cmdl && *cmdl != '\'' && *cmdl != '\"')
			++cmdl;
	}
	return (0);
}

/*
** Affiche un vecteur (char ***) sur stdout
*/

void	print_3d_vec(char ***vec)
{
	int i;

	if (vec && *vec && **vec)
		while (*vec && (i = -1))
		{
			while ((*vec)[++i])
				ft_printf("%s\n", (*vec)[i]);
			++vec;
		}
}

void	destroy_3d_vec(char ***vec)
{
	int		i;
	char	***tmp;

	tmp = vec;
	if (vec && *vec && **vec)
		while (*vec && (i = -1))
		{
			while ((*vec)[++i])
				free((*vec)[i]);
			free(*vec++);
		}
	free(tmp);
}
