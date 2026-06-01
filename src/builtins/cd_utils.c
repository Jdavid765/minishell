/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 xx:xx:xx by canoduran         #+#    #+#             */
/*   Updated: 2026/06/01 xx:xx:xx by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_pwd_node(t_all *all, char *new_cwd)
{
	t_env	*node;
	char	*key;

	key = ft_strdup("PWD");
	if (!key)
		return (1);
	node = ft_node_env(key, new_cwd);
	if (!node)
		return (free(key), 1);
	ft_add_back_env(&all->env, node);
	return (0);
}
/*
	this function creates and inserts a new PWD node
	into the environment list when PWD has been unset.
	returns 0 on success, 1 if a malloc fails.
*/
