/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:44:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 14:34:56 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

t_env	*ft_node_env(char *key, char *value)
{
	t_env	*Newnode;

	Newnode = malloc(sizeof(t_env));
	if (!Newnode)
		return (NULL);
	Newnode->key = key;
	Newnode->value = value;
	Newnode->next = NULL;
	return (Newnode);
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
		while (current)
			current = current->next;
		current->next = new;
	}
	return ;
}

void	ft_lst_del_env(t_env *ft_env)
{
	if (!ft_env)
		return ;
	free(ft_env->value);
}