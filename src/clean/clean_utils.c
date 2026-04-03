/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:56:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/28 23:43:53 by canoduran        ###   ########.fr       */
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
	if (!*strs)
		return ;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	free_all(t_all *all)
{
	clean_cmd_list(all->parser);
	all->parser = NULL;
	clean_token_list(all->token);
	all->token = NULL;
}

/*
	clean a char **
	wierd this that the char ** can't be named tab
*/