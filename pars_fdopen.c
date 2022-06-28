/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_fdopen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:27:19 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/23 11:20:24 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	pipe(cmd->end);
	write(cmd->end[1], res, ft_strlen(res));
	cmd->in = cmd->end[0];
	close(cmd->end[1]);
	free(line);
}

void	open_read(t_cell *cell, t_cmd *cmd)
{
	if (access(cell->word, F_OK) == -1 || access(cell->word, R_OK) == -1)
	{
		perror("minishell: infile error");
		exit(0);
	}
	cmd->in = open(cell->word, O_RDONLY);
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
			cmd->out = open(t->word, O_CREAT | O_WRONLY | O_TRUNC, 0644); //open clear
		else if (!(ft_strcmp(cell->word, ">>")))
			cmd->out = open(cell->word, O_CREAT | O_WRONLY | O_APPEND, 0644); //open append
		else if (!(ft_strcmp(cell->word, "<")))
			open_read(t, cmd); //open read
		else if (!(ft_strcmp(cell->word, "<<")))
			heredoc_proc(t, cmd); //stop word
		if (cmd->out == -1)
		{
			perror("minishell: outfile error");
			exit(0);
		}
		t->type = 0;
	}
}