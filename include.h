/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:45:33 by user42            #+#    #+#             */
/*   Updated: 2020/11/23 17:16:32 by adtheus          ###   ########.fr       */
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

enum	e_standar {in, out};

/*
** Copie de minishell.h
*/

# define BEFORE 0
# define AFTER 1
# define EXIT 10
# define STAY 11

char			**g_envv;

char			**g_endtab;

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

char			*copy_word(char *line, int prev, int i);

char			**ft_extract_sep_quote(char **dest, char *command, char *sep);

char			**ft_split_unless_quote(char *line, char *sep);

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

/*
**toolbox2.c
*/

int				ft_free_split(char **commands);

int				ft_strlen_vec(char **vec);

/*
*** toolbox3.c
*/

int				is_redir(char *str);

t_bool			which_redir(char *str);

int				get_rid_cmd(char ***cmd, int beg, int end);

int				get_rid_cmd_bis(char **cmd, int beg, int end);

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

void			parse_cmd(char **cmd);

int				process_db_quote(char **cmd, int *i);

void			process_simple_quote(char **cmd, int *i);

/*
** parsing/parsing_part3.c
*/

void			process_redir(char **cmd);

/*
** parsing/parsing_part4.c
*/

void			execution(char **cmd);

void			loop_pipe(char **cmd, int *i_l_t_n);

/*
** toolbox4.c
*/

int				verify_duplicate_token_in_cmdl(char *cmdl);

#endif
