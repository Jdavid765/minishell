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

void	exit_builtin(t_all *all, t_parser *cmd)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (cmd->cmd_and_args[1])
	{
		if (!is_numeric(cmd->cmd_and_args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->cmd_and_args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			clean_exit(all, 255);
		}
		else if (cmd->cmd_and_args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return ;
		}
		else
			exit_code = ft_atoi(cmd->cmd_and_args[1]);
	}
	clean_exit(all, exit_code % 256);
}
/*
	this fonction execute the exit builtin
	it checks if the arg is numeric and if there is too many args
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
