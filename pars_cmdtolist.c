/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmdtolist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:54:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/09 16:38:49 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new -> in = 0;
	new -> out = 1;
	new -> stop = NULL;
	new -> next = NULL;
	return (new);
}

t_cmd	*ft_cmdlast(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd -> next)
		cmd = cmd -> next;
	return (cmd);
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*p;

	if (!new)
		return ;
	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	p = ft_cmdlast(*cmd);
	p -> next = new;
}

void	redir_proc(t_cell *cell, t_cmd *cmd)
{
	t_cell	*t;

	t = cell;
	// t->type = 0;
	t = t->next;
	if (!(ft_strcmp(t->word, ">")))
		cmd->out = 6; //open clear
	else if (!(ft_strcmp(t->word, ">>")))
		cmd->out = 6; //open append
	else if (!(ft_strcmp(t->word, "<")))
		cmd->in = 7; //open read
	else if (!(ft_strcmp(t->word, "<<")))
		cmd->stop = t->word; //stop word
	// t->type = 0;
}

void	cmds_proc(t_shell *shell, t_cell *t)
{
	char	*tmp2;

	// t->type = 0;
	if (shell->tmp)
		free(shell->tmp);
	shell->tmp = t->word;
	t = t->next;
	tmp2 = NULL;
	while (t->type == 1)
	{
		if (tmp2)
			free(tmp2);
		tmp2 = ft_strjoin(shell->tmp, " ");
		// free(shell->tmp);
		shell->tmp = ft_strjoin(tmp2, t->word);
		// free(tmp2);
		// t->type = 0;
		t = t->next;
	}
}

t_cmd	*cmd_cells_convert(t_shell *shell)
{
	t_cell	*t;
	t_cmd	*nodes;
	t_cmd	*unit;

	t = shell->cells;
	unit = ft_cmdnew();
	nodes = unit;
	while (t != NULL)
	{
		while (t->type != 3 && t->next)
		{
			if (t->type == 2)
				redir_proc(t, unit);
			t = t->next;
		}
		t = shell->cells;
		while (t->type != 3 && t->next)
		{
			while (t->type != 1 && t->type != 3 && t->next)
				t = t->next;
			if (t->next)
			{
				if (t->type == 1)
					cmds_proc(shell, t);
				t = t->next;
			}
		}
		unit->oper = ft_split(shell->tmp, ' ');
		if (t->type == 3)
		{
			unit = ft_cmdnew();
			ft_cmdadd_back(&nodes, unit);
		}
		t = t->next;
	}
	return(nodes);
}

// sdfsdf>dfgdf|fgf