/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 01:07:09 by adtheus           #+#    #+#             */
/*   Updated: 2020/11/23 17:09:56 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	main(int ac, char **av, char **env)
{
	char	*cmdl;
	char	***cmds;

	(void)ac;
	(void)av;
	set_env(env);
	while (get_new_cmdl(&cmdl) > 0)
	{
		cmds = parse_cmdl(cmdl);
		free(cmds);
		free(cmdl);
	}
	free(cmdl);
	return (ft_eof());
}
