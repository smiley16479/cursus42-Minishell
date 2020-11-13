/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:59:49 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 04:10:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/* 
**	Renvoie (1) si le char (c) fait partie du *set
*/

int	check_set(char c, char *set)
{
	int i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

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
**	Le process pour acquérir une ligne de commande :
**	-	Afficher le prompt
**	-	Lire la ligne entrée par l'utilisateur depuis stdin (gnl)
**	-	Vérifier s'il y a des tokens à la suite 
**			-	si oui redemander une ligne de commande (étape 1)
**			-	si non envoyer la ligne vers le parsing
*/

int get_new_cmdl(char **cmdl)
{
	int gnl_ret;

	ft_prompt();
	if ((gnl_ret = get_next_line(STDIN_FILENO, cmdl)) > 0)
		if (verify_duplicate_token_in_cmdl(*cmdl))
		{
			free(*cmdl);
			gnl_ret = get_new_cmdl(cmdl);
		}
	if (gnl_ret == -1)
		ft_error("gnl_error", "Malloc_issue", NULL, EXIT);
	return (gnl_ret);
}

/*
**	Analyse la ligne de commande et la sépare en élément 
*/
char ***parse_cmdl(char *cmdl)
{
		char		***cmds;
		int i;

		cmds = sep_cmdl_to_cmds(cmdl);
		i = -1;
		while(cmds[++i])
		{
			parse_cmds(cmds[i] = split_redir(cmds[i]));
			// ft_check_built_in(cmds);
		}
	print_3d_vec(cmds);
	return (cmds);
}

int parse_cmds(char **cmd)
{
	int i;

	i = -1;
	while (cmd[++i])
	{
		process_quote(&cmd[i]);
	}
	return (0);
}

/*
** Affiche un vecteur (char ***) sur stdout
*/

/* void	print_3d_vec(char ***vec)
{
	if (vec && *vec && **vec)
		while (*vec)
		{
			while (**vec)
				ft_printf("%s\n", *(*vec)++);
			ft_printf("remise à zero\n");
			++vec;
		}
} */ // Ne marche pas car déplace le **vec qui ne peut plus etre utilisé

void	print_3d_vec(char ***vec)
{
	int i;

	if (vec && *vec && **vec)
		while (*vec && (i = -1))
		{
			while ((*vec)[++i])
				ft_printf("%s\n", (*vec)[i]);
			++vec;
		}
}

void	destroy_3d_vec(char ***vec)
{
	int		i;
	char	***tmp;

	tmp = vec;
	if (vec && *vec && **vec)
		while (*vec && (i = -1))
		{
			while ((*vec)[++i])
				free((*vec)[i]);
			free(*vec++);
		}
	free(tmp);
}
