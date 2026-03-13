/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:41:49 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/13 15:42:03 by canoduran        ###   ########.fr       */
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

char *put_in_key(char *env)
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
t_env	*setup_env(char **env)
{
	t_env 	*head;
	t_env 	*current;
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
			return (NULL);
		current = ft_newnode(key, value);
		
		ft_add_back(&head, current);
		i++;
	}
	return (head);
}