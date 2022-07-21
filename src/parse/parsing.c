/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/21 13:17:41 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cell	*cell_words_convert(void)
{
	int		i;
	t_cell	*nodes;
	t_cell	*unit;

	i = 1;
	nodes = ft_cellnew(g_b.words[0]);
	while (g_b.words[i])
	{
		unit = ft_cellnew(g_b.words[i]);
		ft_celladd_back(&nodes, unit);
		i++;
	}
	i = -1;
	while (g_b.words[++i])
		free(g_b.words[i]);
	free(g_b.words);
	g_b.words = NULL;
	return (nodes);
}

int	syntax_errors_check(void)
{
	t_cell	*tmp;

	tmp = g_b.cells;
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
	int		fd;

	add_history(g_b.line);
	fd = open(g_b.hist_path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell: cannot open history file");
		exit(0);
	}
	write(fd, g_b.line, ft_strlen(g_b.line));
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
	if (g_b.exit != -1)
		finish_free();
	signals_proc();
	g_b.line = readline("minishell>$ ");
	if (!g_b.line)
	{
		g_b.exit = 0;
		finish_free();
	}
	adding_history();
	if (isempty_line(g_b.line) || spaces_adding()
		|| spaces_changing())
		return (1);
	g_b.words = ft_split(g_b.line, '\n');
	g_b.cells = cell_words_convert();
	if (syntax_errors_check())
		return (1);
	quot_correct();
	g_b.cmds = cmd_cells_convert();
	if (g_b.close == 1)
		return (1);
	return (0);
}
