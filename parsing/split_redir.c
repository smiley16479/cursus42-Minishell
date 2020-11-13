/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:10 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/12 22:51:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
** Isole les chaines de char
*/

int		find_char(char *str, int *i)
{
	char	*ptr;
	int		quot[2];

	quot[0] = 0;
	quot[1] = 0;
	ptr = &str[*i];
	while (str[*i])
	{
		if (str[*i] == '\"' && !(quot[1]))
			quot[0] = (quot[0] + 1) % 2;
		if (str[*i] == '\'' && !(quot[0]))
			quot[1] = (quot[1] + 1) % 2;
		if (!(quot[0] + quot[1]) && (str[*i] == '>' || str[*i] == '<' ||
		str[*i] == '|'))
			return (ptr != &str[*i]);
		if (str[*i] == '\\' && ((str[*i + 1]) == '>' || str[*i + 1] == '<'
		|| str[*i + 1] == '|'))
			++*i;
		++*i;
	}
	return (ptr != &str[*i]);
}

/*
** Isole les redirections
*/

int		find_redir(char *str, int *i)
{
	char	*ptr;

	ptr = &str[*i];
	if (!ft_strncmp(&str[*i], ">>", 2))
		*i += 2;
	else if (!ft_strncmp(&str[*i], ">", 1) || !ft_strncmp(&str[*i], "<", 1)
		|| !ft_strncmp(&str[*i], "|", 1))
		++*i;
	return (ptr != &str[*i]);
}

/*
** trouve le nombre de chaine(s) si elle contient des redirections
** "echo hey>a" => contient 4 chaines
*/

int		ft_find_strs(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*set;

	set = ">>\0<\0\0|\0\0>";
	i = 0;
	k = 0;
	while (str[i] && (j = -3))
	{
		k += find_char(str, &i);
		while (str[i] && (j += 3) < 12)
			if (!ft_strncmp(&str[i], &set[j], ft_strlen(&set[j])))
			{
				++k;
				i += ft_strlen(&set[j]);
				break ;
			}
	}
	return (k);
}

/*
**permet de couper "echo >text.txt" en "echo > text.txt"
**transforme echo \> en echo >
*/

void	cut_strs(char *commands, char **dest, int *k)
{
	int i;
	int j;
	int prev;

	i = 0;
	while (commands[i])
	{
		prev = i;
		if (find_char(commands, &i))
			dest[++*k] = ft_substr(commands, prev, i - prev);
		else if (find_redir(commands, &i))
			dest[++*k] = ft_substr(commands, prev, i - prev);
	}
	i = -1;
	while (++i <= *k)
	{
		j = -1;
		while (dest[i][++j])
		{
			if (dest[i][j] == '\\' && (dest[i][j + 1] == '>' ||
			dest[i][j + 1] == '<' || dest[i][j + 1] == '|'))
				ft_get_rid(&dest[i], j);
		}
	}
}

/*
**transforme echo >text.txt en echo > text.txt
*/

char	**split_redir(char **commands)
{
	char	**dest;
	int		i;
	int		k;

	i = -1;
	k = 0;
	while (commands[++i])
		k += ft_find_strs(commands[i]);
	if (!(dest = malloc((k + 1) * sizeof(char *))))
		ft_error("minishell", strerror(errno), ft_strdup(""), EXIT);
	dest[k] = NULL;
	k = -1;
	i = -1;
	while (commands[++i])
		if (ft_find_strs(commands[i]) > 1)
			cut_strs(commands[i], dest, &k);
		else
			dest[++k] = ft_strdup(commands[i]);
	ft_free_split(commands);
	return (dest);
}
