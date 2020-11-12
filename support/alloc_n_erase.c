#include "include.h"

/* 
**  efface un double tableau de char
*/

void erase_db_char_ptr(char ***cmds)
{
	int i;
	
	i = -1;
	if (*cmds && **cmds)
		while ((*cmds)[++i])
			free((*cmds)[i]);
	free(*cmds);
	*cmds = NULL;
}

/* 
**  efface une liste sans ses membres
*/

void erase_lst(t_list_cmd *lst)
{
	t_list_cmd *tmp;
	while (lst)
	{
		tmp = lst->next;
		free(lst->cmd);
		erase_db_char_ptr(&lst->arg);
		free(lst);
		lst = tmp;
	}
}

/* 
**  ahoute un élement à une liste chainée, en affectant à ce premier
**  le contenu passé en paramètre sur som membre list->cmd;
*/

t_list_cmd *ft_lstnew_cmd(void *content)
{
	t_list_cmd *to_return;
	if (!(to_return = malloc(sizeof(t_list_cmd))))
		return (NULL);
	to_return->cmd = content;
	to_return->arg = NULL;
	to_return->next = NULL;
	return (to_return);
}


/* 
**  transfère un tableau de chaines terminé par NULL
**  vers une liste chainée terminée par NULL
*/

t_list_cmd *new_lst_of_cmds(char **cmds)
{
	t_list_cmd *lst[2];
	
	if (!(lst[0] = malloc(sizeof(t_list_cmd))))
			return (write(1, "malloc_failled\n", 15), NULL);
	lst[1] = lst[0];
	while(*cmds)
	{
		lst[0]->arg = NULL;
		lst[0]->cmd = ft_strdup(*cmds++);
		if (*cmds)
		{
			if (!(lst[0]->next = malloc(sizeof(t_list_cmd))))
				return (write(1, "malloc_failled\n", 15), NULL);
		}
		else 
			lst[0]->next = NULL;
		lst[0] = lst[0]->next;
	}
	return (lst[1]);
}

void erase_main_materials(t_list_cmd *lst, char ***cmds, char *cmdl)
{
	erase_lst(lst);
	erase_db_char_ptr(cmds);
	free(cmdl);
}