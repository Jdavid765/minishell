/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:48:54 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/07 23:39:15 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*before_path_check(t_env *env, char *cmd)
{
	char	*path_checker;
	char	*tmp_cmd;

	if (ft_strchr(cmd, '/'))
	{
		path_checker = access_check("", cmd);
		return (path_checker);
	}
	tmp_cmd = ft_strjoin("/", cmd);
	if (!tmp_cmd)
		return (NULL);
	path_checker = path_check(env, tmp_cmd);
	free(tmp_cmd);
	return (path_checker);
}
/*
	this fonction is the main fonction for 
	all the path checks.
	handle absolute or relative path
	return NULL if access fail/wrong path
*/

char	*path_check(t_env *env, char *cmd)
{
	char	*path_str;
	char	**all_path;
	char	*path_checker;

	path_str = find_path_in_env(env);
	if (!path_str)
		return (access_check("", cmd));
	all_path = ft_split(path_str, ':');
	if (!all_path)
		return (NULL);
	path_checker = path_exist(all_path, cmd);
	free_tab(all_path);
	return (path_checker);
}
/*
	get the path in env or try without if not found
	split the path
*/

char	*path_exist(char **all_path, char *path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (all_path && all_path[i])
	{
		tmp = access_check(all_path[i], path);
		if (tmp != NULL)
			return (tmp);
		i++;
	}
	return (NULL);
}
/*
	this fonction loop all the path
	return NULL if no path is found
*/

char	*access_check(char *all_path, char *path)
{
	char	*tmp;

	tmp = ft_strjoin(all_path, path);
	if (!tmp)
		return (NULL);
	if (!access(tmp, F_OK | X_OK))
		return (tmp);
	free(tmp);
	return (NULL);
}
/*
	this fonction check with access if the path exist or not
	free tmp if access fait or return the valid path
*/

char	*find_path_in_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PATH", 5))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
/*
	this fonction find the path in a t_env list
*/
