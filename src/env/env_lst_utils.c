/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:44:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 15:04:37 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_node_env(char *key, char *value)
{
	t_env	*newnode;

	newnode = malloc(sizeof(t_env));
	if (!newnode)
		return (NULL);
	newnode->key = key;
	newnode->value = value;
	newnode->next = NULL;
	return (newnode);
}

void	ft_add_back_env(t_env **head, t_env *new)
{
	t_env	*current;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return ;
}

void	ft_lst_del_env(t_env *ft_env)
{
	if (!ft_env)
		return ;
	if (ft_env->key)
		free(ft_env->key);
	if (ft_env->value)
		free(ft_env->value);
	free(ft_env);
}

void	look_env(t_all *all)
{
	t_env	*head;

	head = all->env;
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

