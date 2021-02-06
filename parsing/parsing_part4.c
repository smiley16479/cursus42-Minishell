/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:35:07 by adtheus           #+#    #+#             */
/*   Updated: 2021/02/04 19:55:03 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
** Si la commande courante est suivie d'un pipe return (1) sinon (0)
*/

int		pipe_followed(char **cmd)
{
	while (*cmd && **cmd != '|')
		++cmd;
	if (*cmd && **cmd == '|')
	{
		free(*cmd);
		*cmd = NULL;
		return (1);
	}
	return (0);
}

/*
** Execute une commande non pipée
*/

void	simple_cmd(char **cmd)
{
	pid_t	pid;

	process_redir(cmd);
	if (ft_check_built_in(cmd))
		return ;
	if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		if (execve(parse_child(cmd), cmd, g_envv) < 0)
			exit(EXIT_FAILURE);
	waitpid(pid, &g_status, 0);
}

/*
** Fonction d'appel pour executer les commandes :
** 	- Si la commande n'est pas pipée on l'éxécute simplement => simple_cmd()
**	- Si elle comporte des pipes la **cmd est envoyée vers loop_pipe
**	PS pour la norme i_l_t_n comporte [0] = le fd de la fin du pipe
**	[1] = si la commande est pipée ou non, [2] = le PID du child actuel
*/

void	execution(char **cmd)
{
	int		i_l_t_n[3];

	if (!(i_l_t_n[1] = pipe_followed(cmd)))
	{
		simple_cmd(cmd);
		while (*cmd)
			free(*cmd++);
	}
	else
		loop_pipe(cmd, i_l_t_n);
}

/*
** Assure la liaison d'un pipe à l'autre.
** (était loop_pipe avt de voir que ça faisait trop de lignes)
*/

void	i_love_the_norm(char ***cmd, int *p, int *i_l_t_n, char *exec)
{
	if ((i_l_t_n[2] = fork()) == -1)
		return ((void)ft_error("minishell", strerror(errno), "fork", EXIT));
	else if (i_l_t_n[2] == 0)
	{
		dup2(i_l_t_n[0], 0);
		if (i_l_t_n[1])
			dup2(p[1], 1);
		close(p[0]);
		if (ft_check_built_in(*cmd))
			exit(g_status);
		exec = parse_child(*cmd);
		if (execve(exec, *cmd, g_envv) < 0)
			ft_error("minishell", strerror(errno), exec, STAY);
		exit(126);
	}
	else
	{
		close(p[1]);
		i_l_t_n[0] = p[0];
		while (**cmd)
			free(*(*cmd)++);
		++(*cmd);
	}
	i_l_t_n[1] = pipe_followed(*cmd);
}

/*
** Exécute une commande pipée
*/

void	loop_pipe(char **cmd, int *i_l_t_n)
{
	int		p[2];
	char	*exec;

	exec = NULL;
	i_l_t_n[0] = 0;
	while (!(*cmd == NULL && *(cmd + 1) == NULL))
	{
		pipe(p);
		process_redir(cmd);
		i_love_the_norm(&cmd, p, i_l_t_n, exec);
	}
	waitpid(i_l_t_n[2], &g_status, 0);
}
