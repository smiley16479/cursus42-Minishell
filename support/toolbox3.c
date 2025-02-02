/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 00:42:28 by adrien            #+#    #+#             */
/*   Updated: 2021/02/26 19:32:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int		is_token(char **cmdl)
{
	char	*token;
	int		i;

	token = ">>\0|\0\0>\0\0<\0\0;\0\0";
	i = 0;
	while (i < 14)
	{
		if (!strncmp(&token[i], *cmdl, strlen(&token[i])))
		{
			*cmdl += strlen(&token[i]);
			return (1);
		}
		i += 3;
	}
	return (0);
}

int		is_two_token(char **cmdl)
{
	int	trigger;

	trigger = 0;
	while (ft_isspace(**cmdl))
		++*cmdl;
	if (is_token(cmdl))
		++trigger;
	while (ft_isspace(**cmdl))
		++*cmdl;
	if ((is_token(cmdl) && trigger) || (**cmdl == '\0' && trigger))
		return (1);
	return (0);
}

int		skip_quote_n_text(char **cmdl, int *text)
{
	(void)text;
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
	int	text;

	text = 0;
	while (*cmdl)
	{
		if (skip_quote_n_text(&cmdl, &text) || is_two_token(&cmdl))
		{
			return ((g_status = (2 + ft_error("Bash",
			"Token", "bad syntaxt", STAY)) << 8));
		}
		if (*cmdl && *cmdl != '\'' && *cmdl != '\"')
			++cmdl;
	}
	return (0);
}

int		ft_error(char *proc, char *mess, char *command, int out)
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
