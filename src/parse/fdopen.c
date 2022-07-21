/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdopen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:27:19 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/21 13:26:11 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pointer(int t)
{
	int	p;

	p = t - 2;
	if (p < 0)
		p = -1;
	return (p);
}

void	heredoc_next(t_cmd *cmd, char *res, char *line)
{
	char	*tmp;

	if (res)
	{
		tmp = res;
		res = ft_strjoin(res, "\n");
		free(tmp);
		pipe(cmd->pfd);
		write(cmd->pfd[1], res, ft_strlen(res));
		cmd->in = cmd->pfd[0];
		close(cmd->pfd[1]);
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
		if (!line || !ft_strcmp(line, cell->word))
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
	heredoc_next(cmd, res, line);
}

void	open_read(t_cell *cell, t_cmd *cmd)
{
	if (access(cell->word, F_OK) == -1 || access(cell->word, R_OK) == -1)
	{
		perror("minishell: infile error");
		g_b.close = 1;
	}
	else
	{
		cmd->in = open(cell->word, O_RDONLY);
		if (cmd->in == -1)
		{
			perror("minishell: infile error");
			g_b.close = 1;
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
			g_b.close = 1;
		}
		t->type = 0;
	}
}
