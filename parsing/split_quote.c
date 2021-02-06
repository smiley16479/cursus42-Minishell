/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:34:30 by alexandre         #+#    #+#             */
/*   Updated: 2021/02/05 18:49:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
**Calcule la taille du vecteur qui sera renvoyé par split_quote
*/

int		ft_len_split_unless_quote(char *line, char *sep)
{
	int quot[2];
	int len;
	int i;

	quot[0] = 0;
	quot[1] = 0;
	len = 1;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"' && !(quot[1]))
			quot[0] = (quot[0] + 1) % 2;
		if (line[i] == '\'' && !(quot[0]))
			quot[1] = (quot[1] + 1) % 2;
		if (check_set(line[i], sep) && i != 0 && !check_set(line[i - 1], sep)
			&& !(quot[0]) && !(quot[1]))
			len++;
		if (line[i] == '\\' && check_set(line[i + 1], sep))
			i++;
	}
	return (len);
}

/*
**Copie i caractères à partir du prev-ième caractère de line dans dest
*/

char	*copy_word(char *line, int prev, int i)
{
	char	*dest;

	if (prev == i)
		return (NULL);
	dest = malloc(i - prev + 1);
	ft_strlcpy(dest, line + prev, i - prev + 1);
	return (dest);
}

void	ft_extract_sep_quote_norm(char *command, int *quot, int i)
{
	if (command[i] == '\"' && !(quot[1]))
		quot[0] = (quot[0] + 1) % 2;
	if (command[i] == '\'' && !(quot[0]))
		quot[1] = (quot[1] + 1) % 2;
}

char	**ft_extract_sep_quote(char **dest, char *command, char *sep)
{
	int i;
	int j;
	int prev;
	int quot[2];

	i = -1;
	j = -1;
	quot[0] = 0;
	quot[1] = 0;
	prev = 0;
	while (command[++i])
	{
		ft_extract_sep_quote_norm(command, quot, i);
		if (check_set(command[i], sep) && i != 0 &&
		!check_set(command[i - 1], sep) && !(quot[0] + quot[1]))
			dest[++j] = copy_word(command, prev, i);
		if (check_set(command[i], sep) && !(quot[0]) && !(quot[1]))
			prev = i + 1;
		if (command[i] == '\\' && check_set(command[i + 1], sep))
			i++;
	}
	dest[++j] = copy_word(command, prev, i);
	dest[++j] = NULL;
	return (dest);
}

int		change_alias_if_not_in_quote(char **command)
{
	int		i;
	int		quot[2];
	t_bool	triger;

	quot[0] = 0;
	quot[1] = 0;
	i = 0;
	triger = 0;
	while ((*command)[i])
	{
		ft_extract_sep_quote_norm(*command, quot, i);
		if ((*command)[i] == '$' && !(quot[0] + quot[1]) &&
		!check_set((*command)[i + 1], "\0\"\'") /* (*command)[i + 1]
		!= '\0' && (*command)[i + 1] != '\"' && (*command)[i + 1] != '\'' */)
		{
			get_allias(command, &i);
			triger = 1;
		}
		if  ((*command)[i])
			++i;
	}
	return (triger);
}

/*
**	Splite en fonction du séparateur,
**	sauf s'il y a des guillemets
*/

char	**ft_split_unless_quote(char *line, char *sep)
{
	char *command;
	char **dest;

	command = ft_strtrim(line, sep);
	dest = malloc((ft_len_split_unless_quote(command, sep) + 1) * 8);
	dest = ft_extract_sep_quote(dest, command, sep);
	free(command);
	return (dest);
}
