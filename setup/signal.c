/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:02 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/23 17:16:32 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
**Associe les fonctions ft_handle_signal ou
**ft_handle_signal_child aux signaux SIGINT et SIGQUIT
*/

void	signal_set_up(void (*ft_handler)(int))
{
	signal(SIGINT, *ft_handler);
	signal(SIGQUIT, *ft_handler);
}

/*
**n'affiche pas de prompt, s'appelle au sein du child
*/

void	ft_handle_signal_child(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		write(1, "\n", 1);
		signal(SIGINT, ft_handle_signal_child);
	}
	if (signum == SIGQUIT)
	{
		g_status = 131;
		write(1, "Quit: 3\n", 8);
		signal(SIGQUIT, ft_handle_signal_child);
	}
}

/*
**réaffiche le prompt, et retour au process de minishell
*/

void	ft_handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130 << 8;
		g_cant_quit = 0;
		write(1, "\n", 1);
		ft_prompt();
		signal(SIGINT, ft_handle_signal);
	}
	if (signum == SIGQUIT)
	{
		g_status = 131 * 256;
		signal(SIGQUIT, ft_handle_signal);
	}
}

/*
**S'utilise si un ctrl-D est détecté (pas un signal à proprement parler)
*/

int		ft_eof(void)
{
	ft_free_split(g_envv);
	write(1, "\n", 1);
	write(1, "\r", 1);
	write(1, "exit\n", 5);
	exit(0);
	return (0);
}

/*
**Change la variable globale g_status
**dans le process père si un signal a été détecté
*/

void	ft_status_handler(void)
{
	if (WIFSIGNALED(g_status))
	{
		if (WTERMSIG(g_status) == 2)
			g_status = 130 * 256;
		if (WTERMSIG(g_status) == 3)
			g_status = 131 * 256;
	}
}
