/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:41:49 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 14:44:05 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ct_key_value(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

char	*put_in_key(char *env)
{
	int		i;
	int		ct_key;
	char	*line;

	i = 0;
	ct_key = ct_key_value(env) + 1;
	line = malloc(sizeof(char) * ct_key);
	if (!line)
		return (NULL);
	while (env[i] != '=')
	{
		line[i] = env[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*put_in_value(char *env)
{
	int		i;
	char	*found;
	char	*line;
	int		ct_value;

	i = 0;
	found = ft_strchr(env, '=');
	found++;
	ct_value = (int)ft_strlen(found) + 1;
	line = malloc(sizeof(char) * ct_value);
	if (!line)
		return (NULL);
	while (found[i])
	{
		line[i] = found[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	add_shlvl(t_env **ft_env)
{
	t_env	*tmp;
	char	*line;

	tmp = *ft_env;
	while (tmp)
	{
		if (tmp->key[0] == 'S')
		{
			if (ft_compare(tmp->key, "SHLVL") == 0)
			{
				line = ft_strdup("2");
				if (!line)
					return (1);
				ft_lst_del_env(tmp);
				tmp->value = line;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	setup_env(t_all *all, char **env)
{
	t_env	*head;
	t_env	*current;
	int		i;
	char	*key;
	char	*value;

	i = 0;
	head = NULL;
	while (env[i])
	{
		key = put_in_key(env[i]);
		value = put_in_value(env[i]);
		if (!key || !value)
			return (1);
		current = ft_node_env(key, value);
		if (!current)
			return (1);
		ft_add_back_env(&head, current);
		i++;
	}
	if (add_shlvl(&head))
		return (1);
	all->env = head;
	return (0);
}
/*clean liste si ca echoue avec clean_env_list(),*/
