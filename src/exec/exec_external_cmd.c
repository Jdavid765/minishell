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

void	child_single_external(t_all *all, t_parser *cmd)
{
	char	**new_env;
	char	*temp_path;

	apply_redirections(cmd);
	temp_path = before_path_check(all->env, cmd->cmd_and_args[0]);
	free(cmd->path);
	cmd->path = temp_path;
	if (!cmd->path)
	{
		ft_putstr_fd("minishell: ", 2);
		if (cmd->cmd_and_args && cmd->cmd_and_args[0])
			ft_putstr_fd(cmd->cmd_and_args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	new_env = re_build_env(all->env, NULL);
	restore_original_signals(all);
	execve(cmd->path, cmd->cmd_and_args, new_env);
	perror("execve");
	free_tab(new_env);
	exit(126);
}
/*
	apply right redirections and check if the PATH exist
	rebuilt the new env for execve and check if it fails
*/

void	exec_single_external(t_all *all, t_parser *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		child_single_external(all, cmd);
	else
		parent_single_external(cmd, pid);
}
/*

*/

void	parent_single_external(t_parser *cmd, pid_t pid)
{
	int	status;

	if (cmd->fd_in != 0)
		xclose(&cmd->fd_in);
	if (cmd->fd_out != 1)
		xclose(&cmd->fd_out);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*get_status() = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		*get_status() = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
		else if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
	}
}
/*
	wait for the end of child process
	and close the fd's he don't need
*/
