/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/09 19:07:22 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_all	all;

	if (!setup(&all))
		return (1);
	main_loop();
	clean_exit();
	return (0);
}
/*
	the all struct contain all the others structs.
	setup() is for all the setup that needs to be done before
	main_loop() is the place where the main loop with readline is done
	clean_exit() is for check that everthing has been clean
*/
