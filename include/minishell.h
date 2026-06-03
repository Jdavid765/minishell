/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* minishell.h                                        :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/02/16 17:14:40 by canoduran         #+#    #+#             */
/* Updated: 2026/05/19 11:21:00 by minishell        ###   ########.fr       */
/* */
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
	bool			had_quotes;
	bool			space_after;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct	s_parser
{
	char			**cmd_and_args;
	char			*path;
	int				fd_in;
	int				fd_out;
	bool			is_builtin;
	bool			access_check;
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
/*                                CORE                                        */
/* ========================================================================== */
/*main.c*/
int			main_loop(t_all *all);
/*setup.c*/
int			setup(t_all *all, char **env);
/*signal.c*/
void		sigint_handler(int signum);
int			setup_signal(t_all *all);
void		restore_original_signals(t_all *all);
void		init_original_signals(t_all *all);
void		ignore_signals(void);

/* ========================================================================== */
/*                                BUILTINS                                    */
/* ========================================================================== */
/*cd_builtin.c */
int			cd_builtin(t_all *all, t_parser *cd_cmd);
int			go_to_home_dir(t_all *all);
int			update_env(t_all *all);
t_env		*find_pwd_node(t_all *all);
t_env		*find_oldpwd_node(t_all *all);
/*cd_utils*/
int			create_pwd_node(t_all *all, char *new_cwd);
/*echo_builtin.c*/
int			is_n_option(char *arg);
void		echo_builtin(t_parser *cmd);
/*env_builtin.c*/
void		cmd_env(t_all *all);
int			create_path(t_env **ft_env);
int			check_path(t_env **ft_env);
/*exit_builtin.c*/
void		exit_builtin(t_all *all, t_parser *cmd);
int			is_numeric(char *str);
/*export_builtin.c*/
void		print_export(t_all *all);
int			add_or_update(t_all *all, char *arg);
int			export_builtin(t_all *all, t_parser *cmd);
/*export_utils.c*/
int			append_node(t_all *all, char *key, char *value);
int			update_existing(t_all *all, char *key, char *value, char *arg);
int			parse_arg(char *arg, char **key, char **value);
int			is_valid_arg(char *key);
/*pwd_builtin.c*/
int			pwd_builtin(t_all *all);
/*unset_builtin.c*/
void		remove_env_node(t_env **head, char *key);
int			unset_builtin(t_all *all, t_parser *cmd);

/* ========================================================================== */
/*                                EXEC                                        */
/* ========================================================================== */
/*exec.c*/
void		executor(t_all *all);
int			count_cmds(t_parser *cmd_list);
void		check_dir_and_perm(t_all *all, char *cmd);
void		check_exec_error(t_all *all, char *cmd);
/*exec_builtins.c */
int			is_builtin(char *cmd);
void		exec_builtin(t_all *all, t_parser *cmd);
void		exec_single_builtin(t_all *all, t_parser *cmd);
/*exec_fds.c */
void		manage_parent_fds(t_parser *cmd, int *prev_read_fd, int *pipefd);
void		setup_pipe_fds(t_parser *cmd, int prev_read_fd, int *pipefd);
void		apply_redirections(t_all *all, t_parser *cmd);
/*exec_path.c*/
char		*before_path_check(t_env *env, char *cmd);
char		*path_check(t_env *env, char *cmd);
char		*path_exist(char **all_path, char *path);
char		*access_check(char *all_path, char *path);
char		*find_path_in_env(t_env *env);
/*exec_pipeline.c*/
void		exec_pipeline(t_all *all);
void		child_pipeline(t_all *all, t_parser *cmd, int prev_fd, int *p_fd);
void		execute_pipeline_cmd(t_all *all, t_parser *cmd);
void		wait_pipeline(pid_t last_pid);
/*exec_simple.c*/
void		exec_single_cmd(t_all *all);
void		exec_single_external(t_all *all, t_parser *cmd);
void		child_single_external(t_all *all, t_parser *cmd);
void		parent_single_external(t_parser *cmd, pid_t pid);

/* ========================================================================== */
/*                                ENV                                         */
/* ========================================================================== */
/*env_init.c*/
t_env		*ft_node_env(char *key, char *value);
int			setup_env(t_all *all, char **env);
int			create_env(t_all *all);
int			search_pwd(t_env **head);
int			create_shlvl(t_env **head);
int			create_path_no_env(t_env **head);
void		ft_add_back_env(t_env **head, t_env *new);
void		ft_lst_del_env(t_env *ft_env);
void		look_env(t_all *all);
/*env_utils.c*/
int			ct_key_value(char *env);
char		*put_in_key(char *env);
char		*put_in_value(char *env);
int			shlvl_add(t_env **ft_env);
/*rebuild_env.c*/
char		**re_build_env(t_env *head, char **new_env);
char		*join_env_value(t_env *current);
int			count_env_list(t_env *head);

/* ========================================================================== */
/*                             EXPANSION                                      */
/* ========================================================================== */
/*expander_quotes.c*/
int			quotes(t_token *token, t_all *all);
int			double_quote(t_token *token, t_all *all);
int			single_quote(t_token *token);
/*expander_split.c*/
int			split_expanded_token(t_token *curr_node, char *expanded_str);
int			insert_split_words(t_token *curr_node, char **words, t_token *next_save, bool orig_space);
/*expander_utils.c*/
char		*expand_in_str(char *str, t_all *all, int i);
char		*get_var_value(char *dollar, t_all *all, int *i);
char		*in_env(char *line, t_all *all);
char		*strip_quotes(char *str);
void		free_expand(char *tmp, char *value, char *before);
/*expender.c */
int			check_exp_var(t_all *all);
int			check_sign(t_token *token, t_all *all);
int			check_dollar(t_token *token, t_all *all);

/* ========================================================================== */
/*                                LEXER                                       */
/* ========================================================================== */
/*lexer.c*/
int			tokenizer(char *user_input, t_all *all);
void		join_adjacent_tokens(t_all *all);
/*lexer_handlers.c*/
int			find_by_char(char *user_input, int *i, t_all *all);
int			new_word_or_cmd(char *user_input, int *start, t_all *all);
int			new_pipe(char *user_input, int *start, t_all *all);
int			is_a_separator(char letter);
/*lexer_nodes.c*/
t_token		*create_token_node(t_token_type type, char *val);
int			new_token_node(t_token **token_head, t_token_type type, char *token_val);
t_token		*last_token_list(t_token *token_head);
/*lexer_quotes.c*/
int			new_double_quote(char *user_input, int *start, t_all *all);
int			new_single_quote(char *user_input, int *start, t_all *all);
/*lexer_redir.c*/
int			new_redir_out_or_appnd(char *user_input, int *start, t_all *all);
int			new_appnd(char *user_input, int *start, t_all *all, int end);
int			new_redir_in_or_heredoc(char *user_input, int *start, t_all *all);
int			new_heredoc(char *user_input, int *start, t_all *all, int end);

/* ========================================================================== */
/*                                PARSER                                      */
/* ========================================================================== */
/*parser_heredoc.c*/
int			heredoc(t_all *all, t_parser *cmd, t_token **tok);
int			loop_heredoc(t_all *all, t_token *delim, int *fd);
int			wait_heredoc(t_all *all, pid_t pid, int *fd);
void		heredoc_child(t_all *all, t_token *tok, int *fd);
void		heredoc_sig_handler(int signum);
/*parser_nodes.c*/
t_parser	*ft_node_pars(char *path);
void		ft_addback_parse(t_parser **head, t_parser *new);
int			count_words(t_token *token);
/*parser_redirs.c*/
int			redir_in(t_parser *cmd, t_token **tok);
int			redir_out(t_parser *cmd, t_token **tok);
int			append(t_parser *cmd, t_token **tok);
/*parser_utils.c*/
int			ft_pipe(t_parser **cmd, t_token *tok, int *index, char *path);
char		*search_path(t_all *all);
char		*search_path_no_env(t_all *all);
/*parsing.c*/
int			parse_token(t_all *all);
int			parse_loop(t_parser **cmd, t_token *token, t_all *all);
int			all_else_if(t_parser **cmd, t_token **token, t_all *all, int *index);

/* ========================================================================== */
/*                                UTILS                                       */
/* ========================================================================== */
/*clean_core.c*/
void		clean_exit(t_all *all, int exit_code);
void		free_all(t_all *all);
void		free_tab(char **strs);
int			xclose(int *fd);
void		clean_loop(t_all *all);
/*clean_lists.c*/
void		clean_token_list(t_token *head);
int			clean_cmd_list(t_parser *head);
void		clean_env_list(t_env *head);
int			clean_parsing_list(t_parser *head);
void		clear_setup_env(char *key, char *value, t_env *head);
/*utils.c*/
int			ft_compare(char *rl, char *string);
int			*get_status(void);

#endif