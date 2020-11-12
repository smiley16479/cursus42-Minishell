/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:49:17 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 21:49:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Renvoie la taille de la liste
*/

int	len_cmd(t_cmd *head)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = head;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/*
** Ferme tous les pipes précédents
*/

int	close_pipe_before(t_cmd *cmd)
{
	t_cmd *current;

	current = cmd;
	if (!(current))
		return (-1);
	if ((close(current->pipes[0]) < 0))
		ft_error("minishell", strerror(errno), ft_strdup("|"), STAY);
	current = current->previous;
	if (!(current))
		return (0);
	if ((close(current->pipes[1]) < 0))
		ft_error("minishell", strerror(errno), ft_strdup("|"), STAY);
	while (current->previous != NULL)
	{
		current = current->previous;
		if ((close(current->pipes[0]) < 0))
			ft_error("minishell", strerror(errno), ft_strdup("|"), STAY);
		if ((close(current->pipes[1]) < 0))
			ft_error("minishell", strerror(errno), ft_strdup("|"), STAY);
	}
	return (0);
}

/*
** Ferme tous les pipes
*/

int	close_pipe(t_cmd *head)
{
	t_cmd *current;

	current = head;
	while (current != NULL)
	{
		if ((close(current->pipes[0]) < 0))
			ft_error("minishell", strerror(errno), ft_strdup("|"), STAY);
		if ((close(current->pipes[1]) < 0))
			ft_error("minishell", strerror(errno), ft_strdup("|"), STAY);
		current = current->next;
	}
	return (0);
}
