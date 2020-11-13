/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 03:56:24 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 05:43:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void process_simple_quote(char **cmd)
{
	int i;

	i = -1;
	while ((*cmd)[++i])
		if ((*cmd)[i] == '\'')
			ft_get_rid(cmd, i);
}

void process_double_quote(char **cmd)
{
	int i;

	i = -1;
	while ((*cmd)[++i])
		if ((*cmd)[i] == '\"')
			ft_get_rid(cmd, i);
}

int process_quote(char **cmd)
{
	int i;

	i = -1;
	while ((*cmd)[++i])
		if ((*cmd)[i] == '\'')
			process_simple_quote(&(*cmd)[i]);
		if ((*cmd)[i] == '\"')
			process_double_quote(cmd);
	return (0);
}