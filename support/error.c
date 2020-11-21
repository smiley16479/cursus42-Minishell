/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:33:10 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/20 16:11:42 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	ft_error(char *proc, char *mess, char *command, int out)
{
	write(2,"\e[0;31m", 7);
	write(2, proc, ft_strlen(proc));
	write(2, ": ", 2);
	write(2, mess, ft_strlen(mess));
	write(2, ": ", 2);
	write(2, command, ft_strlen(command));
	write(2, "\n", 1);
	write(2,"\e[0m", 4);
	if (out == EXIT)
	{
		free(command);
		ft_free_split(g_envv);
		exit(0);
	}
	return (0);
}
