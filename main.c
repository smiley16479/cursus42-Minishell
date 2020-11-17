/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 01:07:09 by adtheus           #+#    #+#             */
/*   Updated: 2020/11/17 14:21:01 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
# define NEW_LINE "\n"
// gcc parsing.c -I../Includes ../parsing/split_quote.c ../libft/libft.a -fsanitize=address -g3

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	char	*cmdl;
	char 	***cmds;

	// t_list_cmd	*lst;
	// t_list_cmd	*tmp;


	set_env(env);
	while (get_new_cmdl(&cmdl))
	{	
		cmds = parse_cmdl(cmdl);

/* 		lst = new_lst_of_cmds(cmds);
		tmp = lst;
		while (tmp)
		{
			// ft_printf("lst :%s\n", tmp->cmd);
			tmp = tmp->next;
		}
		erase_main_materials(lst, cmds, cmdl); */

		
		// destroy_3d_vec(cmds); // plus besoin de destroy car free peu à peu ds loop pipe
		free(cmds);
		free(cmdl);
	}
	free(cmdl);
	return (g_status);
}