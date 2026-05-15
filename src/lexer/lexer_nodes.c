/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:40 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/03 15:13:26 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token_node(t_token_type type, char *val)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = val;
	new->type = type;
	new->is_valid = true;
	new->space_after = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
/*
	this fonction create a new node token node
*/

int	new_token_node(t_token **token_head, t_token_type type, char *token_val)
{
	t_token	*new_node;
	t_token	*last;

	new_node = create_token_node(type, token_val);
	if (!new_node)
		return (1);
	if (*token_head == NULL)
	{
		*token_head = new_node;
		return (0);
	}
	last = last_token_list(*token_head);
	last->next = new_node;
	new_node->prev = last;
	return (0);
}
/*
	this fonction call create_token_node and
	link the new node to the end of the list
	or the head if it's the first
*/

t_token	*last_token_list(t_token *token_head)
{
	while (token_head->next)
	{
		token_head = token_head->next;
	}
	return (token_head);
}
/*
	find the last node of the token list and return it.
*/
