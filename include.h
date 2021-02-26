/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:45:33 by user42            #+#    #+#             */
/*   Updated: 2021/02/25 21:01:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>

enum			e_standar {in, out};

/*
** typ & 0x01	-> sp_quote
** typ & 0x02	-> db_quote
** typ & 0x10	-> acollé à la prochaine portion de texte
** typ & 0x20	-> fin de la commande
*/

# define SPQUOTE	0x01
# define DBQUOTE	0x02
# define FINAL_END	0x04
# define VAR_TYP	0x08
# define STICKY_A	0x10
# define CMDEND		0x20
# define BAD_CHEV	0x40
# define STICKY_B	0x80

typedef struct	s_parse
{
	char			typ;
	char			*cont;
	struct s_parse	*prev;
	struct s_parse	*next;
}				t_parse;

# define EXIT 10
# define STAY 11

char			**g_envv;

int				g_status;

int				g_cant_quit;

typedef char	t_bool;

/*
**alias_quote.c
*/

int				double_quote(char **command, int *k);

char			*alias_envv(char *command);

void			handle_alias(char **command, int i);

char			*set_alias(char *command);

char			**ft_alias_quote(char **commands);

/*
**check_built_in.c
*/

int				ft_check_built_in(char **commands);

/*
**echo.c
*/

int				ft_echo(char **commands);

/*
**env_pwd.c
*/

char			**ft_cut_export_var(char *str, char delim);

void			set_env(char **env);

int				ft_print_env(char **env, int trie);

char			*find_key(char *key);

int				ft_pwd(void);

/*
**error.c
*/

int				ft_error(char *proc, char *mess, char *command, int out);

/*
** ft_export.c
*/

int				ft_add_envv(char *command);

int				ft_export_error(char *command, char **var);

int				ft_export(char **var);

/*
** ft_unset.c
*/

int				ft_destroy(int i);

int				ft_unset(char **variables, int i, int j);

/*
**export_support
*/

void			write_export_msg(char *str, int trie);

void			ft_swap_db_char_ptr(char **ptr1, char **ptr2);

/*
**ft_cd.c
*/

int				ft_cd(char *path);

/*
**main.c
*/

int				ft_parse(char **commands);

int				ft_parse_cmd(char **commands);

int				ft_empty_commands(char **commands);

/*
**parse_exec.c
*/

void			ft_execve(char *file, char **commands, char *exec);

char			*ft_parse_exec(char *exec, char **dir);

char			*parse_child(char **commands);

/*
**prompt.c
*/

void			ft_prompt(void);

/*
**redir.c
*/

int				ft_stdout(char ***commands, int *i);

int				ft_stdin(char ***commands, int *pos);

int				ft_chevron(char ***commands);

int				ft_redir(char **commands);

int				ft_pipe(char **commands, int i, int *status);

/*
**signal.c
*/

void			signal_set_up(void (*ft_handler)(int));

void			ft_handle_signal_child(int signum);

void			ft_handle_signal(int signum);

int				ft_eof(void);

void			ft_status_handler(void);

/*
**split_quote.c
*/

int				ft_len_split_unless_quote(char *line, char *set);

char			**ft_extract_sep_quote(char **dest, char *command, char *sep);

char			**ft_split_unless_quote(char *line, char *sep);

int				change_alias_if_not_in_quote(char **command);

/*
**split_redir.c
*/

int				is_pipe_followed(char *command);

char			**split_redir(char **commands);

/*
**toolbox1.c
*/

int				file_transfer(int fds, int fdd);

char			*ft_strjoin_sep(char *str1, char *sep, char *str2);

void			ft_get_rid(char **src, int pos);

void			ft_add_inside(char **dest, char *sep, int pos);

char			**construct_tab_from_ls(t_parse **ls, int i);

/*
**toolbox2.c
*/

int				ft_free_split(char **commands);

int				ft_strlen_vec(char **vec);

void			ft_add_vec_to_another
				(int *pos, char **to_add, char ***cmd, int join);

void			ft_add_cmd(int pos, char *to_add, char ***cmd);
/*
*** toolbox3.c
*/

int				is_redir(char *str);

int				get_rid_cmd(char **cmd, int beg, int end);

/*
*** toolbox4.c
*/

int				ft_is_char_in_str(char c, char *str1);

/*
** parsing/parsing_part1.c
*/

int				check_set(char c, char *set);

int				get_new_cmdl(char **cmdl);

char			***parse_cmdl(char *cmdl);

int				process_cmd(char **cmd);

/*
** parsing/parsing_part2.c
*/

t_parse			*parse_cmd(char **cmd);

void			process_db_quote(char **cmd, int *i, t_parse **elem);

void			process_simple_quote(char **cmd, int *i, t_parse **elem);

/*
** parsing/parsing_part3.c
*/

int				process_redir_ls(t_parse **ls);

/*
** parsing/parsing_part4.c
*/

void			execution(char **cmd);

void			execution_ls(t_parse **lst);

void			loop_pipe(char **cmd, int *i_l_t_n);

void			loop_pipe_ls(t_parse **ls, int *i_l_t_n);

/*
** toolbox4.c
*/

int				verify_duplicate_token_in_cmdl(char *cmdl);

t_parse			*t_parse_add(char typ, char *cont, t_parse *prev);

int				list_count(t_parse *to_count);

void			list_rewind(t_parse **elem);

void			list_destroy(t_parse *to_destroy);

t_parse			*list_elem_remove(t_parse *elem);

void			list_read(t_parse *to_read);

/*
** toolbox5.c
*/

void			get_variable_outside_quote_list
				(char typ, char *tmp, int k, t_parse **ls);

int				get_allias_outside_quote_list(char **cmd, int *i, t_parse **ls);

void			get_str(char **cmd, int *i, t_parse **parse);

int				get_variable(char **cmd, char *tmp, int *i, int j);

int				get_allias(char **cmd, int *i);

/*
*** toolbox6.c
*/

t_bool			which_redir(char *str);

char			*copy_word(char *line, int prev, int i);

void			set_valid_chevron(t_parse **ls, char **split_db);

#endif
