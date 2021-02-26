/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:33:59 by alexandre         #+#    #+#             */
/*   Updated: 2021/02/26 19:05:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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

int	ft_export_error_sub1(char *command, char **var)
{
	int i;

	i = -1;
	while (command[++i])
		if (!ft_isalnum(command[i]) && !check_set(command[i], "\\_-.:~ /$="))
		{
			return ((g_status |= (!ft_error("export",
			"not valid in this context", command, STAY) << 8)));
		}
	if (*var && ft_strcmp(var[0], "PWD") == 0)
	{
		return ((g_status |= (!ft_error("export",
		"Impossible", var[0], STAY) << 8)));
	}
	return (0);
}

int	ft_export_error(char *command, char **var)
{
	int	i;

	i = -1;
	if (!*command || !*var || *command == '=')
	{
		return ((g_status |= (!ft_error("export", command,
		"not a valid identifier", STAY) << 8)));
	}
	while (var[0][++i])
		if ((!ft_isalnum(var[0][i]) && !check_set(var[0][i], "/_"))
			|| **var == '=' || **var == ' ' || **var == '\0')
		{
			return ((g_status |= (!ft_error("export", command,
			"not a valid identifier", STAY) << 8)));
		}
	ft_export_error_sub1(command, var);
	return (0);
}

int	ft_export_sub1(char **envv, char **var, int i, int j)
{
	char	**tmp;

	while (var[++j])
	{
		if (ft_export_error(var[j], (tmp = ft_split(var[j], '='))))
		{
			ft_free_split(tmp);
			continue ;
		}
		while (g_envv[++i])
		{
			envv = ft_split(g_envv[i], '=');
			if (ft_strcmp(envv[0], tmp[0]) == 0)
			{
				free(g_envv[i]);
				ft_free_split(envv);
				ft_free_split(tmp);
				return (!(g_envv[i] = ft_strdup(var[j])));
			}
			ft_free_split(envv);
		}
		ft_free_split(tmp);
		ft_add_envv(var[j]);
	}
	return (0);
}

int	ft_export(char **var)
{
	char	**envv;

	envv = NULL;
	if ((*var == NULL || (!ft_strcmp(*var, "-p") &&
		var[1] == NULL)) && ft_print_env(g_envv, 1))
		return (0);
	return (ft_export_sub1(envv, var, -1, -1));
}
