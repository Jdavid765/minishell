/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:48:54 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 15:12:51 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	manage_parent_fds(t_parser *cmd, int *prev_read_fd, int *pipefd)
{
	if (*prev_read_fd != -1)
		xclose(prev_read_fd);
	if (cmd->next)
	{
		xclose(&pipefd[1]);
		*prev_read_fd = pipefd[0];
	}
}
/*
	close the prev fd if it exists
	if there is another cmd close the previous one 
*/

void	setup_pipe_fds(t_parser *cmd, int prev_read_fd, int *pipefd)
{
	if (prev_read_fd != -1)
	{
		dup2(prev_read_fd, STDIN_FILENO);
		xclose(&prev_read_fd);
	}
	if (cmd->next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		xclose(&pipefd[0]);
		xclose(&pipefd[1]);
	}
}
/*
	check if it's the first cmd or not to sertup the right redirection
	and check if there is and cmd after
*/

void	apply_redirections(t_parser *cmd)
{
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		exit(1);
	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		xclose(&cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		xclose(&cmd->fd_out);
	}
}
/*
	this fonction apply the redirections by duplicating fds
	and crash the child process if an open failed before
*/
