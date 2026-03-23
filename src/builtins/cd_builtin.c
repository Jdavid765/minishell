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

//////////////////////////////////////////
/*tmp fonction for test cmd*/
t_cmd	*test(t_cmd *cd_cmd, char *rl)
{
	char **toto = ft_split(rl, ' ');
	if (!cd_cmd)
	{
		cd_cmd = malloc(sizeof(t_cmd));
		if (!cd_cmd)
		{
			perror("error on t_cmd malloc");
			return (NULL);
		}
		cd_cmd->cmd_and_args = toto;
		cd_cmd->next = NULL;
		cd_cmd->prev = NULL;
		return (cd_cmd);
	}
	return (NULL);
}

////////////////////////////////////////

int	cd_builtin(t_all *all, t_cmd *cd_cmd, char *rl)
{
	cd_cmd = test(cd_cmd, rl);// a enlever pour test
	if (!cd_cmd->cmd_and_args[1])
		return (0);
	if (chdir(cd_cmd->cmd_and_args[1]) == -1)
		return (1);
	if (update_env(all))
		return (1);
	clean_cmd_list(cd_cmd);
	cd_cmd = NULL;
	return (0);
}

/*
	this fonction change the current working directory
	if success return 0
	if an erro occur 1 is return
*/

int	update_env(t_all * all)
{
	t_env	*pwd_node;
	t_env	*oldpwd_node;

	pwd_node = find_pwd_node(all);
	if (!pwd_node)
		return (1);
	oldpwd_node = find_oldpwd_node(all);
	if (!oldpwd_node)
		return (1);
	free(oldpwd_node->value);
	oldpwd_node->value = pwd_node->value;
	pwd_node->value = getcwd(NULL, 0);
	if (!pwd_node->value)
		return (perror("getcwd :"), 1);
	return (0);
}

/*
	this fonction change oldpwd and pwd in the env
	and replace their value to the new ones
*/

t_env	*find_pwd_node(t_all * all)
{
	t_env	*current;

	current = all->env;
	while(current)
	{
		if (ft_strncmp("PWD", current->key, strlen(current->key)) == 0)
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
		if (strncmp("OLDPWD", current->key, strlen(current->key)) == 0)
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
