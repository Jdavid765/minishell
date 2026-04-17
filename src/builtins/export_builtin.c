/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:59:29 by canoduran         #+#    #+#             */
/*   Updated: 2026/04/17 17:30:41 by canoduran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*retires_quotes(char *arg)
{
	char	*rl;
	int		count;
	int		i;
	int		x;

	count = ft_strlen(arg) + 1;
	i = 0;
	x = 0;
	rl = malloc(sizeof(char) * count);
	if (!rl)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] != '\'' && arg[i] != '\"')
		{
			rl[x] = arg[i];
			x++;
		}
		i++;
	}
	rl[x] = '\0';
	return (rl);
}

int	print_export(t_all *all)
{
	t_env	*current;

	current = all->env;
	while (current)
	{
		if (current->key)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(current->key, STDOUT_FILENO);
			if (current->value)
			{
    			ft_putstr_fd("=\"", STDOUT_FILENO);
    			ft_putstr_fd(current->value, STDOUT_FILENO);
    			ft_putstr_fd("\"", STDOUT_FILENO);
			}
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
	return (0);
}

int	add_or_update(t_all *all, char *arg)
{
	char	*key;
	char	*value;
	char	*rl;

	rl = retires_quotes(arg);
	if (!rl)
		return (1);
	if (!all || !arg)
		return (1);
	if (parse_arg(rl, &key, &value))
		return (1);
	if (is_valid_arg(key))
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(", not a valid arguments\n", STDERR_FILENO);
		free(key);
		free(value);
		return (1);
	}
	if (update_existing(all, key, value, rl))
		return (0);
	return (append_node(all, key, value));
}

int	export_builtin(t_all *all, t_parser *cmd)
{
	int	i;

	if (!cmd->cmd_and_args[1])
	{
		if (print_export(all) == 1)
		return (1);
	}
	i = 1;
	while (cmd->cmd_and_args[i])
	{
		if (add_or_update(all, cmd->cmd_and_args[i]))
			return (1);
		i++;
	}
	return (1);
}
