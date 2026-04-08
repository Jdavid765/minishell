/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/07 15:18:43 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	bullshit(t_all *all)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = all->token;
	while (tmp)
	{
		printf("token nbr %d\n", i);
		printf("value == %s\n", tmp->value);
		printf("type == %d\n", tmp->type);
		printf("====================\n");
		tmp = tmp->next;
		i++;
	}
	clean_token_list(all->token);
	all->token = NULL;
}*/

/*void	look_parser(t_all *all)
{
	t_parser	*head;
	int			i;
	int			x;

	head = all->parser;
	if (!head)
		return ;
	i = 0;
	x = 1;
	while (head)
	{
		while (head->cmd_and_args[i])
		{
			printf("node=%d | cmd = %s\n", x, head->cmd_and_args[i]);
			i++;
		}
		x++;
		i = 0;
		head = head->next;
	}
}*/

int	main_loop(t_all *all)
{
	char	*rl;
	int		value;

	while (1)
	{
		// rl_on_new_line();
		rl = readline("Minishell > ");
		if (!rl)
		{
			printf("exit\n");
			clean_exit(all, all->exit_status);
		}
		tokenizer(rl, all);
		if (check_exp_var(all))
			return (1);
		if ((value = parse_token(all)) == 10)
			printf("Syntax Errors\n");
		executor(all);
		clean_loop(all);
		add_history(rl);
		if (rl)
			free(rl);
	}
	return (0);
}
/*
	The primary shell loop that manages:
	user input, tokenization, parsing,
	execution, and cleanup 
*/

int	main(int ac, char **av, char **env)
{
	t_all	all;

	if (ac != 1 || av[0] == NULL)
		return (1);
	ft_bzero(&all, sizeof(t_all));
	if (setup(&all, env))
		return (1);
	if (main_loop(&all) == 1)
		clean_exit(&all, 1);
	clean_exit(&all, 0);
	return (0);
}
/*
	the all struct contain all the others structs.
	setup() is for all the setup that needs to be done before
	main_loop() is the place where the main loop with readline is done
	clean_exit() is for check that everthing has been clean
*/
