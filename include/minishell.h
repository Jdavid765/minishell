/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:40 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 14:48:45 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
#include <stdbool.h>
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

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN, // <
	REDIR_OUT, // >
	APPEND, // >>
	HEREDOC // <<
}	t_token_type;

typedef struct s_sig
{
	struct sigaction sa;
}	t_sig;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_parsing
{
	char	**cmd_arg;
	int		fd_in;
	int		fd_out;
	struct s_parsing	*next;
}	t_parsing;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	bool			is_valid;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char	**cmd_and_args;
	char	*path;
	int		fd_in;
	int		fd_out;
	bool	is_builtin;
	bool	access_check;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_all
{
	t_sig	sig;
	t_env	*env;
	t_token	*token;
	t_cmd	*cmd;

}	t_all;


/* ========================================================================== */
/* ===============================parsing=====================================*/
/* ========================================================================== */
// t_parsing	*ft_parsing(char *rl);

/* ========================================================================== */
/* ===============================exec========================================*/
/* ========================================================================== */

/* ========================================================================== */
/* ===============================utils=======================================*/
/* ========================================================================== */
int		ft_compare(char *rl, char *string);
void	check_cmd(char *rl, t_all *all);

/* ========================================================================== */
/* ===============================signal======================================*/
/* ========================================================================== */
int			setup_signal(t_all *all);
void		sigint_handler(int signum);


/* ========================================================================== */
/* ===============================builtin=====================================*/
/* ========================================================================== */
int		pwd_builtin(void);
void	exit_builtin(void *data);
int		export_builtin(t_all *all, char *rl);
int		cd_builtin(t_all *all, t_cmd *cd_cmd, char *rl);//enlver char *rl
int		update_env(t_all * all);
t_env	*find_pwd_node(t_all * all);
t_env	*find_oldpwd_node(t_all * all);

/* ========================================================================== */
/* ===============================cleaners====================================*/
/* ========================================================================== */
void	clean_token_list(t_token *head);
int		clean_cmd_list(t_cmd *head);
void	clean_env_list(t_env *head);
int		clean_parsing_list(t_parsing *head);
int		xclose(int *fd);
void	free_tab(char **strs);

/* ========================================================================== */
/* ===============================tokenizer===================================*/
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
/* =============================== PARSE_ENV==================================*/
/* ========================================================================== */
int		setup_env(t_all *all, char **env);
void	cmd_env(t_all *all);

/* ========================================================================== */
/* =============================== FUNCTIONS NODE=============================*/
/* ========================================================================== */
t_env	*ft_node_env(char *key, char *value);
void	ft_add_back_env(t_env **head, t_env *new);
void	ft_lst_del_env(t_env *ft_env);

/* ========================================================================== */
/* =============================== ===========================================*/
/* ========================================================================== */
int			setup(t_all *all, char **env);

#endif