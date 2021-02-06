/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:57:28 by adtheus           #+#    #+#             */
/*   Updated: 2021/02/04 17:14:47 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
** Cherche si un des charactères de première chaine est ds l'autre
*/

int		ft_chr_char_of_str1_in_str2(char *str1, char *str2)
{
	int i;

	while (*str2 && !(i = 0))
	{
		while (str1[i])
		{
			if (str1[i] == *str2)
				return (1);
			++i;
		}
		++str2;
	}
	return (0);
}