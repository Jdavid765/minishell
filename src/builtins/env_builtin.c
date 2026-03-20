/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:41:49 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/20 21:16:22 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void	cmd_env(t_all *all)
{
	t_env	*head;

	head = all->env;
	while (head->next)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

void	create_path(t_env **ft_env)
{
	t_env	*head;
	t_env	*current;
	int		cnt_value;
	char	*key;
	char	*value;

	head = *ft_env;
	cnt_value = ft_strlen("/usr/bin/") + 1;
	key = malloc(sizeof(char) * 5);
	if (!key)
		return ;
	value = malloc(sizeof(char) * cnt_value);
	if (!value)
		return ;
	current = ft_node_env(key, value);
	if (!current)
		return ;
	ft_add_back_env(&head, current);
}

void	check_path(t_env **ft_env)
{
	t_env	*head;

	head = *ft_env;
	while (head)
	{
		if (head->key[0] == 'P')
		{
			if (!ft_compare(head->key, "PATH"))
				return ;	
		}
		head = head->next;
	}
	create_path(&head);
}