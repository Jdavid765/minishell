/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
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
