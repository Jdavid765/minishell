/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:59:29 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/07 23:39:49 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_export(t_all *all)
{
	t_env	*current;

	current = all->env;
	while (current)
	{
		if (current->value)
		{
			ft_putstr_fd("declare -x ", STDERR_FILENO);
			ft_putstr_fd(current->key, STDERR_FILENO);
			ft_putstr_fd(current->value, STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("declare -x ", STDERR_FILENO);
			ft_putstr_fd(current->key, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		}
		current = current->next;
	}
}

int	add_or_update(t_all *all, char *arg)
{
	char	*key;
	char	*value;

	if (!all || !arg)
		return (1);
	if (parse_arg(arg, &key, &value))
		return (1);
	if (is_valid_arg(key))
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(", not a valid identifier\n", STDERR_FILENO);
		free(key);
		free(value);
		return (1);
	}
	if (update_existing(all, key, value, arg))
		return (0);
	return (append_node(all, key, value));
}

int	export_builtin(t_all *all, t_parser *cmd)
{
	int	i;

	if (!cmd->cmd_and_args[1])
	{
		print_export(all);
		return (0);
	}
	i = 1;
	while (cmd->cmd_and_args[i])
	{
		if (!add_or_update(all, cmd->cmd_and_args[i]))
			return (0);
		i++;
	}
	return (1);
}
