/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 23:18:14 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/09 23:29:50 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int str_len(char *s)
{
	int i = 0;
	while(s[i])
		i++;
	return (i);
}

/*
	tmp fonction for wait the add of libft
*/

int	pwd_builtin(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (write(0, pwd, strlen(pwd)) == -1)
		return (free(pwd), perror("write pwd error"), 1);
	if (write(0, "\n", 1) == -1)
		return (free(pwd), perror("write pwd error"), 1);
	free(pwd);
	return (0);
}
/*
	pwd is a pointer to the string of the current working directory
	write is used here for safety
	pwd is free at the end because,
	getcwd allocated memory for given line
*/