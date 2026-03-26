/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 22:38:03 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/24 14:59:37 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

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

// int		check_quotes(t_token *token)
// {
// }

int	check_exp_var(t_all *all)
{
	t_token		*head;

	head = all->token;
	while (head)
	{
		if (check_dollar(head, all))
			return (1);
		head = head->next;
	}
	return (0);
}
