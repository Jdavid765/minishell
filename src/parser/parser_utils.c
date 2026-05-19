/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:56:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/02 00:33:04 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pipe(t_parser **cmd, t_token *tok, int *index, char *path)
{
	t_parser	*new_cmd;
	int			nb_words;

	if (!tok->next)
		return (10);
	else if (tok->next->type == PIPE)
		return (10);
	(*cmd)->cmd_and_args[*index] = NULL;
	new_cmd = ft_node_pars(path);
	if (!new_cmd)
		return (1);
	ft_addback_parse(cmd, new_cmd);
	*cmd = (*cmd)->next;
	nb_words = count_words(tok->next) + 1;
	(*cmd)->cmd_and_args = ft_calloc(nb_words, sizeof(char *));
	if (!(*cmd)->cmd_and_args)
		return (1);
	*index = 0;
	return (0);
}
/*
	this fonction creates a new parser node for the next command in the pipeline
	and prepares the command arguments array
*/

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
/*
	this fonction searches for the PATH variable in the environment list
	and returns its string value, or NULL if not found
*/

char	*search_path_no_env(t_all *all)
{
	t_env	*head;

	head = all->env;
	while (head)
	{
		if (head->key[0] == '_')
		{
			if (!ft_compare(head->key, "_"))
				return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}
/*
	this fonction searches for the fallback '_' variable
	when no environment is provided at launch
*/
