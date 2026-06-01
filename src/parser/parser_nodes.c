/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:18:45 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/25 22:02:55 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_parser	*ft_node_pars(char *path)
{
	t_parser	*newnode;

	newnode = malloc(sizeof(t_parser));
	if (!newnode)
		return (NULL);
	newnode->cmd_and_args = NULL;
	newnode->path = ft_strdup(path);
	if (!newnode->path)
		return (free(newnode), NULL);
	newnode->fd_in = 0;
	newnode->fd_out = 1;
	newnode->is_builtin = FALSE;
	newnode->access_check = FALSE;
	newnode->next = NULL;
	return (newnode);
}
/*
	this fonction creates and initializes a new parser node
	returns NULL if a malloc fails
*/

void	ft_addback_parse(t_parser **head, t_parser *new)
{
	t_parser	*current;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return ;
}
/*
	this fonction adds a newly created parser node
	to the end of the parser linked list
*/

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
