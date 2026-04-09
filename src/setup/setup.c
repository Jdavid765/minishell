/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/19 16:26:10 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup(t_all *all, char **env)
{
	init_original_signals(all);
	if (setup_signal(all))
		return (1);
	if (setup_env(all, env))
		return (1);
	*get_status() = 0;
	if (!all->path)
	{
		all->path = search_path(all);
		if (!all->path)
			return (1);
	}
	return (0);
}
/*
	this fonctions make all the setups needed before the main loop
*/