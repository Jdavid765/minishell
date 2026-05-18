/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 23:16:27 by canoduran         #+#    #+#             */
/*   Updated: 2026/05/18 23:37:02 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	heredoc_write(int *fd, t_token *delim, t_all *all)
{
	char	*rl;
	char	*tmp;
	char	*line;

	rl = readline("> ");
	if (!rl)
		return (xclose(&fd[0]), xclose(&fd[1]), 1);
	if (rl[0] != '\0' && !ft_compare(rl, delim->value))
		return (free(rl), 2);
	tmp = expand_in_str(rl, all);
	line = ft_strjoin(tmp, "\n");
	free(rl);
	free(tmp);
	if (!line)
		return (xclose(&fd[0]), xclose(&fd[1]), 1);
	write(fd[1], line, ft_strlen(line));
	free(line);
	return (0);
}

int	loop_heredoc(t_token *delim, int *fd, bool quotes, t_all *all)
{
	char	*rl;
	char	*line;
	int		ret;

	rl = NULL;
	line = NULL;
	if (quotes == TRUE)
		return (loop_heredoc_quotes(rl, delim, line, fd));
	while (1)
	{
		ret = heredoc_write(fd, delim, all);
		if (ret == 1)
			return (1);
		if (ret == 2)
			break ;
	}
	return (0);
}

int	heredoc(t_parser *cmd, t_token **tok, t_all *all)
{
	int		fd[2];
	int		ret;
	bool	quotes;

	quotes = FALSE;
	(*tok) = (*tok)->next;
	if (!(*tok) || (*tok)->type != WORD)
		return (10);
	if (pipe(fd) < 0)
		return (1);
	if ((*tok)->value[0] == '"' || (*tok)->value[0] == '\'')
		quotes = TRUE;
	ret = loop_heredoc((*tok), fd, quotes, all);
	if (ret)
		return (ret);
	xclose(&fd[1]);
	if (cmd->fd_in != 0)
		xclose(&cmd->fd_in);
	cmd->fd_in = fd[0];
	return (0);
}

int	else_if(t_parser **cmd, t_token **token, int *index, t_all *all)
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
		ret = heredoc(*cmd, token, all);
	return (ret);
}
