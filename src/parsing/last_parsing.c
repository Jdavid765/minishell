/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:17:34 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/10 16:44:24 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_words(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD && token->is_valid == true)
			count++;
		else if (token->type >= REDIR_IN && token->type <= HEREDOC)
		{
			if (token->next)
				token = token->next;
		}
		token = token->next;
	}
	return (count);
}
/*
	count how many word the token list got
	it skip others types and count only if the word is_valid
	(see exp_variable)
*/

char	*search_path(t_all *all)
{
	t_env	*head;

	head = all->env;
	while (head)
	{
		if (head->key[0] == 'P')
		{
			if (!ft_compare(head->key, "PATH"))
				return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}

char	*search_path_no_env(t_all *all)
{
	t_env	*head;

	head = all->env;
	while (head)
	{
		if (head->key[0] == '_')
		{
			if (!ft_compare(head->key, "_"))
				return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}
