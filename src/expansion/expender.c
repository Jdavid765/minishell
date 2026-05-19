/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 23:18:14 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 14:49:42 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_exp_var(t_all *all)
{
	t_token		*head;

	head = all->token;
	while (head)
	{
		if (check_sign(head, all))
			return (1);
		head = head->next;
	}
	return (0);
}
/*
	this fonction loop through all tokens
	to check if they need to be expanded
*/

int	check_sign(t_token *token, t_all *all)
{
	if (token->value[0] == '\"' || token->value[0] == '\'')
	{
		if (quotes(token, all))
			return (1);
	}
	else if (ft_strchr(token->value, '$'))
	{
		if (check_dollar(token, all))
			return (1);
	}
	return (0);
}
/*
	this fonction route the token to quote
	or dollar expansion depending on the sign
*/

int	check_dollar(t_token *token, t_all *all)
{
	char	*tmp;

	if (!token)
		return (1);
	tmp = expand_in_str(token->value, all);
	if (!tmp)
		return (1);
	
	if (ft_strchr(tmp, ' '))
	{
		if (split_expanded_token(token, tmp))
			return (free(tmp), 1);
		free(tmp);
	}
	else
	{
		free(token->value);
		token->value = tmp;
		if (token->value[0] == '\0')
			token->is_valid = false;
	}
	return (0);
}
/*
	the fonction first call the expension once done
	we look if the expended var have space if it's the case then we split
*/