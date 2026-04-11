/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/11 17:09:52 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup(t_all *all, char **env)
{
	if (env[0] == NULL)
	{
		if (create_env(all))
			return (1);
		// all->path = search_path_no_env(all);
		// if (!all->path)
		// 	return (1);
	}
	else
	{
		if (setup_env(all, env))
		return (1);
		all->path = search_path(all);
		if (!all->path)
			return (1);
	}
	init_original_signals(all);
	if (setup_signal(all))
		return (1);
	*get_status() = 0;
	return (0);
}
/*
	this fonctions make all the setups needed before the main loop
*/