/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:32:26 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/10 22:08:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
** remplace les alias au sein des ""
** "$MT_PROGRAMM" => "minishell"
*/

int		double_quote(char **command, int *k)
{
	int i;

	i = *k;
	ft_get_rid(command, i--);
	while ((*command)[++i] && (*command)[i] != '\"')
	{
		if ((*command)[i] == '\\' && ((*command)[i + 1] == '\"' ||
		(*command)[i + 1] == '\\' || (*command)[i + 1] == '$' ||
		(*command)[i + 1] == '~' || (*command)[i + 1] == '\n'))
			ft_get_rid(command, i);
		if ((*command)[i] == '$' && (*command)[i + 1] != 0 &&
		(*command)[i + 1] != '\"' && (*command)[i + 1] != '$' &&
		(*command)[i + 1] != '\'')
			handle_alias(command, i--);
	}
	if ((*command)[i] == '\"')
		ft_get_rid(command, i);
	*k = i;
	return (0);
}

/*
**Transforme le nom des alias
**Par exemple, "MY-PROGRAM"
**devient minishell
*/

char	*alias_envv(char *command)
{
	int		i;
	char	*dest;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(command);
	if (tmp[0] == '?')
	{
		dest = ft_itoa(g_status >> 8);
		tmp[i++] = '\0';
	}
	else
	{
		while (tmp[i] && tmp[i] != '\'' && tmp[i] != '\\' &&
		tmp[i] != '\"' && tmp[i] != '$' && tmp[i] != '=')
			i++;
		tmp[i] = '\0';
		dest = find_key(tmp);
	}
	free(tmp);
	tmp = ft_strjoin(dest, &command[i]);
	free(dest);
	dest = tmp;
	return (dest);
}

/*
** My program is named $MY_PROGRAM
** => My program is named minishell
*/

void	handle_alias(char **command, int i)
{
	char *new;
	char *tmp;

	new = alias_envv(*command + i + 1);
	(*command)[i] = '\0';
	tmp = ft_strjoin(*command, new);
	free(new);
	free(*command);
	*command = tmp;
}

/*
** détecte les guillemets et renvoie aux fonctions ci-dessus
*/

char	*set_alias(char *command)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(command))
	{
		if ((command)[i] == '$' && (command[i + 1] != 0))
			handle_alias(&command, i);
		else if (command[i] == '\\')
			ft_get_rid(&command, i++);
		else if (command[i] == '\"')
			double_quote(&command, &i);
		else if (command[i] == '\'')
		{
			ft_get_rid(&command, i);
			while (command[i] && command[i] != '\'')
				i++;
			if (command[i] == '\'')
				ft_get_rid(&command, i);
		}
		else
			i++;
	}
	return (command);
}
