/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtolist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:54:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/09 17:40:09 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmds_proc(t_cell *t, t_cmd *unit)
{
	char	*str;
	char	*tmp2;

	t->type = 0;
	str = t->word;
	if (t->next && t->next->type == 1)
	{
		str = ft_strdup(t->word);
		t = t->next;
		while (t != NULL && t->type == 1)
		{
			tmp2 = str;
			str = ft_strjoin(str, "\n");
			free(tmp2);
			tmp2 = str;
			str = ft_strjoin(str, t->word);
			free(tmp2);
			t->type = 0;
			t = t->next;
		}
		unit->oper = ft_split(str, '\n');
		free(str);
	}
	else
		unit->oper = ft_split(t->word, '\n');
}

t_cell	*cmd_cells_cont(t_cell *t, t_cmd **unit, t_cmd **nodes)
{
	while (t != NULL && t->type != 3)
	{
		while (t->next && t->type != 1 && t->type != 3)
			t = t->next;
		if (t->type == 1)
			cmds_proc(t, *unit);
		while (t != NULL && t->type == 0)
			t = t->next;
	}
	if (t != NULL && t->next && t->type == 3)
	{
		*unit = ft_cmdnew();
		ft_cmdadd_back(nodes, *unit);
		t = t->next;
	}
	return (t);
}

t_cmd	*cmd_cells_convert(void)
{
	t_cell	*t;
	t_cell	*m;
	t_cmd	*nodes;
	t_cmd	*unit;

	t = shl.cells;
	unit = ft_cmdnew();
	nodes = unit;
	while (t != NULL)
	{
		m = t;
		while (t->next && t->type != 3)
		{
			if (t->type == 2)
				redir_proc(t, unit);
			t = t->next;
		}
		t = m;
		t = cmd_cells_cont(t, &unit, &nodes);
	}
	return(nodes);
}