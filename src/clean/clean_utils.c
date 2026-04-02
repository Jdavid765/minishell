/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:56:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 13:48:37 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	xclose(int *fd)
{
	int	return_value;

	if (!fd || *fd < 0)
		return (1);
	return_value = close(*fd);
	*fd = -1;
	return (return_value);
}

/*
	all the credits to 0yech & stellaaash for this fonction 
	pureee genuis frrr
*/

void	free_tab(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/*
	Frees a null-terminated array of strings and the pointer
	to the array itself.
*/

void	clean_loop(t_all *all)
{
	if (all->token)
	{
		clean_token_list(all->token);
		all->token = NULL;
	}
	if (all->parser)
	{
		clean_cmd_list(all->parser);
		all->parser = NULL;
	}
}
/*
	Resets the shell's temporary data structures
	at the end of each iteration to prevent memory leaks
	and command repetition
*/

void	clean_exit(t_all *all, int exit_code)
{
	clean_loop(all);
	
	if (all->env)
	{
		clean_env_list(all->env);
		all->env = NULL;
	}
	if (all->path)
	{
		free(all->path);
		all->path = NULL;
	}
	rl_clear_history();
	exit(exit_code);
}
/*
	this fonction clean all the allocated memory
	like env, tokens, parser and readline history.
	then it exit the program with the given exit_code
*/
