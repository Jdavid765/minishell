/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:41:49 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/26 21:29:27 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void	cmd_env(t_all *all)
{
	t_env	*head;

	head = all->env;
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
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
	key = malloc(sizeof(char) * 5);
	if (!key)
		return (1);
	value = ft_strdup("/usr/bin/");
	if (!value)
		return (1);
	current = ft_node_env(key, value);
	if (!current)
		return (1);
	ft_add_back_env(&head, current);
	return (0);
}

int	check_path(t_env **ft_env)
{
	t_env	*head;

	head = *ft_env;
	while (head)
	{
		if (head->key[0] == 'P')
		{
			if (!ft_compare(head->key, "PATH"))
			{
				if (!create_path(&head))
					return (0);
			}
		}
		head = head->next;
	}
	return (1);
}
