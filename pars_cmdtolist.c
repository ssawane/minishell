/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmdtolist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:54:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/09 23:49:34 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new -> in = "0";
	new -> out = "1";
	new -> stop = NULL;
	new -> next = NULL;
	new -> oper = NULL;
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

// int		pipe_check(t_cell *cell)
// {
// 	t_cell	*tmp;

// 	if (cell->type == 3 && cell->next)
// 		tmp = cell->next;
	

// }

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

	cell->type = 0;
	t = cell->next;
	if (t)
	{
		if (!(ft_strcmp(cell->word, ">")))
			cmd->out = t->word; //open clear
		else if (!(ft_strcmp(cell->word, ">>")))
			cmd->out = t->word; //open append
		else if (!(ft_strcmp(cell->word, "<")))
			cmd->in = t->word; //open read
		else if (!(ft_strcmp(cell->word, "<<")))
			cmd->stop = t->word; //stop word
		t->type = 0;
	}
}

void	cmds_proc(t_shell *shell, t_cell *t)
{
	char	*tmp2;
	char	*tmp3;

	t->type = 0;
	shell->tmp = NULL;
	shell->tmp = t->word;
	t = t->next;
	while (t->type == 1 && t != NULL)
	{
		tmp2 = ft_strjoin(shell->tmp, " ");
		free(shell->tmp);
		tmp3 = ft_strjoin(tmp2, t->word);
		free(tmp2);
		shell->tmp = tmp3;
		t->type = 0;
		if (t->next)
			t = t->next;
	}
}

t_cmd	*cmd_cells_convert(t_shell *shell)
{
	t_cell	*t;
	t_cell	*m;
	t_cmd	*nodes;
	t_cmd	*unit;

	shell->tmp = NULL;
	t = shell->cells;
	unit = ft_cmdnew();
	nodes = unit;
	while (t != NULL)
	{
		m = t;
		while (t->type != 3 && t->next)
		{
			if (t->type == 2)
				redir_proc(t, unit);
			t = t->next;
		}
		t = m;
		while (t->type != 3 && t->next)
		{
			while (t->type != 1 && t->type != 3 && t->next)
				t = t->next;
			if (t->next)
			{
				if (t->type == 1)
					cmds_proc(shell, t);
				while (t->type == 0 && t->next)
					t = t->next;
			}
		}
		unit->oper = ft_split(shell->tmp, ' ');
		free(shell->tmp);
		if (t->type == 3 && t->next)
		{
			unit = ft_cmdnew();
			ft_cmdadd_back(&nodes, unit);
		}
		t = t->next;
	}
	return(nodes);
}

// sdfsdf>dfgdf|fgf