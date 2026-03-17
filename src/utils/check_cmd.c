/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 23:18:14 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/16 18:53:23 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_cmd(char *rl, t_env **ft_env)
{
	if (ft_compare(rl, "export") == 0)
		export_builtin(ft_env, rl);
	if (ft_compare(rl, "pwd") == 0)
		pwd_builtin();
	if (ft_compare(rl, "exit") == 0)
		exit_builtin((void *)rl);
	if (ft_compare(rl, "env") == 0)
		cmd_env(ft_env);
	return ;
}
