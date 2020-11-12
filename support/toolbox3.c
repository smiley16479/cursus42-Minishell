/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:51 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/08 21:49:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	get_rid_cmd(char ***cmd, int beg, int end)
{
	char	**dest;
	int		i;
	int		j;

	if (!(dest = malloc(sizeof(char*) * (ft_strlen_vec(*cmd) - (end - beg)))))
		ft_error("minishell", strerror(errno), ft_strdup(""), EXIT);
	i = -1;
	j = -1;
	while ((*cmd)[++i])
		if (i < beg || i > end)
			dest[++j] = ft_strdup((*cmd)[i]);
	dest[++j] = NULL;
	free(*cmd);
	*cmd = dest;
	return (0);
}

/* 
**	S'il s'agit d'un chevron return (1)
**	S'il s'agit d'un pipe	 return (2)
*/

int	is_redir(char *str)
{
	if (!(str))
		return (0);
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") ||
	!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "|"))
		return (2);
	return (0);
}

/* 
**	S'il y a une erreur de syntaxe ds la commande e.g:
**	la commande comment par un pipe "|"
*/

int	ft_syntax_error(char **commands)
{
	int i;

	i = -1;
	while (commands[++i])
	{
		if ((is_redir(commands[i]) && !(commands[i + 1])) ||
		(!ft_strcmp(commands[i], "|") && (i == 0)) ||
		(!ft_strcmp(commands[i], "|") && !(commands[i + 1])) ||
		(!ft_strcmp(commands[i], "|") && (!ft_strcmp(commands[i + 1], "|"))) ||
		(is_redir(commands[i]) == 1 && is_redir(commands[i + 1]) == 1))
			return (!(ft_error("minishell",
			"syntax error near unexpected token", commands[i], STAY)));
	}
	return (0);
}
