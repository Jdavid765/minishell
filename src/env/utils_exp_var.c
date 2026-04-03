/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exp_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 19:07:49 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/03 19:11:34 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

char	*strip_quotes(char *str)
{
	int		len;
 
	len = ft_strlen(str);
	return (ft_substr(str, 1, len - 2));
}

void	free_expand(char *tmp, char *value, char *before)
{
	if (tmp)
		free(tmp);
	if (value)
		free(value);
	if (before)
		free(before);
}
