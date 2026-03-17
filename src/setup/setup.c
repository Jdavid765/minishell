/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 14:39:17 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup(t_all *all, char **env)
{
	if(!setup_signal(all))
		printf("Error");
	if(!setup_env(all, env))
		return (1);
	return (0);
}
/*
	this fonctions make all the setups needed before the main loop
*/