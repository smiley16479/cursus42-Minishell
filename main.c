/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 01:07:09 by adtheus           #+#    #+#             */
/*   Updated: 2020/11/14 18:24:30 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
# define NEW_LINE "\n"
// gcc parsing.c -I../Includes ../parsing/split_quote.c ../libft/libft.a -fsanitize=address -g3


/* 
**	Analyse s'il s'agit d'un
*/

int is_a_redirection(char *cmdln)
{
	int i;
	int j;
	char *s;

	s = ">>\0>\0\0<\0\0|\0";
	i = -1;
	while (cmdln[++i] && (j = -3))
		while ((j += 3) < 10)
			if (!ft_strcmp(&cmdln[i], &s[j]))
				return (j / 3);
	return (-1);
}

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
		destroy_3d_vec(cmds);
		free(cmdl);
	}
	free(cmdl);
	write(1, "exit\n", 5);
	// erase_db_char_ptr(&cmds);
	return (0);
}