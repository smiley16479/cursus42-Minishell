/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:35:41 by alexandre         #+#    #+#             */
/*   Updated: 2020/12/04 15:54:49 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	ft_prompt_suite(int j, char *home, char *pwd)
{
(void)j;
	write(1, "\e[32;40m", 8); // <-- c'est la couleur qui fait bugger le prompt
	if (!(pwd = getcwd(pwd, 0)))
		pwd = find_key("PWD");
	if ((j == 0) && (home = malloc(sizeof(char))))
		home[0] = '\0';
	else
		write(1, "~", 1);
	// write(1, &pwd[ft_strlen(home)], ft_strlen(pwd) - ft_strlen(home));
	write(1, pwd, ft_strlen(pwd));
	write(1, "\e[0m", 4); // <-- la couleur fait bugger le prompt (les deux: set et reset)
	free(pwd);
	free(home);
	ft_putstr_fd("$ ", 1);
}

void	ft_prompt(void)
{
	char	**var;
	char	*pwd;
	char	*home;
	int		i;
	int		j;

	i = -1;
	j = 0;
	pwd = NULL;
	while (g_envv[++i])
	{
		var = ft_split(g_envv[i], '=');
		if (ft_strcmp(var[0], "HOME") == 0 && (j = 1))
			home = !var[1] ? ft_strdup("") : ft_strdup(var[1]);
		ft_free_split(var);
	}
	ft_prompt_suite(j, home, pwd);
}
