#ifndef INCLUDE_H
#define INCLUDE_H

#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "printf.h"
#include "get_next_line_bonus.h"

typedef struct s_list_cmd {
	char				*cmd;
	char				**arg;
	struct s_list_cmd	*next;
}				t_list_cmd;

/* 
** alloc_n_erase.c
*/

void erase_db_char_ptr(char ***cmds);

void erase_lst(t_list_cmd *lst);

t_list_cmd *ft_lstnew_cmd(void *content);

t_list_cmd *new_lst_of_cmds(char **cmds);

void erase_main_materials(t_list_cmd *lst, char ***cmds, char *cmdl);




/* 
** Copie de minishell.h
*/

# define BEFORE 0
# define AFTER 1
# define EXIT 10
# define STAY 11

typedef	struct	s_cmd
{
	char			**cmds;
	int				pipes[2];
	struct s_cmd	*next;
	struct s_cmd	*previous;

}				t_cmd;

char			**g_envv;

int				g_status;

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

void			set_env(char **env);

int				ft_print_env(char **env, int trie);

char			*find_key(char *key);

int				ft_pwd(void);

/*
**error.c
*/

int				ft_error(char *proc, char *mess, char *command, int out);

/*
**export_unset
*/

int				ft_add_envv(char *command);

int				ft_export(char *command, char **var);

int				ft_destroy(int i);

int				ft_unset(char *command);

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

int				ft_parse_exec(char *exec, char **commands, char **dir);

int				parse_child(char **commands);

/*
**prompt.c
*/

void			ft_prompt(void);

/*
**redir.c
*/

int				ft_syntax_error(char **commands);

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
**Split_pipe
*/

int				redir_node(t_cmd *cmd, pid_t *pid, int i);

int				redir_cmds(t_cmd *head);

char			**set_cmds(char **commands, int begin, int end);

t_cmd			*ft_split_pipe(char **commands);

/*
**t_cmd
*/

int				len_cmd(t_cmd *head);

int				close_pipe_before(t_cmd *cmd);

int				close_pipe(t_cmd *head);

/*
**toolbox.c
*/

int				file_transfer(int fds, int fdd);

char			*ft_strjoin_sep(char *str1, char *str2, char *sep);

void			ft_get_rid(char **src, int pos);

/*
**toolbox2.c
*/

int				ft_free_split(char **commands);

char			**set_new_commands(char **commands, int i, int pos);

int				ft_strlen_vec(char **vec);

int				has_redir(char **command, int pos);

void			print_vec(char **vec);

/*
*** toolbox3.c
*/

int				is_redir(char *str);

int				get_rid_cmd(char ***cmd, int beg, int end);

int				ft_syntax_error(char **commands);

/*
** parsing/parsing_part1.c
*/

int				check_set(char c, char *set);

int				get_new_cmdl(char **cmdl);

void			print_3d_vec(char ***vec);

void			destroy_3d_vec(char ***vec);

char			***parse_cmdl(char *cmdl);

/*
** toolbox5.c
*/

int				verify_duplicate_token_in_cmdl(char *cmdl);

#endif