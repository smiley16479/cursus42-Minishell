/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:34:50 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/10 22:08:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	**ft_alias_quote(char **commands)
{
	int i;

	i = -1;
	while (commands[++i])
		if (commands[i][0])
			commands[i] = set_alias(commands[i]);
	return (commands);
}
