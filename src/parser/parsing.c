/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:56:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/02 00:33:04 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parse_token(t_all *all)
{
	t_parser	*head;
	t_parser	*current_cmd;
	t_token		*current_tok;
	int			nb_words;
	int			ret;

	if (!all->token)
		return (15);
	current_tok = all->token;
	if (current_tok->type == PIPE)
		return (10);
	head = ft_node_pars(all->path);
	current_cmd = head;
	nb_words = count_words(current_tok) + 1;
	current_cmd->cmd_and_args = ft_calloc(nb_words, sizeof(char *));
	if (!current_cmd->cmd_and_args)
		return (1);
	ret = parse_loop(&current_cmd, current_tok, all);
	if (ret == 1 || ret == 10 || ret == 130)
		return (ret);
	else if (ret == 5)
		return ((all->parser = head), ret);
	all->parser = head;
	return (0);
}
/*
	Main fonction for the the t_parser list
	you can find ft_node pars in the folder "node/node_pars.c"
	it return an INT depending on the error
*/

int	parse_loop(t_parser **cmd, t_token *token, t_all *all)
{
	int		index;
	int		ret;

	index = 0;
	ret = 0;
	while (token)
	{
		ret = all_else_if(cmd, &token, all, &index);
		if (ret)
			return (ret);
		if (token)
			token = token->next;
	}
	if (*cmd && (*cmd)->cmd_and_args)
		(*cmd)->cmd_and_args[index] = NULL;
	return (0);
}

int	all_else_if(t_parser **cmd, t_token **token, t_all *all, int *index)
{
	int	ret;

	ret = 0;
	if ((*token)->type == WORD)
	{
		if ((*token)->is_valid == true)
			(*cmd)->cmd_and_args[(*index)++] = ft_strdup((*token)->value);
	}
	else if ((*token)->type == REDIR_OUT)
		ret = redir_out(*cmd, token);
	else if ((*token)->type == APPEND)
		ret = append(*cmd, token);
	else if ((*token)->type == REDIR_IN)
		ret = redir_in(*cmd, token);
	else if ((*token)->type == PIPE)
		ret = ft_pipe(cmd, (*token), index, all->path);
	else if ((*token)->type == HEREDOC)
		ret = heredoc(all, *cmd, token);
	return (ret);
}
/*
	this fonction iterates over tokens to fill the current parser node
	it dispatches the token parsing through all_else_if
*/

//when i exit i need to free all i allocated;
// 10 = error de syntax
// 1 = error type malloc
// 5 = for double pipe if before the double pipe have command put in linked list
// 15 = for string empty
// i need to look about the cat |