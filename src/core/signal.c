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
	*get_status() = 130;
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
	all->sig.sa_quit.sa_handler = SIG_IGN;
	if (sigemptyset(&all->sig.sa_quit.sa_mask))
		return (perror("sigemptyset"), 1);
	all->sig.sa_quit.sa_flags = 0;
	if (sigaction(SIGINT, &all->sig.sa, NULL) == -1)
		return (perror("sigaction SIGINT"), 1);
	if (sigaction(SIGQUIT, &all->sig.sa_quit, NULL) == -1)
		return (perror("sigaction SIGQUIT"), 1);
	return (0);
}
/*
	setup custom handler for SIGINT and ignore SIGQUIT
	save the original signals to restore them later in child
*/

void	restore_original_signals(t_all *all)
{
	sigaction(SIGINT, &all->sig.sa_orig_int, NULL);
	sigaction(SIGQUIT, &all->sig.sa_orig_quit, NULL);
}
/*
	restore default signals for the child process
	before execve so commands can be killed normally
*/

void	init_original_signals(t_all *all)
{
	ft_bzero(&all->sig.sa_orig_int, sizeof(struct sigaction));
	all->sig.sa_orig_int.sa_handler = SIG_DFL;
	sigemptyset(&all->sig.sa_orig_int.sa_mask);
	all->sig.sa_orig_int.sa_flags = 0;

	ft_bzero(&all->sig.sa_orig_quit, sizeof(struct sigaction));
	all->sig.sa_orig_quit.sa_handler = SIG_DFL;
	sigemptyset(&all->sig.sa_orig_quit.sa_mask);
	all->sig.sa_orig_quit.sa_flags = 0;
}

void	ignore_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
