/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:22:08 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/14 15:46:52 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	local_env(char **envp)
{
	int		i;

	i = -1;
	g_b.envnum = 0;
	while (envp[g_b.envnum])
		g_b.envnum++;
	if (g_b.envnum > 0)
	{
		g_b.envv = malloc(sizeof(char *) * (g_b.envnum + 1));
		while (++i < g_b.envnum)
			g_b.envv[i] = ft_strdup(envp[i]);
		g_b.envv[i] = NULL;
	}
	else
	{
		write(2, "minishell: bad env\n", 19);
		exit(1);
	}
}

void	shlvl_up(void)
{
	int		def;
	char	*tmp;
	int		i;

	i = 0;
	while (!ft_strnstr(g_b.envv[i], "SHLVL=", 6))
	{
		if (!g_b.envv[++i])
		{
			write(2, "minishell: no shlvl\n", 20);
			return ;
		}
	}
	tmp = ft_substr(g_b.envv[i], 6, ft_strlen(g_b.envv[i]) - 5);
	free(g_b.envv[i]);
	def = ft_atoi(tmp) + 1;
	if (def == 1000)
		def = 0;
	free(tmp);
	tmp = ft_itoa(def);
	g_b.envv[i] = ft_strjoin("SHLVL=", tmp);
	free(tmp);
}

void	shell_init(char **envp)
{
	g_b.line = NULL;
	g_b.words = NULL;
	g_b.cells = NULL;
	g_b.cmds = NULL;
	g_b.envv = NULL;
	g_b.close = 0;
	g_b.exit = -1;
	local_env(envp);
	shlvl_up();
}
