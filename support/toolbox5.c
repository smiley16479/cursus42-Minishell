/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 00:42:28 by adrien            #+#    #+#             */
/*   Updated: 2020/11/14 00:55:33 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int is_token(int c)
{
	char *token = "|><;";

	while (*token)
		if (c == *token++)
			return (1);
	return (0);
}

/* 
** is_spaces_inbetween_token
*/

int	is_two_token(char **cmdl)
{
	if (is_token(**cmdl))
	{
		++*cmdl;
		if (**cmdl == '>')
			++*cmdl;
		while (ft_isspace(**cmdl))
			++*cmdl;
		if (is_token(**cmdl))
			return (1);
	}
	return (0);
}

int	skip_apostrophy(char **cmdl)
{
	if (**cmdl == '\"' || **cmdl == '\'')
	{
		if (**cmdl == '\"' && ++*cmdl)
			while (**cmdl && **cmdl != '\"')
				++*cmdl;
		if (**cmdl == '\'' && ++*cmdl)
			while (**cmdl && **cmdl != '\'')
				++*cmdl;
		if (**cmdl == '\'' || **cmdl == '\"')
		{
			++*cmdl;
			return (0);
		}
		else if (**cmdl == '\0')
			return (0);		
		return (1);
	}
	return (0);
}

int	verify_duplicate_token_in_cmdl(char *cmdl)
{
	while (*cmdl)
	{
		if (skip_apostrophy(&cmdl) || is_two_token(&cmdl))
			return (!ft_error("Bash", "Token", "bad syntaxt", STAY));
		if (*cmdl && *cmdl != '\'' && *cmdl != '\"')
			++cmdl;
	}
	return (0);
}

/* int main(void)
{
	char *str1 = "'|| ef'f 'fd 's>> '\"";

	char error;
	if ((error = verify_duplicate_token_in_cmdl(str1)))
		printf("erreur près du symbole :%c\n", error);
	return (0);
} */