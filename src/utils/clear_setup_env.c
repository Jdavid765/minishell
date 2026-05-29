/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_setup_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 13:34:01 by canoduran         #+#    #+#             */
/*   Updated: 2026/05/29 13:42:16 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_setup_env(char *key, char *value, t_env *head)
{
	if (key)
		free(key);
	if (value)
		free(value);
	clean_env_list(head);
}
