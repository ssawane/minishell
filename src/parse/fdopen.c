/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdopen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:27:19 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/03 14:19:16 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_proc_step2(t_cmd *cmd, char *res, char *line)
{
	if (res)
	{
		pipe(cmd->end);
		write(cmd->end[1], res, ft_strlen(res));
		cmd->in = cmd->end[0];
		close(cmd->end[1]);
		free(res);
	}
	free(line);
}

void	heredoc_proc(t_cell *cell, t_cmd *cmd)
{
	char	*line;
	char	*res;
	char	*tmp;

	res = NULL;
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, cell->word))
			break ;
		if (res)
		{
			tmp = res;
			res = ft_strjoin(res, "\n");
			free(tmp);
			tmp = res;
			res = ft_strjoin(res, line);
			free(tmp);
			free(line);
		}
		else
			res = line;
	}
	heredoc_proc_step2(cmd, res, line);
}

void	open_read(t_cell *cell, t_cmd *cmd)
{
	if (access(cell->word, F_OK) == -1 || access(cell->word, R_OK) == -1)
	{
		perror("minishell: infile error");
		shl.close = 1;
	}
	else
	{
		cmd->in = open(cell->word, O_RDONLY);
		if (cmd->in == -1)
		{
			perror("minishell: infile error");
			shl.close = 1;
		}
	}
}

void	redir_proc(t_cell *cell, t_cmd *cmd)
{
	t_cell	*t;

	cell->type = 0;
	t = cell->next;
	if (t->type == 2)
		t = t->next;
	if (t)
	{
		if (!(ft_strcmp(cell->word, ">")))
			cmd->out = open(t->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (!(ft_strcmp(cell->word, ">>")))
			cmd->out = open(t->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (!(ft_strcmp(cell->word, "<")))
			open_read(t, cmd);
		else if (!(ft_strcmp(cell->word, "<<")))
			heredoc_proc(t, cmd);
		if (cmd->out == -1)
		{
			perror("minishell: outfile error");
			shl.close = 1;
		}
		t->type = 0;
	}
}
