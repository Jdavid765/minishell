/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:48:54 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/14 14:08:59 by canoduran        ###   ########.fr       */
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
	if (ct_key == 1)
		return (NULL);
	line = malloc(sizeof(char) * ct_key);
	if (!line)
		return (NULL);
	while (env[i] && env[i] != '=')
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
	if (!found)
		return (ft_strdup(""));
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

int	shlvl_add(t_env **ft_env)
{
	t_env	*tmp;
	char	*line;
	int		increment_shlvl;

	tmp = *ft_env;
	while (tmp)
	{
		if (tmp->key[0] == 'S')
		{
			if (ft_compare(tmp->key, "SHLVL") == 0)
			{
				increment_shlvl = ft_atoi(tmp->value) + 1;
				line = ft_itoa(increment_shlvl);
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
	if (shlvl_add(&head))
		return (1);
	if (check_path(&head))
		return (1);
	all->env = head;
	return (0);
}
