/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 00:13:26 by user42            #+#    #+#             */
/*   Updated: 2020/11/12 22:14:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include.h"
# define NEW_LINE "\n"
// gcc parsing.c -I../Includes ../parsing/split_quote.c ../libft/libft.a -fsanitize=address -g3

/* 
** Prend en paramtère la ligne de command taper par l'utilisateur
** et rend un tableau contenant toutes les chaines qui étaient 
** délimitées par ";"
*/

char ***sep_cmdl_to_cmds(char *cmdln)
{
	char ***cmds;
	char **tmp;
	int i;

	tmp = ft_split_unless_quote(cmdln, ";");
	if (!(cmds = malloc(sizeof(char *) * (ft_strlen_vec(tmp) + 1))))
		return (NULL);
	i = -1;
	while (tmp[++i])
	{
		cmds[i] = ft_split_unless_quote(tmp[i], " \t");
		free(tmp[i]);
	}
	free(tmp);
	cmds[i]= NULL;
	return cmds;
}

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
	char		***cmds;
	char		*cmdl;
	int i;
	// t_list_cmd	*lst;
	// t_list_cmd	*tmp;

	cmds = NULL;
	set_env(env);
	
	while (get_new_cmdl(&cmdl))
	{
		cmds = sep_cmdl_to_cmds(cmdl);
		i = -1;
		while(cmds[++i])
			// ft_check_built_in(cmds);
		print_3d_vec(cmds);

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