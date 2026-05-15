/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:40 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/03 15:13:26 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	new_redir_out_or_appnd(char *user_input, int *start, t_all *all)
{
	char	*arg;
	int		end;

	end = 1;
	if (user_input[*start + 1] == '>')
	{
		if (new_appnd(user_input, start, all, end + 1))
			return (1);
		return (0);
	}
	arg = ft_substr(user_input, *start, end);
	if (arg == NULL)
		return (1);
	*start += end;
	if (new_token_node(&all->token, REDIR_OUT, arg))
		return (free(arg), 1);
	return (0);
}

int	new_appnd(char *user_input, int *start, t_all *all, int end)
{
	char	*arg;

	arg = ft_substr(user_input, *start, end);
	if (arg == NULL)
		return (1);
	*start += end;
	if (new_token_node(&all->token, APPEND, arg))
		return (free(arg), 1);
	return (0);
}

int	new_redir_in_or_heredoc(char *user_input, int *start, t_all *all)
{
	char	*arg;
	int		end;

	end = 1;
	if (user_input[*start + 1] == '<')
	{
		if (new_heredoc(user_input, start, all, end + 1))
			return (1);
		return (0);
	}
	arg = ft_substr(user_input, *start, end);
	if (arg == NULL)
		return (1);
	*start += end;
	if (new_token_node(&all->token, REDIR_IN, arg))
		return (free(arg), 1);
	return (0);
}

int	new_heredoc(char *user_input, int *start, t_all *all, int end)
{
	char	*arg;

	arg = ft_substr(user_input, *start, end);
	if (arg == NULL)
		return (1);
	*start += end;
	if (new_token_node(&all->token, HEREDOC, arg))
		return (free(arg), 1);
	return (0);
}
