/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:56:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/06/02 21:25:16 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		return (xclose(&fd[0]), xclose(&fd[1]), 1);
	if (pid == 0)
	{
		restore_original_signals(all);
		xclose(&fd[0]);
		clean_exit(all, loop_heredoc(all, (*tok), fd));
	}
	ret = wait_heredoc(all, pid, fd);
	if (ret)
		return (ret);
	if (cmd->fd_in != 0)
		xclose(&cmd->fd_in);
	return (cmd->fd_in = fd[0], 0);
}
/*
	this fonction handles the heredoc setup, creates a pipe,
	forks a child process, and reads input until the delimiter is met
*/

int	loop_here_quotes(t_token *delim, int *fd)
{
	char	*rl;
	char	*line;

	while (1)
	{
		rl = readline("> ");
		if (!rl)
			return (ft_putstr_fd("minishell: warning: heredoc EOF\n", 2), 0);
		if (!ft_compare(rl, delim->value))
			return (free(rl), 0);
		line = ft_strjoin(rl, "\n");
		if (!line)
			return (1);
		free(rl);
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	return (0);
}

int	loop_heredoc(t_all *all, t_token *delim, int *fd)
{
	char	*rl;
	char	*expanded;
	char	*line;

	if (delim->had_quotes == TRUE)
		return (loop_here_quotes(delim, fd));
	while (1)
	{
		rl = readline("> ");
		if (!rl)
			return (ft_putstr_fd("minishell: warning: heredoc EOF\n", 2), 0);
		if (!ft_compare(rl, delim->value))
			return (free(rl), 0);
		expanded = expand_in_str(rl, all, 0);
		free(rl);
		line = ft_strjoin(expanded, "\n");
		free(expanded);
		if (!line)
			return (1);
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	return (0);
}
/*
	this fonction reads standard input using readline
	until it matches the delimiter or reaches EOF
*/

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
/*
	this fonction waits for the heredoc child process to finish
	and properly handles signals like SIGINT during the prompt
*/
