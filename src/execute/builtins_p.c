/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:18:21 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/19 21:33:47 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_pr_parent(void)
{
	if (!g_b.cmds->oper[1])
		g_b.exit = g_b.exit_code;
	else if (g_b.cmds->oper[1] && !g_b.cmds->oper[2])
	{
		if (!digscheck(g_b.cmds->oper[1]))
			g_b.exit = ft_atoi(g_b.cmds->oper[1]);
		else if (digscheck(g_b.cmds->oper[1]))
			g_b.exit = 255;
	}
}

void	unset_pr(void)
{
	int		i;
	char	*tmp;

	i = 0;
	if (g_b.cmds->oper[1] && ft_strcmp(g_b.cmds->oper[1], "_"))
	{
		tmp = ft_strjoin(g_b.cmds->oper[1], "=");
		while (g_b.envv[i] && !ft_strnstr(g_b.envv[i],
				tmp, ft_strlen(tmp)))
			i++;
		free(tmp);
		if (g_b.envv[i])
		{
			free(g_b.envv[i]);
			while (g_b.envv[i + 1])
			{
				g_b.envv[i] = g_b.envv[i + 1];
				i++;
			}
			g_b.envv[i] = NULL;
		}
	}
}

void	builtins_parent(void)
{
	if (g_b.pipes == 0 && g_b.cmds->oper && g_b.cmds->oper[0])
	{
		if (!ft_strcmp(g_b.cmds->oper[0], "cd"))
			return ;// func
		else if (!ft_strcmp(g_b.cmds->oper[0], "export"))
			export_pr();
		else if (!ft_strcmp(g_b.cmds->oper[0], "unset"))
			unset_pr();
		else if (!ft_strcmp(g_b.cmds->oper[0], "exit"))
			exit_pr_parent();
	}		
}
