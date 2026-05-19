/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 23:18:14 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/09 23:29:50 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exit_message(char *cmd_and_args)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd_and_args, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

void	exit_builtin(t_all *all, t_parser *cmd)
{
	int	exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->cmd_and_args[1])
	{
		if (!is_numeric(cmd->cmd_and_args[1]) || (int)ft_strlen(cmd->cmd_and_args[1]) >= 20)
		{
			exit_message(cmd->cmd_and_args[1]);
			return ;
		}
		else if (cmd->cmd_and_args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			*get_status() = 2;
			return ;
		}
		exit_code = ft_atoi(cmd->cmd_and_args[1]);
	}
	clean_exit(all, exit_code % 256);
}
/*
	this fonction execute the exit builtin
	it checks if the arg is numeric and if there is too many args or too
	long exit code.
	then call clean_exit to free everything and quit
*/

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
/*
	this fonction check if a string contains only digits
	it allows a single '+' or '-' at the very beginning
	return 1 if true, 0 if false
*/
