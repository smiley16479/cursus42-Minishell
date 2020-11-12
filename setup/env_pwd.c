/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:33:01 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/08 23:32:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
** Copie les variables d'environnement
** à l'exception du OLDPWD
*/

void	set_env(char **env)
{
	int		i;
	int		j;
	// char	*cwd;

	i = -1;
	j = 0;
	// cwd = NULL;
	while (env[++i])
		;
	// 	if (ft_strnstr(env[i], "OLDPWD", 6) != NULL)
	// 		j = 1;
	if (!(g_envv = malloc((i - j + 1) * sizeof(char*))))
		ft_error("minishell", strerror(errno), ft_strdup(""), EXIT);
	i = -1;
	j = 0;
	while (env[++i + j])
	{
//les deux variables devraient etre copiees mais _ devrait
//s'update en function de la dernière commande.

		// if (ft_strnstr(env[i + j], "OLDPWD", 6))
		// 	g_envv[i] = getcwd(cwd, 0);
		// else if (ft_strnstr(env[i + j], "_", 1))
		// 	j += 1;
		// else
			g_envv[i] = ft_strdup(env[i + j]);
	}
	g_envv[i] = NULL;
	g_status = 0;
}

/*
** Affiche le vecteur de string d'export ou env jusqu'à tomber sur NULL,
** avec **env le vecteur et trie si on veut l'afficher trié (1) ou non (0)
*/

int		ft_print_env(char **env, int trie)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = NULL;
	i = -1;
	if (trie && (tmp = malloc(sizeof(char *) * (ft_strlen_vec(env) + 1))))
	{
		while (env[++i])
			tmp[i] = env[i];
		tmp[i] = NULL;
		i = -1;
		while (tmp[++i] && (j = -1))
			while (tmp[++j])
				if (ft_strcmp(tmp[i], tmp[j]) < 0)
					ft_swap_db_char_ptr(&tmp[i], &tmp[j]);
	}
	else if (trie)
		return (ft_error("malloc", "impossible", "export", STAY));
	i = -1;
	while (env[++i])
		write_export_msg(trie ? tmp[i] : env[i], trie);
	free(tmp);
	return (1);
}

/*
**Prend en argument le nom d'une variable et renvoie sa valeur
*/

char	*find_key(char *key)
{
	int		i;
	char	**vec;
	char	*dest;

	i = -1;
	while (g_envv[++i])
	{
		vec = ft_split(g_envv[i], '=');
		if (ft_strcmp(vec[0], key) == 0)
		{
			dest = vec[1];
			free(vec[0]);
			free(vec);
			return (dest);
		}
		ft_free_split(vec);
	}
	return (ft_strdup(""));
}

int		ft_pwd(void)
{
	char *pwd;

	pwd = NULL;
	if ((pwd = getcwd(pwd, 0)))
		;
	else
		pwd = find_key("PWD");
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (0);
}
