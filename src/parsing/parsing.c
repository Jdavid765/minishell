/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:56:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/28 23:59:33 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
 
int	append(t_parser *cmd, t_token **tok)
{
	t_token	*tmp;

	tmp = (*tok)->next;
	if (!tmp || tmp->type != WORD)
		return (10);
	if (cmd->fd_out != 1)
		cmd->fd_out = xclose(&cmd->fd_out);
	cmd->fd_out = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd_out < 0)
		return (1);
	return (0);
}
 
int	redir_in(t_parser *cmd, t_token **tok)
{
	t_token	*tmp;

	tmp = (*tok)->next;
	if (!tmp || tmp->type != WORD)
		return (10);
	if (cmd->fd_in != 0)
		cmd->fd_in = xclose(&cmd->fd_in);
	cmd->fd_in = open(tmp->value, O_RDONLY);
	if (cmd->fd_in < 0)
		return (1);
	return (0);
}
 
int	ft_pipe(t_parser **cmd, t_token *tok, int *index, char *path)
{
	t_parser	*new_cmd;
	int			nb_words;
 
	if (!tok->next)
		return (10);
	else if (tok->next->type == PIPE)
		return (5);
	(*cmd)->cmd_and_args[*index] = NULL;
	new_cmd = ft_node_pars(path);
	ft_addback_parse(cmd, new_cmd);
	*cmd = (*cmd)->next;
	nb_words = count_words(tok->next) + 1;
	(*cmd)->cmd_and_args = ft_calloc(nb_words, sizeof(char *));
	if (!(*cmd)->cmd_and_args)
		return (1);
	*index = 0;
	return (0);
}
 
int	parse_loop(t_parser **cmd, t_token *token, char *path)
{
	int		index;
	int		ret;
 
	index = 0;
	ret = 0;
	while (token)
	{
		if (token->type == WORD)
			(*cmd)->cmd_and_args[index++] = ft_strdup(token->value);
		else if (token->type == REDIR_OUT)
			ret = redir_out(*cmd, &token);
		else if (token->type == APPEND)
			ret = append(*cmd, &token);
		else if (token->type == REDIR_IN)
			ret = redir_in(*cmd, &token);
		else if (token->type == PIPE)
			ret = ft_pipe(cmd, token, &index, path);
		if (ret)
			return (ret);
		if (token)
			token = token->next;
	}
	if (*cmd && (*cmd)->cmd_and_args)
		(*cmd)->cmd_and_args[index] = NULL;
	return (0);
}
 
int	parse_token(t_all *all)
{
	t_parser	*head;
	t_parser	*current_cmd;
	t_token		*current_tok;
	int			nb_words;
	int			ret;
 
	if (!all->token)
		return (10);
	current_tok = all->token;
	if (current_tok->type == PIPE)
		return (10);
	head = ft_node_pars(all->path);
	current_cmd = head;
	nb_words = count_words(current_tok) + 1;
	current_cmd->cmd_and_args = ft_calloc(nb_words, sizeof(char *));
	if (!current_cmd->cmd_and_args)
		return (1);
	ret = parse_loop(&current_cmd, current_tok, all->path);
	if (ret == 1 || ret == 10)
		return (ret);
	else if (ret == 5)
		return ((all->parser = head), ret);
	all->parser = head;
	return (0);
}

//add le before path in this function
//for heredoc i need to do one specific
//if one token type after is not a word i need to cancel all tokeniser and put message
//when i exit i need to free all i allocated;