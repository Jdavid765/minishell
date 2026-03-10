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

void	pwd_builtin(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	write(0, pwd, strlen(pwd));
	write(0, "\n", 1);
}