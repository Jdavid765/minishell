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

size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_free(char **tab, int j)
{
	while (j > 0)
		free(tab[--j]);
	free(tab);
}

int	ft_new_word(char const *s, char c, char **tab)
{
	size_t	j;
	size_t	i;
	size_t	letter;
	size_t	pos;

	j = 0;
	i = 0;
	while (j < ft_count_words(s, c))
	{
		letter = 0;
		while (s[i] == c && s[i])
			i++;
		pos = i;
		while (s[i] != c && s[i])
		{
			letter++;
			i++;
		}
		tab[j] = ft_strndup(&s[pos], letter);
		if (!tab[j])
			return (ft_free(tab, (int)(j)), 0);
		j++;
	}
	tab[j] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	if (!ft_new_word(s, c, tab))
		return (NULL);
	return ((char **)tab);
}

