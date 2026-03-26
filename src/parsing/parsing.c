/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:56:58 by canoduran         #+#    #+#             */
/*   Updated: 2026/03/26 20:17:51 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_words(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		else if (token->type >= REDIR_IN && token->type <= HEREDOC)
		{
			if (token->next)
				token = token->next;
		}
		token = token->next;
	}
	return (count);
}

char	*search_path(t_all *all)
{
	t_env	*head;

	head = all->env;
	while (head)
	{
		if (head->key[0] == 'P')
		{
			if (!ft_compare(head->key, "PATH"))
				return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}

int	parse_token(t_all *all)
{
    if (!all->token)
        return (1);

    t_parser	*head;
    t_parser	*current_cmd;
	t_parser	*new_cmd;
    t_token		*current_tok;
    int			index;
    int			nb_words;

	head = ft_node_pars(all->path);
	current_cmd = head;
	current_tok = all->token;
	new_cmd = NULL;
	index = 0;
	nb_words = count_words(current_tok) + 1;
	current_cmd->cmd_and_args = malloc(sizeof(char *) * nb_words);

	while (current_tok)
	{
		if (current_tok->type == WORD)
		{
            current_cmd->cmd_and_args[index++] = ft_strdup(current_tok->value);
        }
        else if (current_tok->type == REDIR_OUT)
        {
            current_tok = current_tok->next;
            if (current_tok && current_tok->type == WORD)
            {
                if (current_cmd->fd_out != 1)
                    close(current_cmd->fd_out);
                current_cmd->fd_out = open(current_tok->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (current_cmd->fd_out < 0)
					return (1);
            }
			else
				return (printf("Error syntax\n"), 0);
        }
        else if (current_tok->type == APPEND)
        {
            current_tok = current_tok->next;
            if (current_tok && current_tok->type == WORD)
            {
                if (current_cmd->fd_out != 1)
                    close(current_cmd->fd_out);
                current_cmd->fd_out = open(current_tok->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (current_cmd->fd_out < 0)
					return (1);
            }
			else
				return (printf("Error syntax\n"), 0);
        }
        else if (current_tok->type == REDIR_IN)
        {
            current_tok = current_tok->next;
            if (current_tok && current_tok->type == WORD)
            {
                if (current_cmd->fd_in != 0)
                    close(current_cmd->fd_in);
                current_cmd->fd_in = open(current_tok->value, O_RDONLY);
				if (current_cmd->fd_in < 0)
					return (1);
            }
			else
				return (printf("Error syntax\n"), 0);
        }
        else if (current_tok->type == PIPE)
        {
            current_cmd->cmd_and_args[index] = NULL;
			new_cmd = ft_node_pars(all->path);
			ft_addback_parse(&current_cmd, new_cmd);
			current_cmd = current_cmd->next;
            if (current_tok->next)
            {
				nb_words = count_words(current_tok->next);
				current_cmd->cmd_and_args = malloc(sizeof(char *) * (nb_words + 1));
			}
            index = 0;
        }
		if (current_tok)
			current_tok = current_tok->next;
    }
    if (current_cmd && current_cmd->cmd_and_args)
        current_cmd->cmd_and_args[index] = NULL;
    all->parser = head;
    return (0);
}

//addd le before path in this function
//for heredoc i need to do one specific
//if one token type after is not a word i need to cancel all tokeniser and put message
//when i exit i need to free all i allocated;
// for double pipe envoyer le bloc de commande avant et apres le free