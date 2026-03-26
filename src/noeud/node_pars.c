/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:18:45 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/25 22:02:55 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

t_parser	*ft_node_pars(char *path)
{
	t_parser	*Newnode;

	Newnode = malloc(sizeof(t_parser));
	if (!Newnode)
		return (NULL);
	Newnode->cmd_and_args = NULL;
	Newnode->path = ft_strdup(path);
	if (!Newnode->path)
		return (NULL);
	Newnode->fd_in = 0;
	Newnode->fd_out = 1;
	Newnode->is_builtin = FALSE;
	Newnode->access_check = FALSE;
	Newnode->next = NULL;
	return (Newnode);
}

void	ft_addback_parse(t_parser **head, t_parser *new)
{
	t_parser	*current;

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
