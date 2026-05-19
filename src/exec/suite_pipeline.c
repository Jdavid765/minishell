/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suite_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 16:19:40 by canoduran         #+#    #+#             */
/*   Updated: 2026/05/19 16:21:04 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_pipeline(t_all *all, t_parser *cmd, int prev_fd, int *p_fd)
{
	setup_pipe_fds(cmd, prev_fd, p_fd);
	apply_redirections(cmd);
	execute_pipeline_cmd(all, cmd);
}
/*
	bridge for all the cmd exec
*/

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