/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:40 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/09 23:26:43 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int tokenizer(char *user_input, t_all *all)
{
	int i;

	i = 0;
	while(user_input[i])
	{
		if (find_by_char(user_input, i))
			return (1);
		i++;
	}
	return (0);
}

/*
	this fonction create a token chained list by the given line
	this fonction return 1 if fails 
	and return 0 if everything is ok
	the fonc can fail if new_token failed to malloc
*/


int	new_token(t_token *token_head, t_token_type	type, char *token_val)
{
	t_token *last_token;
	t_token *new_token;

	if(token_head->next == NULL)//first token to set
	{
		set_first_node(token_head, type, token_val);
		return (0);
	}
	last_token = last_token_list(token_head);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (1);
	new_token->value = token_val;
	new_token->type = type;
	new_token->is_valid = false;
	new_token->next = NULL;
	new_token->prev = last_token;
	last_token->next = new_token;
	return (0);
}

/*
	create a new node in the token list
	return (1) if malloc fails
	assign the booleen value to false by default
	and set next and prev
*/

t_token	*last_token_list(t_token *token_head)
{
	while(token_head)
	{
		token_head = token_head->next;
	}
	return (token_head);
}

/*
	find the last node of the token list and return it.
*/

void	set_first_node(t_token *first_token, t_token_type	type, char *token_val)
{
	first_token->prev = NULL;
	first_token->next = NULL;
	first_token->value = token_val;
	first_token->type = type;
	first_token->is_valid = false;
}
/*
	same thing as new_token but it's for 
	the first token that already exist
	so we don't need to malloc();
*/
