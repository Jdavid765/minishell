/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 23:08:34 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/03 19:29:59 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_compare(char *rl, char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i + 1] == '\0')
		{
			if (rl[i + 1] != '\0')
				return (1);
		}
		if (string[i] != rl[i])
			return (1);
		i++;
	}
	return (0);
}
/*
	this fonction compares two strings
	returns 0 if they are strictly identical, 1 otherwise
*/

int	*get_status(void)
{
	static int	status;

	return (&status);
}
/*
	this fonction uses a static variable to store and retrieve
	the global exit status securely throughout the minishell
*/
