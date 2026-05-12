/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_exp_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:49:38 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/07 23:07:06 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*in_env(char *line, t_all *all)
{
	t_env	*head;

	if (!line)
		return (NULL);
	head = all->env;
	line++;
	while (head)
	{
		if (!ft_compare(line, head->key))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

char	*get_var_value(char *dollar, t_all *all, int *i)
{
	char	*var;
	char	*value;

	if (dollar[1] == '?')
	{
		*i = 2;
		return (ft_itoa(*get_status()));
	}
	*i = 1;
	if (!dollar[*i] || dollar[*i] == ' ' || dollar[*i] == '"')
		return (ft_strdup("$"));
	while (dollar[*i] && ft_isalnum(dollar[*i]))
		(*i)++;
	if (*i == 1)
		return ((*i)++, ft_strdup(""));
	var = ft_substr(dollar, 0, *i);
	value = in_env(var, all);
	free(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_in_str(char *str, t_all *all)
{
	char	*result;
	char	*before;
	char	*value;
	char	*tmp;
	int		i;
	int		var_len;

	result = ft_strdup(str);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1] != '\0' && result[i + 1] != ' ')
		{
			before = ft_substr(result, 0, i);
			value = get_var_value(&result[i], all, &var_len);
			tmp = ft_strjoin(before, value);
			free(before);
			before = result;
			result = ft_strjoin(tmp, &before[i + var_len]);
			i = i + ft_strlen(value);
			free_expand(tmp, value, before);
		}
		else
			i++;
	}
	return (result);
}
/*
int	replace_dollar(t_token *token, t_all *all)
{
	char	*tmp;

	if (token->value[1] == '?')
	{
		free(token->value);
		token->value = ft_itoa(*get_status() = 0);
		if (!token->value)
			return (1);
	}
	else if ((tmp = in_env(token->value, all)))
	{
		free(token->value);
		token->value = ft_strdup(tmp);
		if (!token->value)
			return (1);
	}
	else
	{
		free(token->value);
		token->value = ft_strdup("");
		if (!token->value)
			return (1);
	}
	return (0);
}*/
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

int	check_dollar(t_token *token, t_all *all)
{
	char	*tmp;

	if (!token)
		return (1);
	tmp = expand_in_str(token->value, all);
	if (!tmp)
		return (1);
	
	if (ft_strchr(tmp, ' '))
	{
		if (split_expanded_token(token, tmp))
			return (free(tmp), 1);
		free(tmp);
	}
	else
	{
		free(token->value);
		token->value = tmp;
		if (token->value[0] == '\0')
			token->is_valid = false;
	}
	return (0);
}
/*
	the fonction first call the expension once done
	we look if the expended var have space if it's the case then we split

*/