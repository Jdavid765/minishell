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
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

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
		printf("%s", cmd->cmd_and_args[i]);
		if (cmd->cmd_and_args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}
/*
	the echo builtin first check if there is a -n flag

*/
