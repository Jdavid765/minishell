/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:59:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/12 14:03:23 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int	search_pwd(t_env **head)
{
	char	*line;
	char	*key;
	char	*value;
	t_env	*current;

	line = getcwd(NULL, 0);
	if (!line)
		return (perror("getcwd :"), 1);
	key = ft_strdup("PWD");
	if (!key)
		return (perror("Malloc :"), 1);
	value = ft_strdup(line);
	if (!value)
		return (perror("Malloc :"), 1);
	current = ft_node_env(key, value);
	if (!current)
		return (1);
	ft_add_back_env(head, current);
	return (0);
}

int	create_SHLVL(t_env **head)
{
	char	*key;
	char	*value;
	t_env	*current;

	key = NULL;
	value = NULL;
	key = ft_strdup("SHLVL");
	if (!key)
		return (perror("Malloc :"), 1);
	value = ft_strdup("1");
	if (!value)
		return (perror("Malloc :"), 1);
	current = ft_node_env(key, value);
	if (!current)
		return (1);
	ft_add_back_env(head, current);
	return (0);
}

int	create_path_no_env(t_env **head)
{
	char	*key;
	char	*value;
	t_env	*current;

	key = NULL;
	value = NULL;
	key = ft_strdup("_");
	if (!key)
		return (1);
	value = ft_strdup("/usr/bin/");
	if (!value)
		return (1);
	current = ft_node_env(key, value);
	if (!current)
		return (1);
	ft_add_back_env(head, current);
	return (0);
}

int	create_env(t_all *all)
{
	t_env	*head;
	
	head = NULL;
	if (search_pwd(&head))
		return (1);
	if (create_SHLVL(&head))
		return (1);
	if (create_path_no_env(&head))
		return (1);
	all->env = head;
	return (0);
}
