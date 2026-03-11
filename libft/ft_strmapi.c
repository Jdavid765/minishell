/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfiora-d <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:57:06 by nfiora-d          #+#    #+#             */
/*   Updated: 2025/10/03 12:43:43 by nfiora-d         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	str = (char *)malloc(sizeof(char) *(ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < (unsigned int)ft_strlen(s))
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str[i] = 0, str);
}
