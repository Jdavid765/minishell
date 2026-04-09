/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:47:11 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/07 14:49:11 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

void	remove_env_node(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_compare(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			ft_lst_del_env(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	unset_builtin(t_all *all, t_parser *cmd)
{
	int	i;

	if (!cmd->cmd_and_args[1])
		return (1);
	i = 1;
	while (cmd->cmd_and_args[i])
	{
		remove_env_node(&all->env, cmd->cmd_and_args[i]);
		i++;
	}
	return (0);
}
