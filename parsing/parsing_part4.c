/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:35:07 by adtheus           #+#    #+#             */
/*   Updated: 2020/11/21 19:11:31 by adtheus          ###   ########.fr       */
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
			exit(EXIT_FAILURE); // 126 ?
	waitpid(pid, &g_status, 0);
}

void	execution(char **cmd)
{
	int		I_L_T_N[3];

	if (!(I_L_T_N[1] = pipe_followed(cmd)))
	{
		simple_cmd(cmd);
		while (*cmd)
			free(*cmd++);
	}
	else
		loop_pipe(cmd, I_L_T_N);
}

/* 
** Assure la liaison d'un pipe à l'autre.
** (était loop_pipe avt de voir que ça faisait 28 lignes)
*/

void	I_love_the_norm(char ***cmd, int *p, int *I_L_T_N)
{
	if ((I_L_T_N[2] = fork()) == -1)
		return ((void)ft_error("minishell", strerror(errno), "fork", EXIT));
	else if (I_L_T_N[2] == 0)
	{
		dup2(I_L_T_N[0], 0); //change the input according to the old one 
		if (I_L_T_N[1])
			dup2(p[1], 1);
		close(p[0]); // close(p[1]); <-- ne semble pas nécessaire
		if (ft_check_built_in(*cmd))
			exit(g_status);
		char *exec = parse_child(*cmd);
		if (execve(exec, *cmd, g_envv) < 0)
			ft_error("minishell", strerror(errno), exec, STAY);
		exit(126);
			// write(2, "ERROR\n", 6); // execve(find_exec((**cmd)[0]), **cmd, g_envv); // la *str de parse_child n'est pas free
	}
	else
	{
		// waitpid(-1, &g_status,  WNOHANG); // <-- ne semble pas nécessaire
		close(p[1]);
		I_L_T_N[0] = p[0]; //save the input for the next command
		while (**cmd)
			free(*(*cmd)++);
		++(*cmd);
	}
	I_L_T_N[1] = pipe_followed(*cmd);
}

void	loop_pipe(char **cmd, int *I_L_T_N)
{
	int		p[2];
/* 	pid_t	pid;
	int		fd_in = 0; // faut il les remplacer par std[in]
	int		piped; */

	// int		I_L_T_N[3] = {fd_in, piped, pid};
	I_L_T_N[0] = 0;

	while (!(*cmd == NULL && *(cmd + 1) == NULL))
	{
		pipe(p);
		process_redir(cmd);
		I_love_the_norm(&cmd, p, I_L_T_N);
	}
	waitpid(I_L_T_N[2], &g_status, 0);
}
