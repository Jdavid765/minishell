/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 22:38:03 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/02 00:02:41 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

char	*strip_quotes(char *str)
{
	int		len;

	len = ft_strlen(str);
	return (ft_substr(str, 1, len - 2));
}

char	*in_env(char *line, t_all *all)
{
	if (!line)
		return (NULL);
	t_env		*head;

	head = all->env;
	line++;
	while (head)
	{
		if (head->key[0] == line[0])
		{
			if (!ft_compare(head->key, line))
				return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}

int	check_dollar(t_token *token, t_all *all)
{
	if (!token)
		return (1);
	char	*tmp;

	tmp = NULL;
	if (token->value[0] == '$' && token->value[1] != '\0')
	{
		if ((tmp = in_env(token->value, all)))
		{
			free(token->value);
			token->value = ft_strdup(tmp);
			printf("%s\n", token->value);
		}
		else
		{
			free(token->value);
			token->value = ft_strdup(" ");
		}
	}
	return (0);
}

int	search_quotes(t_token *token, int ascii)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = token->value;
	tmp++;
	while (tmp[i])
	{
		if (tmp[i] == ascii)
			return (printf("found\n"), 0);
		i++;
	}
	return (1);
}

int		quotes(t_token *token, t_all *all)
{
	char	*tmp;

	if (!token)
		return (1);
	if (token->value[0] == 34)
	{
		if (!search_quotes(token, 34))
		{
			tmp = strip_quotes(token->value);
			free(token->value);
			token->value = tmp;
			if (token->value[0] == '$')
			{
				if (check_dollar(token, all))
					return (1);
			}
		}
	}
	else if (token->value[0] == 39)
	{
		if (!search_quotes(token, 39))
		{
			tmp = strip_quotes(token->value);
			free(token->value);
			token->value = tmp;
		}
	}
	return (0);
}

int	check_sign(t_token *token, t_all *all)
{
	if (token->value[0] == 34 || token->value[0] == 39)
	{
		if (quotes(token, all))
			return (1);
	}
	else if (token->value[0] == '$')
	{
		if (check_dollar(token, all))
			return (1);
	}
	return (0);
}

int	check_exp_var(t_all *all)
{
	t_token		*head;

	head = all->token;
	while (head)
	{
		if (check_sign(head, all))
			return (1);
		head = head->next;
	}
	return (0);
}
