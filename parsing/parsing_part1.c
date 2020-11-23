/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:59:49 by user42            #+#    #+#             */
/*   Updated: 2020/11/23 17:21:25 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
**	Renvoie (1) si le char (c) fait partie du *set
*/

int		check_set(char c, char *set)
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

char	***sep_cmdl_to_cmds(char *cmdln)
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
	cmds[i] = NULL;
	return (cmds);
}

/*
**	Le process pour acquérir une ligne de commande :
**	-	Armer les signaux
**	-	Afficher le prompt
**	-	Lire la ligne entrée par l'utilisateur depuis stdin (gnl)
**	-	Vérifier s'il y a des tokens à la suite
**			-	si oui redemander une ligne de commande (étape 1)
**			-	si non envoyer la ligne vers le parsing
*/

int		get_new_cmdl(char **cmdl)
{
	int gnl_ret;

	signal_set_up(ft_handle_signal);
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
**	Sépare la ligne de commande en commandes et l'analyse
*/

char	***parse_cmdl(char *cmdl)
{
	char	***cmds;
	int		std[2];
	int		i;

	if (!*(cmds = sep_cmdl_to_cmds(cmdl)))
		return (cmds);
	else if (!(**cmds))
	{
		free(*cmds);
		return (cmds);
	}
	i = -1;
	while (cmds[++i])
	{
		if ((std[in] = dup(0)) < 0 ||
			0 > (std[out] = dup(1)))
			ft_error("dup", "fd duplication failed", "dup", STAY);
		process_cmd(cmds[i] = split_redir(cmds[i]));
		if (dup2(std[in], 0) < 0 || 0 > dup2(std[out], 1))
			ft_error("dup2", "fd duplication failed", "dup2", STAY);
	}
	return (cmds);
}

/*
**	Active les fonctions de parsing :
**	1. Les quotes ds le fichier parsing_part.2
**	2. Les redirections ds le fichier parsing_part.3
**	3. Les pipes et l'éxécution ds le fichier parsing_part.4
*/

int		process_cmd(char **cmd)
{
	parse_cmd(cmd);
	execution(cmd);
	free(cmd);
	return (0);
}
