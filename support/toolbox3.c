/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:51 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/14 23:41:26 by adtheus          ###   ########.fr       */
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
** Indique les pos des chaines à détruire selon [beg - end] (inclus)
*/

void	get_rid_cmd_bis(char **cmd, int beg, int end)
{
	int i;

	i = -1;
	while (++i + beg <= end)
		free(cmd[beg + i]);
	while (cmd[end])
		cmd[beg++] = cmd[++end];
	cmd[beg] = NULL;
}

/* 
**	Return respectivement 1, 2 ,3 ou 4 pour >, >>, < ou | sinon return (0)
*/

bool	which_redir(char *str)
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
**	S'il y a une erreur de syntaxe ds la commande e.g:
**	la commande comment par un pipe "|"
*/

int	ft_syntax_error(char **commands)
{
	int i;
	bool b[2];

	b[0] = which_redir(commands[i]);
	b[1] = which_redir(commands[i + 1]);
	i = -1;
	while (commands[++i])
	{
		if ((b[0] && !b[1]) || (!ft_strcmp(commands[i], "|") && (i == 0)) ||
		(!ft_strcmp(commands[i], "|") && !(commands[i + 1])) ||
		(!ft_strcmp(commands[i], "|") && (!ft_strcmp(commands[i + 1], "|"))) ||
		(b[0] != 0 && b[0] < 4 && b[1] != 0 && b[1] < 4))
			return (!(ft_error("minishell",
			"syntax error near unexpected token", commands[i], STAY)));
	}
	return (0);
}
