/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 23:18:14 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 14:49:42 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
/*
	this fonction check which quote is used
	and send it to the right handle
*/

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
/*
	this fonction remove double quotes
	and expand variables inside if needed
*/

int	single_quote(t_token *token)
{
	char	*tmp;

	tmp = strip_quotes(token->value);
	free(token->value);
	token->value = tmp;
	return (0);
}
/*
	this fonction only remove single quotes
	without expanding anything inside
*/
