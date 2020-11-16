/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:35:07 by adtheus           #+#    #+#             */
/*   Updated: 2020/11/16 12:23:23 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	loop_pipe(char **cmd) 
{
	int		p[2];
	pid_t	pid;
	int		fd_in = 0; // faut il les remplacer par std[in]
	int		i;	

	i = -1;
	while (!(*cmd == NULL && *(cmd + 1) == NULL) && (i = -1))
	{
		while (*(cmd[++i]) != '|' && cmd[i] != NULL && cmd[i + 1] != NULL )
			;
		if (*(cmd[i]) == '|')
		{
			free(cmd[i]);
			cmd[i] = NULL;
		}
		pipe(p);
		if ((pid = fork()) == -1)
		{
			exit(EXIT_FAILURE);
		}
	  else if (pid == 0)
		{
			dup2(fd_in, 0); //change the input according to the old one 
			if (*(cmd + 1) != NULL)
				dup2(p[1], 1);
			close(p[0]);
			close(p[1]);
			char *exec = parse_child(cmd);
			execve(exec, cmd, g_envv); // execve(find_exec((*cmd)[0]), *cmd, g_envv); // la *str de parse_child n'est pas free
			exit(EXIT_FAILURE);
		}
	  else
		{
			waitpid(-1, NULL, WNOHANG);

			close(p[1]);
			fd_in = p[0]; //save the input for the next command
			while (cmd)
				++cmd;
			++cmd;
		}
	}
	waitpid(-1, &g_status, 0);
}
