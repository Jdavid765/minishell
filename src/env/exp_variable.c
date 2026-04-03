/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 22:38:03 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/03 19:13:26 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"
 
int	double_quote(t_token *token, t_all *all)
{
	char	*tmp;

	tmp = strip_quotes(token->value);
	free(token->value);
	token->value = tmp;
	if (ft_strchr(token->value, '$'))
	{
		tmp = expand_in_str(token->value, all);
		free(token->value);
		token->value = tmp;
	}
	return (0);
}
 
int	single_quote(t_token *token)
{
	char	*tmp;
 
	tmp = strip_quotes(token->value);
	free(token->value);
	token->value = tmp;
	return (0);
}
 
int	quotes(t_token *token, t_all *all)
{
	if (!token)
		return (1);
	if (token->value[0] == 34)
		return (double_quote(token, all));
	else if (token->value[0] == 39)
		return (single_quote(token));
	return (0);
}
 
int	check_sign(t_token *token, t_all *all)
{
	if (token->value[0] == 34 || token->value[0] == 39)
	{
		if (quotes(token, all))
			return (1);
	}
	else if (token->value[0] == '$')
	{
		if (check_dollar(token, all))
			return (1);
	}
	return (0);
}
 
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
