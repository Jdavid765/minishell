/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:48:54 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 15:12:51 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(t_all *all)
{
	int	nb_cmds;

	if (!all || !all->parser)
		return ;
	ignore_signals();
	nb_cmds = count_cmds(all->parser);
	if (nb_cmds == 1)
		exec_single_cmd(all);
	else
		exec_pipeline(all);
	setup_signal(all);
}
/*
	main fonction for the execution
*/

int	count_cmds(t_parser *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}
/*
	this fonction help tout count,
	how many cmd are send to the exec part
*/
