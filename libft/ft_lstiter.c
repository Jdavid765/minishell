/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfiora-d <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:08:16 by nfiora-d          #+#    #+#             */
/*   Updated: 2025/10/14 16:08:23 by nfiora-d         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f || !lst)
		return ;
	while (lst->next)
	{
		f(lst->content);
		lst = lst->next;
	}
	f(lst->content);
}
