/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:48:54 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 15:12:51 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}
/*
	Checks if the command passed is a builtin
	returns 1 if it is, 0 otherwise.
*/

void	exec_builtin(t_all *all, t_parser *cmd)
{
	if (ft_strncmp(cmd->cmd_and_args[0], "echo", 5) == 0)
		echo_builtin(cmd);
	else if (ft_strncmp(cmd->cmd_and_args[0], "cd", 3) == 0)
		cd_builtin(all, cmd);
	else if (ft_strncmp(cmd->cmd_and_args[0], "pwd", 4) == 0)
		pwd_builtin();
	else if (ft_strncmp(cmd->cmd_and_args[0], "export", 7) == 0)
	{
		// export_builtin(all, cmd); // TODO: A adapter pour prendre un t_parser
	}
	else if (ft_strncmp(cmd->cmd_and_args[0], "unset", 6) == 0)
	{
		// unset_builtin(all, cmd); // TODO: A implémenter / prototyper
	}
	else if (ft_strncmp(cmd->cmd_and_args[0], "env", 4) == 0)
		cmd_env(all);
	else if (ft_strncmp(cmd->cmd_and_args[0], "exit", 5) == 0)
		exit_builtin(all, cmd);
}
/*
	choose the right builtin to use
	with the right fonction
*/

void	exec_single_builtin(t_all *all, t_parser *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (cmd->fd_in != 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	exec_builtin(all, cmd);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	(void)xclose(&saved_stdin);
	(void)xclose(&saved_stdout);
}
/*
	saves OG fd 1/0 then exec the builtin
	and give back the right fd
*/
