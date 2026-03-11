/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfiora-d <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:57:06 by nfiora-d          #+#    #+#             */
/*   Updated: 2025/10/03 12:43:43 by nfiora-d         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
