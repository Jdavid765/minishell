/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 23:16:27 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/02 00:00:42 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_out(t_parser *cmd, t_token **tok)
{
	(*tok) = (*tok)->next;
	if (!(*tok) || (*tok)->type != WORD)
		return (10);
	if (cmd->fd_out != 1)
		xclose(&cmd->fd_out);
	cmd->fd_out = open((*tok)->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
		return (1);
	return (0);
}

int	loop_heredoc(t_token *delim, int *fd)
{
	char	*rl;
	char	*line;

	while (1)
	{
		rl = readline("> ");
		if (!rl)
		{
			ft_putstr_fd("minishell: warning: here-doc delimited by EOF\n", 2);
			break ;
		}
		if (!ft_compare(rl, delim->value))
		{
			free(rl);
			break ;
		}
		line = ft_strjoin(rl, "\n");
		free(rl);
		if (!line)
			return (1);
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	return (0);
}

int	wait_heredoc(t_all *all, pid_t pid, int *fd)
{
	int	status;

	xclose(&fd[1]);
	waitpid(pid, &status, 0);
	setup_signal(all);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		*get_status() = 130;
		return (xclose(&fd[0]), 130);
	}
	return (0);
}

int	heredoc(t_all *all, t_parser *cmd, t_token **tok)
{
	int		fd[2];
	pid_t	pid;
	int		ret;

	(*tok) = (*tok)->next;
	if (!(*tok) || (*tok)->type != WORD)
		return (10);
	if (pipe(fd) < 0)
		return (1);
	ignore_signals();
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		restore_original_signals(all);
		xclose(&fd[0]);
		exit(loop_heredoc((*tok), fd));
	}
	ret = wait_heredoc(all, pid, fd);
	if (ret)
		return (ret);
	if (cmd->fd_in != 0)
		xclose(&cmd->fd_in);
	return (cmd->fd_in = fd[0], 0);
}

int	all_else_if(t_parser **cmd, t_token **token, t_all *all, int *index)
{
	int	ret;

	ret = 0;
	if ((*token)->type == WORD)
	{
		if ((*token)->is_valid == true)
			(*cmd)->cmd_and_args[(*index)++] = ft_strdup((*token)->value);
	}
	else if ((*token)->type == REDIR_OUT)
		ret = redir_out(*cmd, token);
	else if ((*token)->type == APPEND)
		ret = append(*cmd, token);
	else if ((*token)->type == REDIR_IN)
		ret = redir_in(*cmd, token);
	else if ((*token)->type == PIPE)
		ret = ft_pipe(cmd, (*token), index, all->path);
	else if ((*token)->type == HEREDOC)
		ret = heredoc(all, *cmd, token);
	return (ret);
}
