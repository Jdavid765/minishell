/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 23:18:14 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/07 16:19:22 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

void	check_cmd(t_all *all)
{
	char	*cmd;

	cmd = all->parser->cmd_and_args[0];
	if (!cmd)
		return ;
	if (ft_compare(cmd, "export") == 0)
		export_builtin(all, all->parser);
	else if (ft_compare(cmd, "pwd") == 0)
		pwd_builtin();
	else if (ft_compare(cmd, "exit") == 0)
		exit_builtin(all, all->parser);
	else if (ft_compare(cmd, "env") == 0)
		cmd_env(all);
	else if (ft_compare(cmd, "cd") == 0)
		cd_builtin(all, all->parser);
	else if (ft_compare(cmd, "echo") == 0)
		echo_builtin(all->parser);
	else if (ft_compare(cmd, "unset") == 0)
		unset_builtin(all, all->parser);
}
