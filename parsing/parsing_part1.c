/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:59:49 by user42            #+#    #+#             */
/*   Updated: 2020/11/16 12:10:02 by adtheus          ###   ########.fr       */
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
	char	***cmds;
	char	**tmp;
	int		i;

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
			if ((std[in] = dup(STDIN_FILENO)) < 0 || 0 > (std[out] = dup(STDOUT_FILENO)))
				ft_error("dup", "fd duplication failed", "dup", STAY);
			parse_cmd(cmds[i] = split_redir(cmds[i]));
			if (dup2(std[in], STDIN_FILENO) < 0 || 0 > dup2(std[out], STDOUT_FILENO))
				ft_error("dup2", "fd duplication failed", "dup2", STAY);
		}
		// print_3d_vec(cmds);
	return (cmds);
}

/* 
**	Active les fonctions de parsing :
**	1. Les quotes ds le fichier parsing_part.2
**	2. Les redirections ds le fichier parsing_part.3
**	3. Les pipes ds le fichier parsing_part.4
*/

int parse_cmd(char **cmd)
{
	process_quote(cmd);
	// process_redir(cmd); // dan sles redir on aura un problème s'il y a plusieurs redirections
	// ft_check_built_in(cmds);
	// printf("0 : %s\n1 : %s\n2 : %s\n3 : %s\n4 : %s\n", 
	// *cmd, *(cmd + 1), *(cmd + 2), *(cmd + 3), *(cmd + 4));
	loop_pipe(cmd);
// print_2d_vec(cmd);
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
