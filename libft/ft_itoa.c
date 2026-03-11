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

long	nb_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		sign;
	int		len;
	long	nb;

	nb = (unsigned long)n;
	sign = 0;
	res = malloc(sizeof(char) * (nb_len(nb) + 1));
	if (!res)
		return (NULL);
	len = nb_len(nb);
	res[len] = 0;
	if (nb < 0)
	{
		nb *= -1;
		sign = 1;
		res[0] = '-';
	}
	while (len > sign)
	{
		res[len - 1] = '0' + (nb % 10);
		nb = nb / 10;
		len--;
	}
	return (res);
}
