/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:59:29 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/17 13:45:56 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_builtin(t_env **ft_env, char *rl)
{
	t_env	*head;
	t_env	*current;
	char	**line;

	line = ft_split(rl, ' ');
	if (!line)
		return (1);
	current = ft_node_env(line[1], line[3]);
	ft_add_back_env(&*ft_env, current);
	head = *ft_env;
	while(head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return(0);
}
