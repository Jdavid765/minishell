/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_setup_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:58:52 by canoduran         #+#    #+#             */
/*   Updated: 2026/05/19 21:01:52 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_setup_env(char *key, char *value, t_env *head)
{
	if (key)
		free(key);
	if (value)
		free(value);
	clean_env_list(head);
}
