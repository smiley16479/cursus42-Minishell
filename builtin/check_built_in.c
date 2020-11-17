/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:32:40 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/17 13:12:03 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/* 
** En travaux... sert à mettre à jour la variable d'environnement '_'
*/

void	set__var(char **cmds)
{
	// for (int i = 0; cmds[i]; ++i)
	// printf("ds execve; %s\n", cmds[i]);
	
	// int 	i;
	char	**_var;

	// i = 0;
	if (!(_var = (char**)malloc(sizeof(char *) * 3)))
		ft_error("minishell", strerror(errno), "malloc", STAY);
	_var[0]	= ft_strdup("_");
	_var[1]	= ft_strdup(*cmds);
	_var[2] = NULL;
	ft_export(ft_strdup("cmd"), _var);
	ft_free_split(_var);

	// ft_export(cmds[i + 1], ft_split(cmds[i + 1], '=')
}

void	ft_exit(char **commands)
{
	int num;
	int i;

	i = -1;
	ft_free_split(g_envv);
	num = g_status >> 8;
	if (commands[1] != NULL)
	{
		while (commands[1][++i])
			if (commands[1][i] < '0' || commands[1][i] > '9')
			{
				ft_error("minishell: exit", commands[1],
				"numeric argument required", STAY);
				ft_free_split(commands);
				exit(2);
			}
		num = ft_atoi(commands[1]);
	}
	ft_free_split(commands);
	exit(num);
}

/*
***Renvoie vers le bon built in.
***Renvoie 0 si un builtin est détecté
***1 sinon
*/

int		ft_check_built_in(char **cmds)
{
	int i;

	i = -1;
	if (ft_strcmp("cd", cmds[0]) == 0)
		g_status = ft_cd(cmds[1]) << 8;
	else if (ft_strcmp("export", cmds[0]) == 0 && cmds[1] == NULL)
		ft_print_env(g_envv, 1);
	else if (ft_strcmp("export", cmds[0]) == 0)
		while (cmds[++i + 1])
			g_status = ft_export(cmds[i + 1], ft_split(cmds[i + 1], '=')) << 8;
	else if (ft_strcmp("unset", cmds[0]) == 0)
		while (cmds[++i + 1])
			g_status = ft_unset(cmds[i + 1]) << 8;
	else if (ft_strcmp("echo", cmds[0]) == 0)
		g_status = ft_echo(cmds) << 8;
	else if (ft_strcmp("exit", cmds[0]) == 0)
		ft_exit(cmds);
	else if (ft_strcmp("env", cmds[0]) == 0)
		g_status = !ft_print_env(g_envv, 0) << 8;
	else if (ft_strcmp("pwd", cmds[0]) == 0)
		g_status = ft_pwd() << 8;
	else
		return (0);
	return (1);
}
