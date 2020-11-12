/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:58:02 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 16:20:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static inline int	i_love_the_norm(void)
{
	return (!ft_error("minishell", strerror(errno), ft_strdup("|"), STAY));
}

/*
** Créée les pipes et lance les commandes après avoir
** remplacé stdin et stdout
** Subtilité: il faut fermer tous les pipes précédents!
*/

int					redir_node(t_cmd *cmd, pid_t *pid, int i)
{
	pipe(cmd->pipes);
	pid[i] = fork();
	if (pid[i] == -1)
		return (!ft_error("minishell", strerror(errno), "fork", EXIT));
	if (pid[i] == 0)
	{
		close_pipe_before(cmd);
		if (cmd->previous && dup2(cmd->previous->pipes[0], 1) < 0)
			return (i_love_the_norm());
		if (cmd->next && dup2(cmd->pipes[1], STDOUT_FILENO) < 0)
			return (i_love_the_norm());
		ft_chevron(&(cmd->cmds));
		if ((close(cmd->pipes[1]) < 0))
			return (i_love_the_norm());
		if (cmd->previous && (close(cmd->previous->pipes[0]) < 0))
			return (i_love_the_norm());
		exit(g_status >> 8);
	}
	return (0);
}

/*
** Renvoie vers redir_node sur tous les t_cmd
** Ferme les pipes à la fin
*/

int					redir_cmds(t_cmd *head)
{
	t_cmd	*current;
	pid_t	*pid;
	int		i;

	i = -1;
	current = head;
	pid = malloc(len_cmd(head) * sizeof(pid_t));
	if (!(current->next))
		return (ft_chevron(&(current->cmds)));
	while (current)
	{
		++i;
		redir_node(current, pid, i);
		current = current->next;
	}
	i = -1;
	close_pipe(head);
	while (++i < len_cmd(head))
		waitpid(pid[i], &g_status, WUNTRACED);
	return (0);
}

/*
** Copie les commandes de begin à end
*/

char				**set_cmds(char **commands, int begin, int end)
{
	int		i;
	char	**dest;

	i = begin;
	if (!(dest = malloc((end - begin + 1) * sizeof(char*))))
		ft_error("minishell", strerror(errno), ft_strdup(""), EXIT);
	while (++i < end && commands[i])
		dest[i - begin - 1] = ft_strdup(commands[i]);
	dest[i - begin - 1] = NULL;
	return (dest);
}

/*
** Découpe les commandes en fonction des pipes
** et les répartit dans une liste
*/

t_cmd				*ft_split_pipe(char **commands)
{
	int		i;
	int		prev;
	t_cmd	*current;
	t_cmd	*head;

	i = -1;
	prev = -1;
	head = malloc(sizeof(struct s_cmd));
	current = head;
	head->previous = NULL;
	while (commands[++i])
	{
		if (!ft_strcmp(commands[i], "|"))
		{
			current->cmds = set_cmds(commands, prev, i);
			prev = i;
			current->next = malloc(sizeof(struct s_cmd));
			current->next->previous = current;
			current = current->next;
		}
	}
	current->cmds = set_cmds(commands, prev, i);
	current->next = NULL;
	return (head);
}
