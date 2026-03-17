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
	if(ft_isalpha(user_input[*i]))//si c'est un mot ou une commande
	{
		if(new_word_or_cmd(user_input, i, all))
			return (1);
	}
	// if(user_input[*i] == "\"")//si c'est un quote simple
	// 	new_single_quote();
	// if(user_input[*i])//si c'est un quotes double
	// 	new_double_quote();
	// if(user_input[*i])//si c'est un pipe
	// 	new_pipe();
	// if(user_input[*i])//si c'est un < ou un <<
	// 	new_redir_in_heredoc();
	// if(user_input[*i])//si c'est un > ou un >>
	// 	new_redir_in_or_appnd();
	// //if(user_input[*i])//c'est c'est ???
	return (0);
}
/*
	this fonction send the char read in a redirection fonction
	the purpose is to split the string
	into substrings and know what each arg is
	return (1) if a malloc fails
*/


int	new_word_or_cmd(char *user_input, int *start, t_all *all)
{
	char	*arg;
	int	end;

	end = 0;
	printf("start == %d\n", *start);
	while(user_input[*start + end] && !is_a_separator(user_input[*start + end]))
	{
		end++;
	}
	arg = ft_substr(user_input, *start, end);
	if(arg == NULL)
		return (1);
	printf("arg == %s\n", arg);
	*start += end;
	if(!new_token_node(&all->token, WORD, arg))
		return (free(arg), 1);
	
	return (0);
}
/*
	this fonction find new token et set a new node
	return 1 if an error occurs
*/

int	is_a_separator(char letter)
{
	if(letter == '|')
		return (1);
	if(letter == '<')
		return (1);
	if(letter == '>')
		return (1);
	if(letter == '\'')
		return (1);
	if(letter == '\"')
		return (1);
	if(letter == '-')
		return (1);
	if(letter == ' ')
		return (1);
	return (0);
}
/*
	this fonction help new_word_or_cmd() while condtion
	to stop if the char is an important char
*/
