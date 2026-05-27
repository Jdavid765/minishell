/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:14:06 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/11 18:24:34 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_input(t_all *all)
{
	char	*rl;

	rl_on_new_line();
	if (isatty(STDIN_FILENO))
		rl = readline("Minishell > ");
	else
		rl = readline(NULL);
	if (!rl)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDERR_FILENO);
		clean_exit(all, *get_status());
	}
	return (rl);
}
/*
	this function handles user input using readline.
	it checks if the input comes from a terminal (isatty)
	to avoid printing the prompt in a pipe.
	if rl is NULL (Ctrl-D), it exits the shell.
*/

static void	handle_execution(t_all *all, int value)
{
	if (value == 10 || value == 5)
	{
		ft_putstr_fd("syntax error near unexpected token \n", STDERR_FILENO);
		*get_status() = 2;
	}
	else if (value == 0)
	{
		executor(all);
	}
}
/*
	this function checks the return value of the parser.
	if a syntax error is found (5 or 10), it prints an error
	and sets the status to 2.
	otherwise (0), it calls the executor to run the commands.
*/

int	main_loop(t_all *all)
{
	char	*rl;
	int		value;

	while (1)
	{
		rl = get_input(all);
		if (tokenizer(rl, all) == 0)
		{
			if (check_exp_var(all))
			{
				if (rl)
					free(rl);
				return (1);
			}
			join_adjacent_tokens(all);
			value = parse_token(all);
			handle_execution(all, value);
		}
		clean_loop(all);
		if (rl && rl[0])
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
	The entry point of the minishell program.
	It initializes the main structures and launches the core loop.
*/
