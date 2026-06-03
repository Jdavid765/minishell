/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:03:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/06/03 17:44:19 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_child(t_all *all, t_token *tok, int *fd)
{
	int	ret;

	signal(SIGINT, heredoc_sig_handler);
	xclose(&fd[0]);
	ret = loop_heredoc(all, tok, fd);
	xclose(&fd[1]);
	clean_exit(all, ret);
}
