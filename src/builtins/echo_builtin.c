/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:48:54 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 15:12:51 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*
	Validates if an argument is a properly formatted '-n' flag,
	including cases like '-nnnn'
*/
void	echo_builtin(t_parser *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->cmd_and_args[i] && is_n_option(cmd->cmd_and_args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->cmd_and_args[i])
	{
		ft_putstr_fd(cmd->cmd_and_args[0], STDOUT_FILENO);
		if (cmd->cmd_and_args[i + 1])
			ft_putstr_fd(cmd->cmd_and_args[0], STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
/*
	the echo builtin first check if there is a -n flag
	then print the output and check if n_flag is true
*/
