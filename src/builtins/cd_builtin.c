/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:41:49 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/26 21:27:32 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_builtin(t_all *all, t_parser *cd_cmd)
{
	if (!cd_cmd->cmd_and_args[1])
		return (go_to_home_dir(all));
	if (chdir(cd_cmd->cmd_and_args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(cd_cmd->cmd_and_args[1]);
		return (1);
	}
	if (update_env(all))
		return (1);
	cd_cmd = NULL;
	return (0);
}

/*
	this fonction change the current working directory
	if success return 0
	if an erro occur 1 is return
*/


int	go_to_home_dir(t_all *all)
{
	t_env	*current;
	char	*home_path;

	current = all->env;
	home_path = NULL;
	while (current)
	{
		if (ft_strncmp("HOME", current->key, 5) == 0)
		{
			home_path = current->value;
			break ;
		}
		current = current->next;
	}
	if (!home_path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home_path) == -1)
		return (perror("minishell: cd"), 1);
	return (update_env(all));
}

/*
	This function handles the case where 'cd' is called without arguments.
	It looks up the HOME variable and changes the current directory.
	Returns 0 on success, 1 on error.
*/

int	update_env(t_all *all)
{
	t_env	*pwd_node;
	t_env	*oldpwd_node;
	char	*new_cwd;

	pwd_node = find_pwd_node(all);
	oldpwd_node = find_oldpwd_node(all);
	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
		return (perror("getcwd"), 1);
	if (oldpwd_node && pwd_node)
	{
		free(oldpwd_node->value);
		oldpwd_node->value = ft_strdup(pwd_node->value); 
	}
	if (pwd_node)
	{
		free(pwd_node->value);
		pwd_node->value = new_cwd;
	}
	else
		ft_add_back_env(&all->env, ft_node_env(ft_strdup("PWD"), new_cwd));
	return (0);
}
/*
	this fonction change oldpwd and pwd in the env
	and replace their value to the new ones 
	if pwd is unset a new node is created for pwd
*/

t_env	*find_pwd_node(t_all * all)
{
	t_env	*current;

	current = all->env;
	while(current)
	{
		if (ft_strncmp("PWD", current->key, 4) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
/*
	this fonction find the PWD node in the env list
	or if not found
*/

t_env	*find_oldpwd_node(t_all * all)
{
	t_env	*current;

	current = all->env;
	while(current)
	{
		if (strncmp("OLDPWD", current->key, 7) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
/*
	like the upper fonction
	this fonction find the OLDPWD node in the env list
	or if not found
*/
