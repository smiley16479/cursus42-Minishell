/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:35:07 by adtheus           #+#    #+#             */
/*   Updated: 2020/11/17 13:51:14 by adtheus          ###   ########.fr       */
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



void	loop_pipe(char **cmd) 
{
	int		p[2];
	pid_t	pid;
	int		fd_in = 0; // faut il les remplacer par std[in]
	int		piped;	

	while (!(*cmd == NULL && *(cmd + 1) == NULL))
	{
		piped = pipe_followed(cmd);
		pipe(p);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2(fd_in, 0); //change the input according to the old one 
			if (piped)
				dup2(p[1], 1);
			close(p[0]); // close(p[1]); <-- ne semble pas nécessaire
			
			process_redir(cmd);
			if (ft_check_built_in(cmd))
				exit(EXIT_SUCCESS);

			char *exec = parse_child(cmd);
			if (execve(exec, cmd, g_envv) < 0)
				write(2, "ERROR\n", 6); // execve(find_exec((*cmd)[0]), *cmd, g_envv); // la *str de parse_child n'est pas free
			exit(EXIT_FAILURE); // 126 ?
		}
		else
		{
			waitpid(-1, NULL,  WNOHANG);
			close(p[1]);
			fd_in = p[0]; //save the input for the next command
			while (*cmd) // while (*cmd++); ? ça marcherait pas mieux ça 
			{
				free(*cmd);
				++cmd;	
			}
			++cmd;
		}
	}
	waitpid(pid, NULL, 0);
}
