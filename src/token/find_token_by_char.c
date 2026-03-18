/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token_by_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:40 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 15:03:40 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_by_char(char *user_input, int *i, t_all *all)
{
	if (user_input[*i] == '|')
		return (new_pipe(user_input, i, all));
	else if (user_input[*i] == '<')
		return (new_redir_in_or_heredoc(user_input, i, all));
	else if (user_input[*i] == '>')
		return (new_redir_out_or_appnd(user_input, i, all));
	else if (user_input[*i] == '\'')
		return (new_single_quote(user_input, i, all));
	else if (user_input[*i] == '\"')
		return (new_double_quote(user_input, i, all));
	else if (user_input[*i] != ' ' && user_input[*i] != '\0')
		return (new_word_or_cmd(user_input, i, all));
	else
		return ((*i)++, 0);
}

/*
	this fonction send the char read in a redirection fonction
	the purpose is to split the string
	into substrings and know what each arg is
	return (1) if a malloc fails
*/

int	new_redir_out_or_appnd(char *user_input, int *start, t_all *all)
{
	char	*arg;
	int		end;

	end = 1;
	if(user_input[*start + 1] == '>')
	{
		if(new_appnd(user_input, start, all, end + 1))
			return (1);
		return (0);
	}
	arg = ft_substr(user_input, *start, end);
	if(arg == NULL)
		return (1);
	*start += end;
	if(new_token_node(&all->token, REDIR_OUT, arg))
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
	if(user_input[*start + 1] == '<')
	{
		if(new_heredoc(user_input, start, all, end + 1))
			return (1);
		return (0);
	}
	arg = ft_substr(user_input, *start, end);
	if(arg == NULL)
		return (1);
	*start += end;
	if(new_token_node(&all->token, REDIR_IN, arg))
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

int	new_pipe(char *user_input, int *start, t_all *all)
{
	char	*arg;
	int		end;

	end = 1;
	arg = ft_substr(user_input, *start, end);
	if (arg == NULL)
		return (1);
	*start += end;
	if (new_token_node(&all->token, PIPE, arg))
		return (free(arg), 1);
	return (0);
}

int	new_double_quote(char *user_input, int *start, t_all *all)
{
	char	*arg;
	int		end;

	end = 1;
	while (user_input[*start + end] && user_input[*start + end] != '\"')//a voir plus tard le cas d'un quote sans sa paire
		end++;
	arg = ft_substr(user_input, *start, ++end);
	if (arg == NULL)
		return (1);
	*start += end;
	if (new_token_node(&all->token, WORD, arg))
		return (free(arg), 1);
	return (0);
}

int	new_single_quote(char *user_input, int *start, t_all *all)
{
	char	*arg;
	int		end;

	end = 1;
	while (user_input[*start + end] && user_input[*start + end] != '\'')
		end++;
	arg = ft_substr(user_input, *start, ++end);
	if (arg == NULL)
		return (1);
	*start += end;
	if (new_token_node(&all->token, WORD, arg))
		return (free(arg), 1);
	return (0);
}

int	new_word_or_cmd(char *user_input, int *start, t_all *all)
{
	char	*arg;
	int		end;

	end = 0;
	while (user_input[*start + end] && !is_a_separator(user_input[*start + end]))
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
	this fonction find new token et set a new node
	return 1 if an error occurs
*/

int	is_a_separator(char letter)
{
	if (letter == '|')
		return (1);
	if (letter == '<')
		return (1);
	if (letter == '>')
		return (1);
	if (letter == '\'')
		return (1);
	if (letter == '\"')
		return (1);
	// if (letter == '-')
	// 	return (1);
	if  (letter == ' ')
		return (1);
	return (0);
}
/*
	this fonction help new_word_or_cmd() while condtion
	to stop if the char is an important char
*/
