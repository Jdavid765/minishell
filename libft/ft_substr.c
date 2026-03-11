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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	size;

	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
	{
		len = size;
	}
	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	while (s[i])
	{
		if (i == start)
		{
			ft_strlcpy(sub, &s[start], len + 1);
		}
		i++;
	}
	return (sub);
}
