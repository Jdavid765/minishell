/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:56:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/02 00:33:04 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_in(t_parser *cmd, t_token **tok)
{
	(*tok) = (*tok)->next;
	if (!(*tok) || (*tok)->type != WORD)
		return (10);
	if (cmd->fd_in != 0)
		xclose(&cmd->fd_in);
	cmd->fd_in = open((*tok)->value, O_RDONLY);
	if (cmd->fd_in < 0)
		return (1);
	return (0);
}
/*
	this fonction handles input redirection (<)
	and opens the target file in read-only mode
*/

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
/*
	this fonction handles output redirection (>)
	and opens the target file in write/truncate mode
*/

int	append(t_parser *cmd, t_token **tok)
{
	(*tok) = (*tok)->next;
	if (!(*tok) || (*tok)->type != WORD)
		return (10);
	if (cmd->fd_out != 1)
		xclose(&cmd->fd_out);
	cmd->fd_out = open((*tok)->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd_out < 0)
		return (1);
	return (0);
}
/*
	this fonction handles append redirection (>>)
	and opens the target file in write/append mode
*/
