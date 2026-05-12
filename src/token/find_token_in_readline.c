/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token_in_readline.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:40 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/29 14:13:44 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tokenizer(char *user_input, t_all *all)
{
	int		i;
	t_token	*last;

	i = 0;
	while (user_input[i])
	{
		while (user_input[i] == ' ')
			i++;
		if (user_input[i] == '\0')
			break ;
		if (find_by_char(user_input, &i, all))
			return (1);
		last = last_token_list(all->token);
		if (last)
		{
			if (user_input[i] == ' ' || user_input[i] == '\0')
				last->space_after = true;
			else
				last->space_after = false;
		}
	}
	return (0);
}

/*
	this fonction create a token chained list by the given line
	this fonction return 1 if fails 
	and return 0 if everything is ok
	fail if create_token_node failed to malloc
*/

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

void	join_adjacent_tokens(t_all *all)
{
	t_token	*curr;
	t_token	*to_delete;
	char	*tmp;

	curr = all->token;
	while (curr && curr->next)
	{
		if (curr->type == WORD && curr->next->type == WORD && curr->space_after == false)
		{
			tmp = ft_strjoin(curr->value, curr->next->value);
			free(curr->value);
			curr->value = tmp;
			curr->space_after = curr->next->space_after;
			to_delete = curr->next;
			curr->next = to_delete->next;
			if (curr->next)
				curr->next->prev = curr;
			free(to_delete->value);
			free(to_delete);
		}
		else
			curr = curr->next;
	}
}
