/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/25 22:58:36 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	bullshit(t_all *all)
{
	int i = 1;

	t_token	*tmp = all->token;

	while(tmp)
	{
		printf("token nbr %d\n", i);
		printf("value == %s\n", tmp->value);
		printf("type == %d\n", tmp->type);
		printf("====================\n");
		tmp = tmp->next;
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		i++;
	}
	// printf("");
}

void	look_parser(t_all *all)
{
	t_parser	*head;
	int			i;

	head = all->parser;
	i = 0;
	while (head)
	{
		while (head->cmd_and_args[i])
		{
			printf("nbr = %s\n", head->cmd_and_args[i]);
			i++;	
		}
		i = 0;
		head = head->next;
	}
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
		if (parse_token(all) == 1)
			return (1);
		if (check_exp_var(all))
			return (1);
		look_parser(all);
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
	if (setup(&all, env))
		return (1);
	if (!all.path)
		if (!(all.path = search_path(&all)))
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
