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
	if (prev_read_fd != -1)
		xclose(&prev_read_fd);
	wait_pipeline(pid);
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

void	execute_pipeline_cmd(t_all *all, t_parser *cmd)
{
	char	**envp;
	char	*temp_path;

	if (is_builtin(cmd->cmd_and_args[0]))
	{
		exec_builtin(all, cmd);
		exit(*get_status());
	}
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
	envp = re_build_env(all->env, NULL);
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

void	wait_pipeline(pid_t last_pid)
{
	int		status;
	int		sig_int;
	int		sig_quit;
	pid_t	wpid;

	sig_int = 0;
	sig_quit = 0;
	while ((wpid = waitpid(-1, &status, 0)) > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				*get_status() = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*get_status() = 128 + WTERMSIG(status);
		}
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				sig_int = 1;
			else if (WTERMSIG(status) == SIGQUIT)
				sig_quit = 1;
		}
	}
	if (sig_int)
		printf("\n");
	if (sig_quit)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
}
/*

*/










