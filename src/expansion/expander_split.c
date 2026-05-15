/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:49:38 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/07 23:07:06 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	split_expanded_token(t_token *curr_node, char *expanded_str)
{
	char	**words;
	t_token	*next_save;
	bool	orig_space;

	orig_space = curr_node->space_after;
	words = ft_split(expanded_str, ' ');
	if (!words)
		return (1);
	if (!words[0])
	{
		free(curr_node->value);
		curr_node->value = ft_strdup("");
		curr_node->is_valid = false;
		curr_node->space_after = orig_space;
		return (free_tab(words), 0);
	}
	free(curr_node->value);
	curr_node->value = ft_strdup(words[0]);
	next_save = curr_node->next;
	if (insert_split_words(curr_node, words, next_save, orig_space))
		return (free_tab(words), 1);
	free_tab(words);
	return (0);
}

int	insert_split_words(t_token *curr_node, char **words, t_token *next_save, bool orig_space)
{
	int		i;
	t_token	*new_node;

	i = 1;
	while (words[i])
	{
		new_node = create_token_node(WORD, ft_strdup(words[i]));
		if (!new_node)
			return (1);
		curr_node->space_after = true;
		curr_node->next = new_node;
		new_node->prev = curr_node;
		curr_node = new_node;
		i++;
	}
	curr_node->space_after = orig_space;
	curr_node->next = next_save;
	if (next_save)
		next_save->prev = curr_node;
	return (0);
}
