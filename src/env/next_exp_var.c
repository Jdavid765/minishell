/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_exp_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:49:38 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/03 20:48:59 by canoduran        ###   ########.fr       */
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
		return (ft_itoa(all->exit_status));
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

int	replace_dollar(t_token *token, t_all *all)
{
	char	*tmp;

	if (token->value[1] == '?')
	{
		free(token->value);
		token->value = ft_itoa(all->exit_status);
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
}

int	check_dollar(t_token *token, t_all *all)
{
	if (!token)
		return (1);
	if (token->value[0] == '$' && token->value[1] != '\0')
	{
		if (replace_dollar(token, all))
			return (1);
	}
	return (0);
}
