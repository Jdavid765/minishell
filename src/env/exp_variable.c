/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 22:38:03 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/24 11:16:26 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

void	create_exp_var(char *line, t_all *all)
{
	t_exp_var	*head;
	t_exp_var	*current;
	char		*value;
	char		*key;

	head = NULL;
	value = ft_strchr(line, '=');
	if (!value)
		return ;
	value++;
	if (!ft_isalpha(line[0]))
		return ;
	key = put_in_key(line);
	if (!key)
		return ;
	current = node_exp_var(key, value);
	ft_add_back_exp(&head, current);
	all->exp_var = head;
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

char	*in_exp_var(char *line, t_all *all)
{
	if (!line)
		return (NULL);
	t_exp_var	*head;

	head = all->exp_var;
	line++;
	while (head)
	{
		if (head->key[0] == line[0])
		{
			if (!ft_compare(line, head->key))
				return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}

int	check_exp_var(t_all *all)
{
	t_token		*head;
	char		*tmp;

	head = all->token;
	while (head)
	{
		if (head->value[0] == '$' && head->value[1] != '\0')
		{
			if ((tmp = in_env(head->value, all)) 
				|| ((tmp = in_exp_var(head->value, all))))
			{
				free(head->value);
				head->value = ft_strdup(tmp);
				printf("%s\n", head->value);
				break ;
			}
			else
				head->value = ft_strdup(" ");
		}
		else
			create_exp_var(head->value, all);
		head = head->next;
	}
	return (0);
}
