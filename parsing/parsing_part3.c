/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 17:35:01 by adtheus           #+#    #+#             */
/*   Updated: 2021/02/25 19:44:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_parse	*chevron_simple_et_db_ls(t_parse *ls, t_bool b)
{
	int fd;

	if (0 > (fd = open(ls->cont, O_CREAT | O_WRONLY |
		(b == 1 ? O_TRUNC : O_APPEND), 00644)))
		ft_error("open", strerror(errno), (b == 1 ? ">" : ">>"), STAY);
	if (dup2(fd, 1) == -1)
		ft_error("open", strerror(errno), (b == 1 ? ">" : ">>"), STAY);
	return (list_elem_remove(ls));
}

t_parse	*backward_chevron_ls(t_parse *ls)
{
	int fd;
	int	p[2];

	if (0 > (fd = open(ls->cont, O_RDONLY)))
		ft_error("open", strerror(errno), "<", STAY);
	(pipe(p) == -1) ? ft_error("pipe", strerror(errno), "<", STAY) : 0;
	dup2(p[0], 0) < 0 ? ft_error("dup", strerror(errno), "<", STAY) : 0;
	file_transfer(fd, p[1]);
	close(p[0]);
	close(p[1]);
	close(fd);
	return (list_elem_remove(ls));
}

void	process_redir_ls_suite(t_parse **list, t_parse **ls, int redir_type)
{
	if (redir_type == 1 || redir_type == 2)
	{
		if ((*ls)->prev == NULL)
		{
			*list = chevron_simple_et_db_ls((*ls), redir_type);
			(*ls) = *list;
		}
		else
			(*ls) = chevron_simple_et_db_ls((*ls), redir_type);
	}
	else if (redir_type == 3)
	{
		if ((*ls)->prev == NULL)
		{
			*list = backward_chevron_ls((*ls));
			(*ls) = *list;
		}
		else
			(*ls) = backward_chevron_ls((*ls));
	}
	else
		(*ls) = (*ls)->next;
}

int		process_redir_ls(t_parse **list)
{
	int		redir_type;
	t_parse	*ls;

	ls = *list;
	while (ls && (ls->typ & CMDEND) != CMDEND)
	{
		if ((redir_type = which_redir(ls->cont)))
		{
			if (ls->prev == NULL)
			{
				*list = list_elem_remove(ls);
				ls = *list;
			}
			else
				(ls = list_elem_remove(ls));
		}
		if ((ls->typ & BAD_CHEV) == BAD_CHEV)
		{
			write(2, "bash : ambiguous redirection\n", 30);
			g_status = 1 << 8;
			return (1);
		}
		process_redir_ls_suite(list, &ls, redir_type);
	}
	return (0);
}
