/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:59:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/11 18:25:13 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	return (all->env = head, 0);
}
/*
	this fonction set up the env link list from the main envp
	and add shlvl and path if they are needed
	return 1 if an error occur
*/

int	create_env(t_all *all)
{
	t_env	*head;

	head = NULL;
	if (search_pwd(&head))
		return (1);
	if (create_shlvl(&head))
		return (1);
	if (create_path_no_env(&head))
		return (1);
	all->env = head;
	// look_env(all);
	return (0);
}
/*
	this fonction create a basic env list
	used if the program is launched without envp (env -i)
*/

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
/*
	this fonction get the current working directory
	and create a new PWD node for the env list
*/

int	create_shlvl(t_env **head)
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
/*
	this fonction create a new node SHLVL set to 1
	used when we start the shell without env
*/

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
/*
	this fonction create a basic path for the '_' variable
	if no env is provided at the start
*/
