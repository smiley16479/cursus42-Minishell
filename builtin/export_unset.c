/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandreschwerer <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:33:59 by alexandre         #+#    #+#             */
/*   Updated: 2020/10/12 21:54:30 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**ajoute une variable d'environnement
*/

int	ft_add_envv(char *command)
{
	int		i;
	char	**new_envv;

	i = 0;
	while (g_envv[i])
		i++;
	if (!(new_envv = malloc((i + 2) * sizeof(char*))))
		ft_error("minishell", strerror(errno), ft_strdup(""), EXIT);
	i = -1;
	while (g_envv[++i])
		new_envv[i] = ft_strdup(g_envv[i]);
	new_envv[i++] = ft_strdup(command);
	new_envv[i] = NULL;
	ft_free_split(g_envv);
	g_envv = new_envv;
	return (0);
}

int	ft_export_error(char *command, char **var)
{
	int	i;

	i = -1;
	while (var[0][++i])
	{
		if ((!(ft_isalnum(var[0][i])) && var[0][i] != '_') || *command == '=')
			return (!(ft_error("export", command,
			"not a valid identifier", STAY)));
	}
	i = -1;
	while (command[++i])
	{
		if (!(ft_isalnum(command[i])) && command[i] != '=' && command[i] != '/'
		&& command[i] != '_' && command[i] != '-' && command[i] != '.'
		&& command[i] != '~' && command[i] != ' ' && command[i] != '\\')
			return (!(ft_error("export", "not valid in this context",
			command, STAY)));
	}
	if (ft_strcmp(var[0], "PWD") == 0)
		return (!(ft_error("export", "Impossible", command, STAY)));
	return (0);
}

int	ft_export(char *command, char **var)
{
	int		i;
	char	**envv;

	i = -1;
	if ((command == NULL || !ft_strcmp(command, "-p")
		|| *command == '\0') && ft_print_env(g_envv, 1))
		return (ft_free_split(var));
	if ((ft_export_error(command, var)))
		return (!(ft_free_split(var)));
	while (g_envv[++i])
	{
		envv = ft_split(g_envv[i], '=');
		if (ft_strcmp(envv[0], var[0]) == 0)
		{
			free(g_envv[i]);
			ft_free_split(envv);
			ft_free_split(var);
			return (!(g_envv[i] = ft_strdup(command)));
		}
		ft_free_split(envv);
	}
	ft_free_split(var);
	ft_add_envv(command);
	return (0);
}

/*
**détruit une variable d'environnement
*/

int	ft_destroy(int i)
{
	char	**new_env;
	int		j;
	int		k;

	j = 0;
	while (g_envv[j])
		j++;
	if (!(new_env = malloc(j * sizeof(char*))))
		ft_error("minishell", strerror(errno), ft_strdup(""), EXIT);
	j = -1;
	k = -1;
	while (g_envv[++j])
	{
		if (j != i)
			new_env[++k] = g_envv[j];
		else
			free(g_envv[i]);
	}
	free(g_envv);
	new_env[++k] = NULL;
	g_envv = new_env;
	return (0);
}

/*
**Refaire error zsh : no match found
*/

int	ft_unset(char *command)
{
	int		i;
	char	**tmp;

	i = -1;
	while (command[++i])
		if (!(ft_isalnum(command[i])) && command[i] != '/' && command[i] != '_'
		&& command[i] != '-' && command[i] != '.')
			return (ft_error("unset", "invalid parameter name", command, STAY));
	i = -1;
	if (ft_strcmp(command, "PWD") == 0)
		return (ft_error("export", "I can't let you do that", command, STAY));
	while (g_envv[++i])
	{
		tmp = ft_split(g_envv[i], '=');
		if (ft_strcmp(command, tmp[0]) == 0)
		{
			ft_free_split(tmp);
			ft_destroy(i);
			return (0);
		}
		ft_free_split(tmp);
	}
	return (1);
}
