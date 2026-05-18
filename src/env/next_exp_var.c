/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_exp_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:49:38 by canoduran         #+#    #+#             */
/*   Updated: 2026/05/18 19:55:09 by canoduran        ###   ########.fr       */
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

char	*expand_dollar(char *result, int *i, t_all *all)
{
	char	*before;
	char	*value;
	char	*tmp;
	int		var_len;

	before = ft_substr(result, 0, *i);
	value = get_var_value(&result[*i], all, &var_len);
	tmp = ft_strjoin(before, value);
	free(before);
	before = result;
	result = ft_strjoin(tmp, &before[*i + var_len]);
	*i = *i + ft_strlen(value);
	free_expand(tmp, value, before);
	return (result);
}

char	*expand_in_str(char *str, t_all *all)
{
	char	*result;
	int		i;

	result = ft_strdup(str);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1] != '\0' && result[i + 1] != ' ')
			result = expand_dollar(result, &i, all);
		else
			i++;
	}
	return (result);
}

int	check_dollar(t_token *token, t_all *all)
{
	char	*tmp;

	if (!token)
		return (1);
	tmp = expand_in_str(token->value, all);
	if (!tmp)
		return (1);
	free(token->value);
	token->value = tmp;
	if (token->value[0] == '\0')
		token->is_valid = false;
	return (0);
}
