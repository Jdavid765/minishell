/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 23:27:40 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/07 23:38:45 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int	append_node(t_all *all, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (free(key), free(value), 1);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (!all->env)
		return (all->env = new_node, 0);
	current = all->env;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (0);
}

int	update_existing(t_all *all, char *key, char *value, char *arg)
{
	t_env	*current;

	current = all->env;
	while (current)
	{
		if (ft_compare(current->key, key) == 0)
		{
			if (ft_strchr(arg, '='))
			{
				free(current->value);
				current->value = value;
			}
			else
				free(value);
			free(key);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	parse_arg(char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*key = ft_substr(arg, 0, eq - arg);
		*value = ft_strdup(eq + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
	if (!*key)
		return (1);
	return (0);
}

int	is_valid_arg(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (1);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
