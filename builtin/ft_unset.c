/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:33:59 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/21 02:51:44 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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

int	ft_unset(char **v, int i, int j)
{
	char	**tmp;

	while (v[++j] && (i = -1))
	{
		if (v[j][0] == '\0')
			return (!ft_error("unset", "invalid parameter name", v[j], STAY));
		while (v[j][++i])
			if (!(ft_isalnum(v[j][i])) && v[j][i] != '/' && v[j][i] != '_'
			&& v[j][i] != '-' && v[j][i] != '.')
				return (!ft_error("unset", "invalid parameter name", v[j], 11));
		i = -1;
		while (g_envv[++i])
		{
			tmp = ft_split(g_envv[i], '=');
			if (ft_strcmp(v[j], tmp[0]) == 0)
			{
				ft_free_split(tmp);
				ft_destroy(i);
				return (0);
			}
			ft_free_split(tmp);
		}
	}
	return (0);
}
