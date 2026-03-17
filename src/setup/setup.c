/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/13 15:42:41 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*setup(t_all *all, char **env)
{
	t_env	*ft_env;

	if(!setup_signal(all))
		printf("Error");
	ft_env = setup_env(env);
	if (!ft_env)
		return (NULL);
	return (ft_env);
}
/*
	this fonctions make all the setups needed before the main loop
*/