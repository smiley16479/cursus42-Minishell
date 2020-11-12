/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:32:49 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/10 21:52:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	ft_echo_n(char **command, int *i)
{
	int j;
	int n;

	n = 0;
	if (command[*i] && command[*i + 1])
	{
		while ((command[*i + 1]) && ft_strncmp(command[*i + 1], "-n", 2) == 0)
		{
			j = 2;
			while (command[*i + 1][j] != 0 && command[*i + 1][j] == 'n')
				j++;
			if (command[*i + 1][j] == 0)
				n = 1;
			else
				return (n);
			(*i)++;
		}
	}
	return (n);
}

int	ft_echo(char **command)
{
	int n;
	int i;

	i = 0;
	n = ft_echo_n(command, &i);
	while (command[++i])
	{
		write(1, command[i], ft_strlen(command[i]));
		if (command[i + 1])
			write(1, " ", 1);
	}
	if (!(n))
		write(1, "\n", 1);
	return (0);
}
