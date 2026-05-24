/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:40 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/03 15:13:26 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	new_double_quote(char *user_input, int *start, t_all *all)
{
	char	*arg;
	int		end;

	end = 1;
	while (user_input[*start + end] && user_input[*start + end] != '\"')
		end++;
	if (user_input[*start + end] == '\0')
	{
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		*get_status() = 2;
		return (1);
	}
	if (user_input[*start + end] == '\"')
		end++;
	arg = ft_substr(user_input, *start, end);
	if (arg == NULL)
		return (1);
	*start += end;
	if (new_token_node(&all->token, WORD, arg))
		return (free(arg), 1);
	return (0);
}
/*
	this fonction extracts a string inside double quotes
	and creates a new WORD token node
	returns 1 if a malloc fails
*/

int	new_single_quote(char *user_input, int *start, t_all *all)
{
	char	*arg;
	int		end;

	end = 1;
	while (user_input[*start + end] && user_input[*start + end] != '\'')
		end++;
	if (user_input[*start + end] == '\'')
		end++;
	arg = ft_substr(user_input, *start, end);
	if (arg == NULL)
		return (1);
	*start += end;
	if (new_token_node(&all->token, WORD, arg))
		return (free(arg), 1);
	return (0);
}
/*
	this fonction extracts a string inside single quotes
	and creates a new WORD token node
	returns 1 if a malloc fails
*/
