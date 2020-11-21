/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 17:35:01 by adtheus           #+#    #+#             */
/*   Updated: 2020/11/21 22:20:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	chevron_simple_et_db(char **cmd, t_bool b)
{
	int fd;

	if (0 > (fd = open(*(cmd + 1), O_CREAT | O_WRONLY |
		(b == 1 ? O_TRUNC : O_APPEND), 00644)))
		ft_error("open", strerror(errno), (b == 1 ? ">" : ">>"), STAY);
	if (dup2(fd, 1) == -1)
		ft_error("open", strerror(errno), (b == 1 ? ">" : ">>"), STAY);
	get_rid_cmd_bis(cmd, 0, 1);
}

void	backward_chevron(char **cmd)
{
	int fd;
	int	p[2];

	if (0 > (fd = open(*(cmd + 1), O_RDONLY)))
		ft_error("open", strerror(errno), "<", STAY);
	(pipe(p) == -1) ? ft_error("pipe", strerror(errno), "<", STAY) : 0;
	dup2(p[0], 0) < 0 ? ft_error("dup", strerror(errno), "<", STAY) : 0;
	file_transfer(fd, p[1]);
	close(p[0]);
	close(p[1]);
	close(fd);
	get_rid_cmd_bis(cmd, 0, 1);
}

void	process_redir(char **cmd)
{
	int	redir_type;

	while (*cmd)
	{
		redir_type = which_redir(*cmd);
		if (redir_type == 1 || redir_type == 2)
			chevron_simple_et_db(cmd, redir_type);
		else if (redir_type == 3)
			backward_chevron(cmd);
		else
			++cmd;
	}
}
