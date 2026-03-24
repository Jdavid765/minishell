/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_exp_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 23:36:04 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/23 23:43:08 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

t_exp_var	*node_exp_var(char *key, char *value)
{
	t_exp_var	*Newnode;

	Newnode = malloc(sizeof(t_exp_var));
	if (!Newnode)
		return (NULL);
	Newnode->key = key;
	Newnode->value = value;
	Newnode->next = NULL;
	return (Newnode);
}

void	ft_add_back_exp(t_exp_var **head, t_exp_var *new)
{
	t_exp_var	*current;

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