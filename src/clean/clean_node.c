/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:56:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/28 23:33:08 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		if (head->value)
			free(head->value);
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
/*
	this fonction clean the token list basically
*/

int	clean_cmd_list(t_parser *head)
{
	t_parser	*tmp;
	int			status;

	status = 0;
	while (head)
	{
		if (head->cmd_and_args)
			free_tab(head->cmd_and_args);
		if (head->path)
			free(head->path);
		if (head->fd_in != 0 && xclose(&head->fd_in) == -1)
		{
			perror("xclose :");
			status = 1;
		}
		if (head->fd_out != 1 && xclose(&head->fd_out) == -1)
		{
			perror("xclose :");
			status = 1;
		}
		tmp = head->next;
		free(head);
		head = tmp;
	}
	return (status);
}

/*
	this fonction clean the cmd list 
	free the char * and char ** needed
	close the fd if they still open w/ xclose
	if xclose fail status is set to 1 refeer the error
	and perror is called
*/

void	clean_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		free(head->key);
		free(head->value);
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
/*
	this fonction clean the env list basically
*/

int	clean_parsing_list(t_parser *head)
{
	t_parser	*tmp;
	int			status;

	status = 0;
	while (head)
	{
		free_tab(head->cmd_and_args);
		tmp = head->next;
		if (head->fd_in != -1 && xclose(&head->fd_in) == -1)
		{
			perror("xclose :");
			status = 1;
		}
		if (head->fd_out != -1 && xclose(&head->fd_out) == -1)
		{
			perror("xclose :");
			status = 1;
		}
		free(head);
		head = tmp;
	}
	return (status);
}
/*
	this fonction the parsing list
	free the char ** needed and
	close the 2 fd in & out if needed w/ xclose
*/