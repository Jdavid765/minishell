/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/11 23:59:58 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main_loop(char **env, t_env **ft_env)
{
	char	*rl;

	if (env)
		printf("!\n");

	while (1)
	{
		if ((rl = readline("Prompt > ")) == NULL)
			return (1);
		printf("%s\n", rl);
		check_cmd(rl, ft_env);
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
	t_env	*ft_env;
	if (ac != 1 || av[0] == NULL)
		return (1);
	ft_env = setup(&all, env);
	if (!ft_env)
		return (1);
	if (main_loop(env, &ft_env) == 1)
		return (1);
	return (0);
}
/*
	the all struct contain all the others structs.
	setup() is for all the setup that needs to be done before
	main_loop() is the place where the main loop with readline is done
	clean_exit() is for check that everthing has been clean
*/
