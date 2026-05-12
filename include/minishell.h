/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:40 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/10 16:44:44 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

typedef enum	e_token_type
{
	WORD,
	PIPE,
	REDIR_IN, // <
	REDIR_OUT, // >
	APPEND, // >>
	HEREDOC // <<
}	t_token_type;

typedef struct	s_sig
{
	struct sigaction	sa;
	struct sigaction	sa_quit;
	struct sigaction	sa_orig_int;
	struct sigaction	sa_orig_quit;
}	t_sig;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	bool			is_valid;
	bool			space_after;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct	s_parser
{
	char	**cmd_and_args;
	char	*path;
	int		fd_in;
	int		fd_out;
	bool	is_builtin;
	bool	access_check;
	struct s_parser	*next;
}	t_parser;

typedef struct	s_all
{
	t_sig		sig;
	t_env		*env;
	t_token		*token;
	char		**env_for_exec;
	t_parser	*parser;
	char		*path;
}	t_all;


/* ========================================================================== */
/* ===============================parsing=====================================*/
/* ========================================================================== */
int		parse_token(t_all *all);
int		check_exp_var(t_all *all);
char	*search_path(t_all *path);
int		count_words(t_token *token);
int		ft_pipe(t_parser **cmd, t_token *tok, int *index, char *path);
int		redir_in(t_parser *cmd, t_token **tok);
int		append(t_parser *cmd, t_token **tok);
int		all_else_if(t_parser **cmd, t_token **token, char *path, int *index);
int		split_expanded_token(t_token *curr_node, char *expanded_str);
int		insert_split_words(t_token *curr_node, char **words, t_token *next_save, bool orig_space);
void	join_adjacent_tokens(t_all *all);

/* ========================================================================== */
/* ===============================exec========================================*/
/* ========================================================================== */
char		*before_path_check(t_env *env, char *cmd);
char		*path_check(t_env *env, char *cmd);
char		*path_exist(char **all_path, char *path);
char		*access_check(char *all_path, char *path);
char		*find_path_in_env(t_env *env);
char		**re_build_env(t_env *head, char **new_env);
char		*join_env_value(t_env *current);
int			count_env_list(t_env *head);
void		executor(t_all *all);
int			count_cmds(t_parser *cmd_list);
void		exec_single_cmd(t_all *all);
void		exec_pipeline(t_all *all);
void		apply_redirections(t_parser *cmd);
void		child_single_external(t_all *all, t_parser *cmd);
void		parent_single_external(t_parser *cmd, pid_t pid);
int			is_builtin(char *cmd);
void		exec_builtin(t_all *all, t_parser *cmd);
void		exec_single_builtin(t_all *all, t_parser *cmd);
void		exec_single_external(t_all *all, t_parser *cmd);
void		wait_pipeline(pid_t last_pid);
void		child_pipeline(t_all *all, t_parser *cmd, int prev_fd, int *p_fd);
void		manage_parent_fds(t_parser *cmd, int *prev_read_fd, int *pipefd);
void		setup_pipe_fds(t_parser *cmd, int prev_read_fd, int *pipefd);
void		execute_pipeline_cmd(t_all *all, t_parser *cmd);

/* ========================================================================== */
/* ===============================utils====================================== */
/* ========================================================================== */
int			ft_compare(char *rl, char *string);
int			*get_status(void);

/* ========================================================================== */
/* ===============================signal===================================== */
/* ========================================================================== */
int			setup_signal(t_all *all);
void		sigint_handler(int signum);
void		restore_original_signals(t_all *all);
void		ignore_signals(void);
void		init_original_signals(t_all *all);

/* ========================================================================== */
/* ===============================builtin==================================== */
/* ========================================================================== */
int			pwd_builtin(t_all *all);
void		exit_builtin(t_all *all, t_parser *cmd);
int			cd_builtin(t_all *all, t_parser *cd_cmd);
int			go_to_home_dir(t_all *all);
int			update_env(t_all * all);
t_env		*find_pwd_node(t_all * all);
t_env		*find_oldpwd_node(t_all * all);
void		echo_builtin(t_parser *cmd);
void		exit_builtin(t_all *all, t_parser *cmd);
int			is_numeric(char *str);
int			unset_builtin(t_all *all, t_parser *cmd);
int			export_builtin(t_all *all, t_parser *cmd);
int			is_valid_arg(char *key);
int			parse_arg(char *arg, char **key, char **value);
int			update_existing(t_all *all, char *key, char *value, char *arg);
int			append_node(t_all *all, char *key, char *value);

/* ========================================================================== */
/* ===============================cleaners=================================== */
/* ========================================================================== */
void		clean_token_list(t_token *head);
int			clean_cmd_list(t_parser *head);
void		clean_env_list(t_env *head);
int			clean_parsing_list(t_parser *head);
int			xclose(int *fd);
void		free_tab(char **strs);
void		clean_loop(t_all *all);
void		clean_exit(t_all *all, int exit_code);
void		free_all(t_all *all);

/* ========================================================================== */
/* ===============================tokenizer================================== */
/* ========================================================================== */
int			tokenizer(char *user_input, t_all *all);
int			new_token_node(t_token **token_head, t_token_type type, char *token_val);
t_token		*create_token_node(t_token_type type, char *val);
t_token		*last_token_list(t_token *token_head);
int			find_by_char(char *user_input, int *i, t_all *all);
int			new_word_or_cmd(char *user_input, int *start, t_all *all);
int			new_single_quote(char *user_input, int *start, t_all *all);
int			new_double_quote(char *user_input, int *start, t_all *all);
int			new_pipe(char *user_input, int *start, t_all *all);
int			new_redir_in_or_heredoc(char *user_input, int *start, t_all *all);
int			new_heredoc(char *user_input, int *start, t_all *all, int end);
int			new_redir_out_or_appnd(char *user_input, int *start, t_all *all);
int			new_appnd(char *user_input, int *start, t_all *all, int end);
int			is_a_separator(char letter);

/* ========================================================================== */
/* =============================== PARSE_ENV================================= */
/* ========================================================================== */
int		setup_env(t_all *all, char **env);
void	cmd_env(t_all *all);
int		check_path(t_env **ft_env);
int		ct_key_value(char *env);
char	*put_in_key(char *env);
char	*put_in_value(char *env);
char	*search_path(t_all *all);
int		setup(t_all *all, char **env);
int		create_env(t_all *all);

/* ========================================================================== */
/* =============================== FUNCTIONS NODE============================ */
/* ========================================================================== */
t_env		*ft_node_env(char *key, char *value);
void		ft_add_back_env(t_env **head, t_env *new);
void		ft_lst_del_env(t_env *ft_env);
t_parser	*ft_node_pars(char *path);
void		ft_addback_parse(t_parser **head, t_parser *new);

/* ========================================================================== */
/* =============================== EXP_VARIABLES ============================ */
/* ========================================================================== */
int			setup(t_all *all, char **env);
int			main_loop(t_all *all);
int		check_dollar(t_token *token, t_all *all);
int		replace_dollar(t_token *token, t_all *all);
char	*expand_in_str(char *str, t_all *all);
char	*get_var_value(char *dollar, t_all *all, int *i);
char	*in_env(char *line, t_all *all);
char	*strip_quotes(char *str);
void	free_expand(char *tmp, char *value, char *before);
char	*search_path_no_env(t_all *all);

#endif