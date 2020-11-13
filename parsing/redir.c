/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:35:49 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/13 01:09:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
**Ferme stdin et le remplace par le contenu du fichier après le "<"
**Supprime des commandes le "<" et le fichier consécutif
*/

int		ft_stdin(char ***commands, int *pos)
{
	int		pip[2];
	int		fd;

	if ((fd = open((*commands)[*pos + 1], O_RDONLY)) == -1)
	{
		return (!ft_error("minishell", strerror(errno),
		ft_strdup((*commands)[*pos + 1]), STAY));
	}
	pipe(pip);
	if (dup2(pip[0], STDIN_FILENO) == -1)
		return (!ft_error("minishell", strerror(errno), ft_strdup("<"), STAY));
	close(pip[0]);
	file_transfer(fd, pip[1]);
	close(pip[0]);
	close(pip[1]);
	get_rid_cmd(commands, *pos, *pos + 1);
	*pos = *pos - 1;
	return (0);
}

/*
**remplace stdout par le fichier mentionné après le ">"
**en ouvrant ce fichier
*/

int		ft_stdout(char ***cmd, int *pos)
{
	int		fd;
	int		i;
	char	**commands;
	int		flag;

	flag = ft_strcmp((*cmd)[*pos], ">") ? O_APPEND : O_TRUNC;
	i = *pos;
	commands = *cmd;
	if ((fd = open(commands[i + 1], O_CREAT | flag | O_RDWR, 0644)) == -1)
	{
		return (!ft_error("minishell", strerror(errno),
		ft_strdup(commands[i + 1]), STAY));
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (!ft_error("minishell", strerror(errno), ft_strdup(">"), STAY));
	get_rid_cmd(cmd, i, i + 1);
	*pos = *pos - 1;
	return (0);
}

/*
**  Détecte les chevrons, appelle les fonctions correspondantes
** Puis appelle alias_quote, qui enlève les quotes
*/

int		ft_chevron(char ***commands)
{
	int i;
	int back;

	i = -1;
	while (++i < ft_strlen_vec(*commands))
	{
		back = 0;
		if (!ft_strcmp((*commands)[i], ">") ||
		!ft_strcmp((*commands)[i], ">>"))
			if (ft_stdout(commands, &i) || !(back = 1))
				return (g_status = 1 << 8);
		if (!(back) && !ft_strcmp((*commands)[i], "<"))
			if (ft_stdin(commands, &i))
				return (g_status = 1 << 8);
	}
	if (!ft_empty_commands(*commands))
		return (ft_parse_cmd(*commands));
	return (0);
}

/*
**S'il n'y a pas de syntax error
**détecte les pipe et renvoie vers ft_pipe
**lance la détection des chevrons si pas de pipe
*/

int		ft_redir(char **commands)
{
	t_cmd *head;

	if (ft_syntax_error(commands))
	{
		g_status = 258 << 8;
		return (1);
	}
	head = ft_split_pipe(commands);
	redir_cmds(head);
	return (0);
}
