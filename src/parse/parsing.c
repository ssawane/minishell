/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/13 16:01:54 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cell	*cell_words_convert(void)
{
	int		i;
	t_cell	*nodes;
	t_cell	*unit;

	i = 1;
	nodes = ft_cellnew(shl.words[0]);
	while (shl.words[i])
	{
		unit = ft_cellnew(shl.words[i]);
		ft_celladd_back(&nodes, unit);
		i++;
	}
	i = -1;
	while (shl.words[++i])
		free(shl.words[i]);
	free(shl.words);
	shl.words = NULL;
	return (nodes);
}

int	syntax_errors_check(void)
{
	t_cell	*tmp;

	tmp = shl.cells;
	while (tmp)
	{
		if (tmp->type == 2 && !ft_strcmp(tmp->word, "<"))
			if (tmp->next->type == 2 && !ft_strcmp(tmp->next->word, ">"))
				tmp = tmp->next;
		if (tmp->type == 2)
			if (!tmp->next || tmp->next->type == 2 || tmp->next->type == 3)
				return (syntax_error_mes());
		if (tmp->type == 3)
			if (!tmp->next || tmp->next->type == 3)
				return (syntax_error_mes());
		tmp = tmp->next;
	}
	return (0);
}

void	adding_history(void)
{
	int	fd;

	add_history(shl.line);
	fd = open("history.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell: cannot open history file");
		exit(0);
	}
	write(fd, shl.line, ft_strlen(shl.line));
	write(fd, "\n", 1);
	close(fd);
}

int	isempty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
			i++;
	if (line[i] == '\0')
		return (1);
	i = 0;
	return (0);
}

int	main_parsing(void)
{
	if (shl.exit != -1)
			finish_free();
	signals_proc();
	shl.line = readline("minishell>$ ");
	if (!shl.line)
	{
		shl.exit = 0;
		finish_free();
	}
	adding_history();
	if (isempty_line(shl.line) || spaces_adding()
		|| spaces_changing())
		return (1);
	shl.words = ft_split(shl.line, '\n');
	shl.cells = cell_words_convert();
	if (syntax_errors_check())
		return (1);
	quot_correct();
	shl.cmds = cmd_cells_convert();
	if (shl.close == 1)
		return (1);
	return (0);
}
