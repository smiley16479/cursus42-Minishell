/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:35:07 by adtheus           #+#    #+#             */
/*   Updated: 2020/11/17 19:39:32 by adtheus          ###   ########.fr       */
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
	if (!pipe_followed(cmd))
	{
		simple_cmd(cmd);
		while (*cmd)
			free(*cmd++);
	}
	else
		loop_pipe(cmd);
}

void	loop_pipe(char **cmd)
{
	int		p[2];
	pid_t	pid;
	int		fd_in = 0; // faut il les remplacer par std[in]
	int		piped;

	while (!(*cmd == NULL && *(cmd + 1) == NULL))
	{
		pipe(p);
		process_redir(cmd);
		piped = pipe_followed(cmd);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2(fd_in, 0); //change the input according to the old one 
			if (piped)
				dup2(p[1], 1);
			close(p[0]); // close(p[1]); <-- ne semble pas nécessaire
			if (ft_check_built_in(cmd))
				exit(g_status);
			char *exec = parse_child(cmd);
			if (execve(exec, cmd, g_envv) < 0)
				write(2, "ERROR\n", 6); // execve(find_exec((*cmd)[0]), *cmd, g_envv); // la *str de parse_child n'est pas free
			exit(EXIT_FAILURE); // 126 ?
		}
		else
		{
			// waitpid(-1, NULL,  WNOHANG); // <-- ne semble pas nécessaire
			close(p[1]);
			fd_in = p[0]; //save the input for the next command
			while (*cmd)
				free(*cmd++);
			++cmd;
		}
	}
	waitpid(pid, &g_status, 0);
}
