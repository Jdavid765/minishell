/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:59:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/10 16:38:37 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int	search_pwd(char *key, char *value)
{
	char	*line;

	line = getcwd(NULL, 0);
	if (!line)
		return (perror("getcwd :"), 1);
	key = ft_strdup("PWD");
	if (!key)
		return (perror("Malloc :"), 1);
	value = ft_strdup(line);
	if (!value)
		return (perror("Malloc :"), 1);
	return (0);
}

int	create_SHLVL(char *key, char *value)
{
	key = ft_strdup("SHLVL");
	if (!key)
		return (perror("Malloc :"), 1);
	value = ft_strdup("1");
	if (!value)
		return (perror("Malloc :"), 1);
	return (0);
}

int	create_env(t_all *all)
{
	t_env	*head;
	t_env	*current;
	char	*key;
	char	*value;
	
	head = NULL;
	key = NULL;
	value = NULL;
	if (search_pwd(key, value))
		return (1);
	current = ft_node_env(key, value);
	if (!current)
		return (1);
	ft_add_back_env(&head, current);
	if (create_SHLVL(key, value))
		return (1);
	current = ft_node_env(key, value);
	if (!current)
		return (1);
	ft_add_back_env(&head, current);
	all->env = head;
	return (0);
}
