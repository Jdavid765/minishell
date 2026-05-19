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

int	pwd_builtin(t_all *all)
{
	char	*pwd;
	t_env	*pwd_node;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd_node = find_pwd_node(all);
		if (pwd_node && pwd_node->value)
		{
			ft_putendl_fd(pwd_node->value, STDOUT_FILENO);
			return (0);
		}
		return (perror("pwd: error retrieving current directory"), 1);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
/*
	pwd is a pointer to the string of the current working directory
	write is used here for safety
	pwd is free at the end because,
	getcwd allocated memory for given line
*/
