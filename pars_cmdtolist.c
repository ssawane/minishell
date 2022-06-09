/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmdtolist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:54:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/09 11:35:50 by ssawane          ###   ########.fr       */
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

void	redir_proc(t_shell *shell, t_cmd *cmd)
{
	t_cell	*t;

	t = shell->cells;
	if (t->type == 2)
	{
		t->type = 0;
		t = t->next;
		if (!ft_strcmp(t->word, ">"))
			cmd->out = t->word; //open clear
		else if (!ft_strcmp(t->word, ">>"))
			cmd->out = t->word; //open append
		else if (!ft_strcmp(t->word, "<"))
			cmd->in = t->word; //open read
		else if (!ft_strcmp(t->word, "<"))
			cmd->stop = t->word;
		t->type = 0;
	}
}



t_cmd	*cmd_cells_convert(t_shell *shell)
{
	t_cell	*t;
	t_cmd	*nodes;

	t = shell->cells;
	while (t->next)
	{
		nodes = ft_cmdnew();
		while (t->type != 3 && t->next)
		{
			redir_proc(shell, nodes);
			t = t->next;
		}
		t = shell->cells;
		while (t->type != 3 && t->next)
		{
			cmds_proc(shell, nodes);
			t = t->next;			
		}
		
	}
}