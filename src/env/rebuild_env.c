/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:48:54 by canoduran         #+#    #+#             */
/*   Updated: 2026/06/03 00:06:02 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**re_build_env(t_env *head, char **new_env)
{
	int		i;
	t_env	*tmp;

	i = count_env_list(head);
	tmp = head;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[i] = NULL;
	i = 0;
	while (tmp)
	{
		new_env[i] = join_env_value(tmp);
		if (!new_env[i])
			return (free_tab(new_env), NULL);
		i++;
		tmp = tmp->next;
	}
	return (new_env);
}
/*
	this fonction rebuild the env with the t_env_list
	this fonction is needed because of the export/unset builtin
*/

char	*join_env_value(t_env *current)
{
	char	*key_and_value;
	int		s1_len;
	int		s2_len;
	int		check_size;

	s1_len = ft_strlen(current->key);
	if (!current->value)
		return (ft_strdup(current->key));
	s2_len = ft_strlen(current->value);
	key_and_value = malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!key_and_value)
		return (NULL);
	ft_strlcpy(key_and_value, current->key, (s1_len + s2_len + 2));
	ft_strlcat(key_and_value, "=", (s1_len + s2_len + 2));
	check_size = (int)ft_strlcat(key_and_value, current->value,
			(s1_len + s2_len + 2));
	if (check_size != (s1_len + s2_len + 1))
		return (free(key_and_value), NULL);
	return (key_and_value);
}
/*
	this fonction malloc a string and cat
	<key> + '=' + <value> , inside a t_env node.
	return NULL if fail
*/

int	count_env_list(t_env *head)
{
	int		i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
/*
	count nbr of nodes env_list have
	and returns it
*/