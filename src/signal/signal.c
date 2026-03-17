/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/11 23:37:09 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
/*
	this fonction handle le SINgint signal who is enabled with CTRL + C
	the 3 rl_ fonctions helps readline to put a newline if the shortcut is used
*/


int	setup_signal(t_all *all)
{
	all->sig.sa.sa_handler = sigint_handler;
	if (sigemptyset(&all->sig.sa.sa_mask))
		return (perror("sigemptyset"), 1);
	all->sig.sa.sa_flags = 0;
	if (sigaddset(&all->sig.sa.sa_mask, SIGQUIT) == -1)
		return (perror("sigaddset"), 1);
	if (sigaction(SIGINT, &all->sig.sa, NULL) == -1)
		return (perror("sigaction"), 1);
	return (0);
}
/*
	this fonction setup the sa_mask set and the flags to 
	prevent any garbage value.
	sigaction enable the catch of the SIGINT signal
*/