/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 23:16:27 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/28 23:16:42 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_words(t_token *token)
{
	int	count;
 
	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
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
 
int	redir_out(t_parser *cmd, t_token **tok)
{
	t_token	*tmp;

	tmp = (*tok)->next;
	if (!tmp || tmp->type != WORD)
		return (10);
	if (cmd->fd_out != 1)
		cmd->fd_out = xclose(&cmd->fd_out);
	cmd->fd_out = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
		return (1);
	return (0);
}