/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 01:07:09 by adtheus           #+#    #+#             */
/*   Updated: 2021/02/25 21:03:23 by user42           ###   ########.fr       */
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
