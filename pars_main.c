/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/09 16:39:22 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argc_check(int ac, char **av)
{
	if (ac != 1 || av[1] != NULL)
	{
		printf("%s\n", "error about file or directory");
		return (0);
	}
	return (1);
}

int	close_term_check(char *line)
{
	if (!(ft_strcmp(line, "exit")))
		return (0);
	return (1);
}

t_cell	*cell_words_convert(t_shell *shell)
{
	int		i;
	t_cell	*nodes;
	t_cell	*unit;

	i = 0;
	nodes = ft_cellnew(shell->words[0]);
	while (shell->words[++i])
	{
		unit = ft_cellnew(shell->words[i]);
		ft_celladd_back(&nodes, unit);
	}
	return (nodes);
}

void	main_parsing(t_shell *shell)
{
	line_correcting(shell);
	shell->words = ft_split(shell->line, ' ');
	shell->cells = cell_words_convert(shell);
	shell->cmds = cmd_cells_convert(shell);
}

int	main(int ac, char **av)
{
	t_shell	shell;

	if (argc_check(ac, av))
	{
		while (close_term_check(shell.line = readline("minishell>$ ")))
		{
			main_parsing(&shell);
			// print(&shell);
			 print2(&shell);
			print3(&shell);
		}
	}
	return (0);
}