/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:02:34 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/04 15:00:44 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(void)
{
	int		i;
	t_cell	*tmp;
	t_cmd	*tmp2; 

	i = -1;
	if (shl.line)
	{
		free(shl.line);
		shl.line = NULL;
	}
	while (shl.cmds)
	{
		tmp2 = shl.cmds;
		if (shl.cmds->oper)
		{
			i = -1;
			while(shl.cmds->oper[++i])
				free(shl.cmds->oper[i]);
			free(shl.cmds->oper);
		}
		shl.cmds = shl.cmds->next;
		free(tmp2);
	}
	shl.cmds = NULL;
	if (shl.cells)
	{
		while (shl.cells)
		{
			free(shl.cells->word);
			shl.cells->word = NULL;
			tmp = shl.cells;
			shl.cells = shl.cells->next;
			free(tmp);
		}
		shl.cells = NULL;
	}
	shl.close = 0;
}

void	free_env(void)
{
	int	i;

	i = -1;
	if (shl.envv)
	{
		while(shl.envv[++i])
			free(shl.envv[i]);
		free(shl.cmds->oper);
	}
}

int	close_term_check(char *line)
{
	if (!(ft_strcmp(line, "exit")))
		return (0);
	return (1);
}

void	local_env(char **envp)
{
	int		i;

	i = -1;
	shl.envnum = 0;
	while (envp[shl.envnum])
		shl.envnum++;
	if (shl.envnum > 0)
	{
		shl.envv = malloc(sizeof(char *) * (shl.envnum + 1));
		while (++i < shl.envnum)
			shl.envv[i] = ft_strdup(envp[i]);
		shl.envv[i] = NULL;
	}
	else
	{
		printf("%s\n", "bad env");
		shl.close = 1;
	}
}

void	shell_initialization(char **envp)
{
	shl.line = NULL;
	shl.words = NULL;
	shl.cells = NULL;
	shl.cmds = NULL;
	shl.envv = NULL;
	shl.close = 0;
	shl.mpp = 0;
	local_env(envp);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	shell_initialization(envp);
	while (close_term_check(shl.line = readline("minishell>$ ")))
	{
		if (!main_parsing())
		{
			// main_exec(&shell);
			// print();
			// print2(&shell);
			print3();
		}
		ft_free();
	}
	// free_env();
	return (0);
}