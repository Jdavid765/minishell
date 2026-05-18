/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 23:16:27 by canoduran         #+#    #+#             */
/*   Updated: 2026/05/18 23:06:54 by canoduran        ###   ########.fr       */
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

int	loop_heredoc_quotes(char *rl, t_token *delim, char *line, int *fd)
{
	char	*new_delim;

	new_delim = strip_quotes(delim->value);
	while (1)
	{
		rl = readline("q> ");
		if (!rl)
			return (xclose(&fd[0]), xclose(&fd[1]), 1);
		if (rl[0] != '\0' && !ft_compare(rl, new_delim))
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

int	loop_heredoc(char *rl, t_token *delim, char *line, int *fd, bool quotes, t_all *all)
{
	char	*tmp;

	if (quotes == TRUE)
	{
		if (loop_heredoc_quotes(rl, delim, line, fd) == 1)
			return (1);
		return (0);
	}
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
		tmp = expand_in_str(rl, all);
		line = ft_strjoin(tmp, "\n");
		free(rl);
		free(tmp);
		rl = NULL;
		if (!line)
			return (xclose(&fd[0]), xclose(&fd[1]), 1);
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	return (0);
}

int	heredoc(t_parser *cmd, t_token **tok, t_all *all)
{
	char	*rl;
	char	*line;
	int		fd[2];
	int		ret;
	bool	quotes;

	ret = 0;
	rl = NULL;
	line = NULL;
	quotes = FALSE;
	(*tok) = (*tok)->next;
	if (!(*tok) || (*tok)->type != WORD)
		return (10);
	if (pipe(fd) < 0)
		return (1);
	if ((*tok)->value[0] == '"' || (*tok)->value[0] == '\'')
		quotes = TRUE;
	ret = loop_heredoc(rl, (*tok), line, fd, quotes, all);
	if (ret)
		return (ret);
	xclose(&fd[1]);
	if (cmd->fd_in != 0)
		xclose(&cmd->fd_in);
	cmd->fd_in = fd[0];
	return (0);
}

int	else_if(t_parser **cmd, t_token **token, char *path, int *index, t_all *all)
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
		ret = heredoc(*cmd, token, all);
	return (ret);
}
