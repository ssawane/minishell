/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:26:14 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/12 20:44:26 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_paths(void)
{
	int	i;

	i = -1;
	while (shl.paths[++i])
		free(shl.paths[i]);
	free(shl.paths);
}

char	**paths_pars(char **envp)
{
	char	*path_envp;
	char	**paths;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
	{
		if (envp[++i] == NULL)
		{
			write(2, "error: unset path\n", 18);
			exit(127);
		}
	}
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
	shl.paths = paths_pars(shl.envv);
	if (!access(cmd->oper[0], X_OK))
		execve(cmd->oper[0], cmd->oper, shl.envv);
	while (shl.paths[++i])
	{
		cmd_final = ft_strjoin(shl.paths[i], cmd->oper[0]);
		if (!access(cmd_final, X_OK))
			execve(cmd_final, cmd->oper, shl.envv);
		free(cmd_final);
	}
	write(2, "minishell: ", 11);
	write(2, cmd->oper[0], ft_strlen(cmd->oper[0]));
	write(2, ": command not found\n", 20);
	free_paths();
	exit (127);
}

