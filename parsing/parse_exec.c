/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:35:01 by alexandre         #+#    #+#             */
/*   Updated: 2021/02/26 17:09:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
**recherche un exécutable dans tous les dossiers mentionnés par Path
*/

char		*ft_parse_path(char *exec, char **dir)
{
	char		*file;
	char		*tmp;
	struct stat	filestat;
	int			i;

	i = -1;
	if (lstat(exec, &filestat) == 0 && (S_ISREG(filestat.st_mode)))
		return (exec);
	while (dir[++i])
	{
		tmp = ft_strjoin(dir[i], "/");
		file = ft_strjoin(tmp, exec);
		free(tmp);
		if (lstat(file, &filestat) == 0 && (S_ISREG(filestat.st_mode)))
		{
			ft_free_split(dir);
			return (file);
		}
		free(file);
	}
	ft_free_split(dir);
	return (NULL);
}

/*
**recherche un exécutable dans tous les dossiers mentionnés par Path
**puis dans le dossier présent
*/

char		*ft_parse_exec(char *exec, char **dir)
{
	char		*file[2];
	char		*executable;
	struct stat	filestat;

	file[0] = NULL;
	file[1] = NULL;
	if (dir)
		if ((executable = ft_parse_path(exec, dir)))
			return (executable);
	file[0] = getcwd(file[0], 0);
	file[1] = ft_strjoin(file[0], "/");
	free(file[0]);
	file[0] = ft_strjoin(file[1], exec);
	if (lstat(file[0], &filestat) == 0 && (S_ISREG(filestat.st_mode)))
	{
		free(file[0]);
		free(file[1]);
		return (exec);
	}
	free(file[0]);
	free(file[1]);
	ft_error("minishell", exec, "command not found", STAY);
	exit(127);
	return (NULL);
}

/*
**déclenche parse_exec
*/

char		*parse_child(char **commands)
{
	char *path;
	char *exec;

	path = find_key("PATH");
	exec = ft_parse_exec(commands[0], ft_split(path, ':'));
	free(path);
	return (exec);
}
