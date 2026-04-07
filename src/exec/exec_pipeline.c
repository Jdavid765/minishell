/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:48:54 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 15:12:51 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_pipeline(void)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			*get_status() = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*get_status() = 128 + WTERMSIG(status);
	}
}
/*

*/

void	exec_pipeline(t_all *all)
{
	t_parser	*cmd;
	int			pipefd[2];
	int			prev_read_fd;
	pid_t		pid;

	cmd = all->parser;
	prev_read_fd = -1;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
			child_pipeline(all, cmd, prev_read_fd, pipefd);
		else
			manage_parent_fds(cmd, &prev_read_fd, pipefd);
		cmd = cmd->next;
	}
	wait_pipeline();
}
/*
	main loop for execute more than one cmd
	fork every cmd and send it where it belong
*/

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
		close(*prev_read_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
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
		close(prev_read_fd);
	}
	if (cmd->next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}
/*
	check if it's the first cmd or not to sertup the right redirection
	and check if there is and cmd after
*/

void	execute_pipeline_cmd(t_all *all, t_parser *cmd)
{
	char	**envp;

	if (is_builtin(cmd->cmd_and_args[0]))
	{
		exec_builtin(all, cmd);
		exit(0);
	}
	if (!cmd->path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	envp = re_build_env(all->env, NULL);
	free(cmd->path);
	cmd->path = before_path_check(all->env, cmd->cmd_and_args[0]);
	restore_original_signals(all);
	execve(cmd->path, cmd->cmd_and_args, envp);
	perror("execve");
	free_tab(envp);
	exit(126);
}

/*
	check if the cmd is a builtin else exec the extrenal cmd
	check if it fails
*/
