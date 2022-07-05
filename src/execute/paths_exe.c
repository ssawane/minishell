/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:26:14 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/05 13:48:24 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**paths_pars(char **envp)
{
	char	*path_envp;
	char	**paths;
	char	*tmp;
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(envp[4]);
	path_envp = ft_substr(envp[4], 5, len - 4);
	paths = ft_split(path_envp, ':');
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	return (paths);
}

void	execute(t_cmd *cmd)
{
	int		i;
	char	*cmd_final;

	i = -1;
	while (shl.paths[++i])
	{
		cmd_final = ft_strjoin(shl.paths[i], cmd->oper[0]);
		printf("cmd->oper[0]: %s\n", cmd->oper[0]);
		if (!access(cmd_final, X_OK))
		{
			printf("success: %s\n", "1");
			execve(cmd_final, cmd->oper, shl.envv);
			break ;
		}
		free(cmd_final);
	}
	if (shl.paths[i] == 0)
	{
		perror ("minishell: command not found");
		exit (0);
	}
}

