/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 00:42:28 by adrien            #+#    #+#             */
/*   Updated: 2021/02/04 14:56:33 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int		is_token(int c)
{
	char *token;

	token = "|><;";
	while (*token)
		if (c == *token++)
			return (1);
	return (0);
}

/*
** is_spaces_inbetween_token or only one token
*/

int		is_two_token(char **cmdl)
{
	if (is_token(**cmdl))
	{
		++*cmdl;
		if (**cmdl == '>')
			++*cmdl;
		while (ft_isspace(**cmdl))
			++*cmdl;
		if (is_token(**cmdl) || **cmdl == '\0')
			return (1);
	}
	return (0);
}

int		skip_apostrophy(char **cmdl)
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

int		verify_duplicate_token_in_cmdl(char *cmdl)
{
	while (*cmdl)
	{
		if (skip_apostrophy(&cmdl) || is_two_token(&cmdl))
		{
			return ((g_status = (2 + ft_error("Bash",
			"Token", "bad syntaxt", STAY)) << 8));
		}
		if (*cmdl && *cmdl != '\'' && *cmdl != '\"')
			++cmdl;
	}
	return (0);
}

int	ft_error(char *proc, char *mess, char *command, int out)
{
	write(2, "\e[0;31m", 7);
	write(2, proc, ft_strlen(proc));
	write(2, ": ", 2);
	write(2, mess, ft_strlen(mess));
	write(2, ": ", 2);
	write(2, command, ft_strlen(command));
	write(2, "\n", 1);
	write(2, "\e[0m", 4);
	if (out == EXIT)
	{
		free(command);
		ft_free_split(g_envv);
		exit(0);
	}
	return (0);
}
