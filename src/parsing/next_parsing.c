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

int	loop_heredoc(char *rl, t_token *delim, char *line, int *fd)
{
	while (1)
	{
		rl = readline("> ");
		if (!rl)
			return (xclose(&fd[0]), xclose(&fd[1]), 1);
		if (rl[0] != '\0' && !ft_compare(rl, delim->value))
		{
			free(rl);
			break ;
		}
		line = ft_strjoin(rl, "\n");
		free(rl);
		rl = NULL;
		if (!line)
			return (xclose(&fd[0]), xclose(&fd[1]), 1);
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	return (0);
}

int	heredoc(t_parser *cmd, t_token **tok)
{
	char	*rl;
	char	*line;
	int		fd[2];
	int		ret;

	ret = 0;
	rl = NULL;
	line = NULL;
	(*tok) = (*tok)->next;
	if (!(*tok) || (*tok)->type != WORD)
		return (10);
	if (pipe(fd) < 0)
		return (1);
	ret = loop_heredoc(rl, (*tok), line, fd);
	if (ret)
		return (ret);
	xclose(&fd[1]);
	if (cmd->fd_in != 0)
		xclose(&cmd->fd_in);
	cmd->fd_in = fd[0];
	return (0);
}

int	all_else_if(t_parser **cmd, t_token **token, char *path, int *index)
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
		ret = ft_pipe(cmd, (*token), index, path);
	else if ((*token)->type == HEREDOC)
		ret = heredoc(*cmd, token);
	return (ret);
}
