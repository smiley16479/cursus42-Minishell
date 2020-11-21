/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:51 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/21 22:41:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int		get_rid_cmd(char ***cmd, int beg, int end)
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

int		get_rid_cmd_bis(char **cmd, int beg, int end)
{
	int i;

	i = -1;
	while (++i + beg <= end)
		free(cmd[beg + i]);
	while (&cmd[end] != g_endtab)
		cmd[beg++] = cmd[++end];
	cmd[beg] = NULL;
	return (1);
}

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
