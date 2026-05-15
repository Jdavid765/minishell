/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:48:54 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/09 19:45:10 by canoduran        ###   ########.fr       */
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
				free(tmp->value);
				tmp->value = line;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}


