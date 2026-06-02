/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:48:54 by canoduran         #+#    #+#             */
/*   Updated: 2026/06/02 21:41:47 by canoduran        ###   ########.fr       */
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

void	check_dir_and_perm(t_all *all, char *cmd)
{
	struct stat	s;

	if (access(cmd, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd);
		clean_exit(all, 127);
	}
	if (stat(cmd, &s) == 0 && S_ISDIR(s.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
		clean_exit(all, 126);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd);
		clean_exit(all, 126);
	}
}
/*
	this fonction check if the path exist, is a directory
	or lack execution permissions and exit with the right code
*/

void	check_exec_error(t_all *all, char *cmd)
{
	if (ft_strchr(cmd, '/'))
		check_dir_and_perm(all, cmd);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	clean_exit(all, 127);
}
/*
	this fonction check if the cmd is a path to route to the
	right error handler or print command not found and exit 127
*/
