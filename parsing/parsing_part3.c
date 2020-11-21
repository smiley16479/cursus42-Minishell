/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 17:35:01 by adtheus           #+#    #+#             */
/*   Updated: 2020/11/21 19:36:56 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"


void chevron_simple_et_db(char **cmd, bool b)
{
	int fd;

	if (0 > (fd = open(*(cmd + 1), O_CREAT|O_WRONLY| (b == 1 ? O_TRUNC : O_APPEND), 00644)))
		ft_error("open", strerror(errno), (b == 1 ? ">" : ">>"), STAY);
	if (dup2(fd, 1/* std[out] */) == -1)
		ft_error("open", strerror(errno), (b == 1 ? ">" : ">>"), STAY);
	// close(fd);
	get_rid_cmd_bis(cmd, 0, 1);
}

void backward_chevron(char **cmd)
{
	int fd;
	int	p[2];

	if (0 > (fd = open(*(cmd + 1), O_RDONLY)))
		ft_error("open", strerror(errno), "<", STAY);
	(pipe(p) == -1) ? ft_error("pipe", strerror(errno), "<", STAY) : 0;
	dup2(p[0], 0/* std[in] */) < 0 ? ft_error("dup", strerror(errno), "<", STAY) : 0;
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