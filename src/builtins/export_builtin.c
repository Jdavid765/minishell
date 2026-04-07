/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:59:29 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/07 15:10:01 by canoduran        ###   ########.fr       */
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
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
}

int	add_or_update(t_all *all, char *arg)
{
	//ajouter ou check si elle existe deja et la remplacer.
	if (!all || !arg)
		return (1);
	return (0);
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
		if (add_or_update(all, cmd->cmd_and_args[i]))
			return (1);
		i++;
	}
	return (0);
}
