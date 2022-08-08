/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:26:14 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/15 12:09:02 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipes_check(void)
{
	t_cmd	*tmp;

	tmp = g_b.cmds;
	g_b.pipes = -1;
	while (tmp)
	{
		g_b.pipes++;
		tmp = tmp->next;
	}
}

void	free_paths(void)
{
	int	i;

	i = -1;
	while (g_b.paths[++i])
		free(g_b.paths[i]);
	free(g_b.paths);
}

void	empty_paths_err(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
	exit(127);
}

char	**paths_pars(char **envp, char *str)
{
	char	*path_envp;
	char	**paths;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		if (envp[++i] == NULL)
			empty_paths_err(str);
	path_envp = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 4);
	paths = ft_split(path_envp, ':');
	free(path_envp);
	i = -1;
	while (paths[++i])
	{
		path_envp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(path_envp);
	}
	return (paths);
}

void	execute(t_cmd *cmd)
{
	int		i;
	char	*cmd_final;

	i = -1;
	g_b.paths = paths_pars(g_b.envv, cmd->oper[0]);
	if (!access(cmd->oper[0], X_OK))
		execve(cmd->oper[0], cmd->oper, g_b.envv);
	while (g_b.paths[++i])
	{
		cmd_final = ft_strjoin(g_b.paths[i], cmd->oper[0]);
		if (!access(cmd_final, X_OK))
			execve(cmd_final, cmd->oper, g_b.envv);
		free(cmd_final);
	}
	write(2, "minishell: ", 11);
	write(2, cmd->oper[0], ft_strlen(cmd->oper[0]));
	write(2, ": command not found\n", 20);
	free_paths();
	exit (127);
}
