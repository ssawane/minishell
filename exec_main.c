/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:37:23 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/09 23:52:15 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	main_exec(t_shell *shell)
{
	t_cmd	*t;
	int		i;
	char	*cmd_final;

	shell->paths = paths_pars(shell->envv);
	t = shell->cmds;
	i = -1;
	while (t != NULL)
	{
		while (shell->paths[++i])
		{
			cmd_final = ft_strjoin(shell->paths[i], t->oper[0]);
		if (!access(cmd_final, X_OK))
		{
			execve(cmd_final, t->oper, shell->envv);
			break ;
		}
		free(cmd_final);
		}
		t = t->next;
	}
	if (shell->paths[i] == 0)
	{
		perror ("minishell: command not found");
		exit (0);
	}
}