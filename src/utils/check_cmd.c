/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 23:18:14 by canoduran         #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/03/11 18:20:57 by canoduran        ###   ########.fr       */
=======
/*   Updated: 2026/03/11 18:20:15 by canoduran        ###   ########.fr       */
>>>>>>> 813fe0645f5b12a96a491077788d0b863eb99b70
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_cmd(char *rl)
{
	if (ft_compare(rl, "export") == 0)
		printf("Test\n");
	if (ft_compare(rl, "pwd") == 0)
		pwd_builtin();
	if (ft_compare(rl, "exit") == 0)
		exit_builtin((void *)rl);
	return ;
}
