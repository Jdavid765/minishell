/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:41:49 by canoduran         #+#    #+#             */
/*   Updated: 2026/05/19 21:35:01 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_env(t_all *all)
{
	t_env	*head;

	head = all->env;
	while (head)
	{
		if (head->key)
			ft_putstr_fd(head->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		if (head->value)
			ft_putstr_fd(head->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		head = head->next;
	}
}

int	create_path(t_env **ft_env)
{
	t_env	*head;
	t_env	*current;
	char	*key;
	char	*value;

	head = *ft_env;
	key = ft_strdup("_");
	if (!key)
		return (1);
	value = ft_strdup("/usr/bin/");
	if (!value)
		return (free(key), 1);
	current = ft_node_env(key, value);
	if (!current)
		return (free(key), free(value), 1);
	ft_add_back_env(&head, current);
	return (0);
}

int	check_path(t_env **ft_env)
{
	t_env	*head;
	int		found;

	found = 0;
	head = *ft_env;
	while (head)
	{
		if (head->key[0] == 'P')
		{
			if (!ft_compare(head->key, "PATH"))
				found = 1;
		}
		head = head->next;
	}
	if (found == 0)
	{
		if (!create_path(ft_env))
			return (1);
	}
	return (0);
}
