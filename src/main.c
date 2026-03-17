/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 14:45:57 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	bullshit(t_all *all)
{
	int i = 1;

	while(all->token)
	{
		printf("token nbr %d\n", i);
		printf("value == %s\n", all->token->value);
		printf("type == %d\n", all->token->type);
		printf("====================");
		all->token = all->token->next;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		i++;
	}
	// printf("");
}

int	main_loop(t_all *all, char **env)
{
	char	*rl;

	if (env)
		printf("!\n");

	while (1)
	{
		if ((rl = readline("Minishell > ")) == NULL)
			return (1);
		tokenizer(rl, all);
		bullshit(all);
		check_cmd(rl, all);
		add_history(rl);
		if (rl)
			free(rl);
	}
	return (0);
}
/*
	The best choice in the loop is call function 
	to compare if the line write in rl = is command or built in
	and execute the command or built in if is it.
	I propose this for not poluate the code.
*/




int	main(int ac, char **av, char **env)
{
	t_all	all;
	if (ac != 1 || av[0] == NULL)
		return (1);
	ft_bzero(&all, sizeof(t_all));
	if (!setup(&all, env))
		return (1);
	if (main_loop(&all, env) == 1)
		return (1); //free
	return (0);
}
/*
	the all struct contain all the others structs.
	setup() is for all the setup that needs to be done before
	main_loop() is the place where the main loop with readline is done
	clean_exit() is for check that everthing has been clean
*/
