/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandreschwerer <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:34:18 by alexandre         #+#    #+#             */
/*   Updated: 2020/10/21 15:38:02 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export_pwd(char *command)
{
	int		i;
	char	**envv;

	i = -1;
	while (g_envv[++i])
	{
		envv = ft_split(g_envv[i], '=');
		if (ft_strcmp(envv[0], "PWD") == 0)
		{
			free(g_envv[i]);
			ft_free_split(envv);
			return (!(g_envv[i] = command));
		}
		ft_free_split(envv);
	}
	ft_add_envv(command);
	return (0);
}

void	ft_cd_exp(char *path, int i)
{
	char	buff[1024];
	char	*oldpwd;
	char	*pwd;
	char	*keypwd;

	getcwd(buff, 1024);
	keypwd = find_key("PWD");
	oldpwd = ft_strjoin("OLDPWD=", keypwd);
	pwd = ft_strjoin("PWD=", buff);
	ft_export(oldpwd, ft_split(oldpwd, '='));
	ft_export_pwd(pwd);
	if (i)
		free(path);
	free(keypwd);
	free(oldpwd);
}

int		ft_cd(char *path)
{
	int		i;

	i = !(path) ? 1 : 0;
	if (!(path))
		path = find_key("HOME");
	if (!(path[0]))
		return (!(ft_error("minishell", "cd", "HOME not set", STAY)));
	if ((g_status = !(!(chdir(path)))))
		return (!(ft_error("cd", strerror(errno), path, STAY)));
	else
		ft_cd_exp(path, i);
	return (0);
}
