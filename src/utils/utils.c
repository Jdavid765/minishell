/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 23:08:34 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/09 23:13:00 by canoduran        ###   ########.fr       */
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
<<<<<<< HEAD
}
=======
}
>>>>>>> a4d56f6 (adding pwd builtin)
