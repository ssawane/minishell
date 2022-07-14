/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:02:34 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/13 22:56:27 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_shl	shl;

void	rowed_free(void)
{
	t_cell	*tmp;

	if (shl.line)
		free(shl.line);
	while (shl.cells)
	{
		free(shl.cells->word);
		shl.cells->word = NULL;
		tmp = shl.cells;
		shl.cells = shl.cells->next;
		free(tmp);
	}
	shl.cmds = NULL;
	shl.line = NULL;
	shl.cells = NULL;
	shl.words = NULL;
	shl.close = 0;
}

void	finish_free(void)
{
	int	i;

	i = -1;
	if (shl.envv)
	{
		while(shl.envv[++i])
			free(shl.envv[i]);
		free(shl.envv);
	}
	write(1, "exit\n", 5);
	exit(shl.exit);
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

void	shlvl_up(void)
{
	int		def;
	char	*tmp;
	int		i;

	i = 0;
	while (!ft_strnstr(shl.envv[i], "SHLVL=", 6))
		if (!shl.envv[++i])
		{
			write(2, "error: no shlvl\n", 16);
			return;
		}
	tmp = ft_substr(shl.envv[i], 6, ft_strlen(shl.envv[i]) - 5);
	free(shl.envv[i]);
	def = ft_atoi(tmp) + 1;
	if (def == 1000)
		def = 0;
	free(tmp);
	tmp = ft_itoa(def);
	shl.envv[i] = ft_strjoin("SHLVL=", tmp);
	free(tmp);
}

void	shell_init(char **envp)
{
	shl.line = NULL;
	shl.words = NULL;
	shl.cells = NULL;
	shl.cmds = NULL;
	shl.envv = NULL;
	shl.close = 0;
	shl.fdp = 0;
	shl.exit = -1;
	local_env(envp);
	shlvl_up();
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	shell_init(envp);
	while (1)
	{
		if (!main_parsing())
		{
			// print();
			// print3();
			main_exe();
			// print3();
		}
		rowed_free();
	}
	return (0);
}