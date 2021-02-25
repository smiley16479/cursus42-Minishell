/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:35:07 by adtheus           #+#    #+#             */
/*   Updated: 2021/02/24 16:07:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
** Si la commande courante est suivie d'un pipe return (1) sinon (0)
*/

int		pipe_followed_ls(t_parse *ls)
{
	while (ls && !(ls->typ & FINAL_END))
		if (*ls->cont == '|' && (ls->typ & 0x0F) == 0)
			break ;
		else
			ls = ls->next;
	if (ls && !(ls->typ & FINAL_END) && *ls->cont == '|' && !(ls->typ & 0x0F))
	{
		ls->typ += CMDEND;
		// printf("ds pipe cont1 : %s, typ ->%d\n", ls->cont, ls->typ);
		return (1);
	}
	// printf("ds pipe cont2 : %s, typ ->%d\n", ls->cont, ls->typ);
	return (0);
}

/*
** Execute une commande non pipée
*/

void	simple_cmd_ls(t_parse **ls)
{
	pid_t	pid;
	char	**cmd;

	// printf("ds simple cmd\n");
	// list_read(*ls);
	// process_redir_ls(ls);
	if (process_redir_ls(ls)) //si redir ambigue on saute les autres instructions
		while ((*ls) && !((*ls)->typ & CMDEND))
			(*ls) = (*ls)->next;
	cmd = construct_tab_from_ls(ls);
	// for (size_t i = 0; cmd[i]; i++)
		// printf("cmd[i]: %s\n", cmd[i]);
	if (ft_check_built_in(cmd))
		/* return */ ;
	else if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		if (execve(parse_child(cmd), cmd, g_envv) < 0)
			exit(EXIT_FAILURE);
	ft_free_split(cmd);
	waitpid(pid, &g_status, 0);
}


/*
** Fonction d'appel pour executer les commandes :
** 	- Si la commande n'est pas pipée on l'éxécute simplement => simple_cmd()
**	- Si elle comporte des pipes la **cmd est envoyée vers loop_pipe
**	PS pour la norme i_l_t_n comporte [0] = le fd de la fin du pipe
**	[1] = si la commande est pipée ou non, [2] = le PID du child actuel
*/

void	execution_ls(t_parse **ls)
{
	int		i_l_t_n[3];

	if (!(i_l_t_n[1] = pipe_followed_ls(*ls)))
		simple_cmd_ls(ls);
	else
		loop_pipe_ls(ls, i_l_t_n);
	// printf("ds exec : %p\n", *ls);
	list_destroy(*ls);
}

/*
** Assure la liaison d'un pipe à l'autre.
** (était loop_pipe avt de voir que ça faisait trop de lignes)
*/

void	loop_pipe_ls_suite(t_parse **ls, int *p, int *i_l_t_n, char *exec)
{
	char **cmd;

	cmd = construct_tab_from_ls(ls);
	// printf("loop_pipe_suite\n");
	// for (size_t i = 0; cmd[i]; i++)
	// {
	// 	printf("loop_pipe,cmd: [%s]\n", cmd[i]);
	// }
	// list_read(*ls);
	if ((i_l_t_n[2] = fork()) == -1)
		return ((void)ft_error("minishell", strerror(errno), "fork", EXIT));
	else if (i_l_t_n[2] == 0)
	{
		dup2(i_l_t_n[0], 0);
		if (i_l_t_n[1])
			dup2(p[1], 1);
		close(p[0]);
		if (ft_check_built_in(cmd))
			exit(g_status);
		exec = parse_child(cmd);
		if (execve(exec, cmd, g_envv) < 0)
			ft_error("minishell", strerror(errno), exec, STAY);
		exit(126);
	}
	else
	{
		close(p[1]);
		i_l_t_n[0] = p[0];
		ft_free_split(cmd);
	}
	i_l_t_n[1] = pipe_followed_ls(*ls);
}

/*
** Exécute une commande pipée
*/

void	loop_pipe_ls(t_parse **ls, int *i_l_t_n)
{
	int		p[2];
	char	*exec;

	exec = NULL;
	i_l_t_n[0] = 0;
	// printf("loop_pipe,cmd\n");
	while (*ls && !((*ls)->typ & FINAL_END))
	{
		// printf("ds loop_pipe cont : %s, typ ->%d\n", (*ls)->cont, (*ls)->typ);
		pipe(p);
		if (process_redir_ls(ls)) //si redir ambigue on saute les autres instructions
			while ((*ls) && !((*ls)->typ & CMDEND))
				(*ls) = (*ls)->next;
		loop_pipe_ls_suite(ls, p, i_l_t_n, exec);
	}
	waitpid(i_l_t_n[2], &g_status, 0);
}