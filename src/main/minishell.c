/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:02:34 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/08 13:01:20 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_shl	g_b;

void	rowed_free(void)
{
	t_cell	*tmp;

	if (g_b.line)
		free(g_b.line);
	while (g_b.cells)
	{
		free(g_b.cells->word);
		g_b.cells->word = NULL;
		tmp = g_b.cells;
		g_b.cells = g_b.cells->next;
		free(tmp);
	}
	g_b.cmds = NULL;
	g_b.line = NULL;
	g_b.cells = NULL;
	g_b.words = NULL;
	g_b.close = 0;
}

void	finish_free(void)
{
	int	i;

	i = -1;
	if (g_b.envv)
	{
		while (g_b.envv[++i])
			free(g_b.envv[i]);
		free(g_b.envv);
	}
	i = -1;
	if (g_b.expenv)
	{
		while (g_b.expenv[++i])
			free(g_b.expenv[i]);
		free(g_b.expenv);
	}
	if (g_b.hist_path)
		free(g_b.hist_path);
	write(1, "exit\n", 5);
	exit(g_b.exit);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	shell_init(envp);
	while (1)
	{
		if (!main_parsing())
			main_exe();
		rowed_free();
	}
	return (0);
}
