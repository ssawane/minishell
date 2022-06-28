/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:37:23 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/26 14:12:53 by ssawane          ###   ########.fr       */
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

void	execute(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*cmd_final;

	i = -1;
	while (shell->paths[++i])
	{
		cmd_final = ft_strjoin(shell->paths[i], cmd->oper[0]);
		if (!access(cmd_final, X_OK))
		{
			execve(cmd_final, cmd->oper, shell->envv);
			break ;
		}
		free(cmd_final);
	}
	if (shell->paths[i] == 0)
	{
		perror ("minishell: command not found");
		exit (0);
	}
}

// void	ft_parent(t_shell *shell, t_cmd *cmdprev, t_cmd *cmd)
// {
// 	int		status;

// 	cmd = cmdprev->next;
// 	dup2(cmdprev->end[0], STDIN_FILENO);
// 	dup2(cmd->out, STDOUT_FILENO);
// 	close(cmdprev->end[1]);
// 	close(cmd->out);
// 	execute(cmd, shell);
// }

void	ft_child(t_shell *shell, t_cmd *cmd)
{	
	if (cmd->in != 0)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != 1)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	execute(cmd, shell);
}

void	pipes_check(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmds;
	shell->pipes = -1;
	while (tmp)
	{
		shell->pipes++;
		tmp = tmp->next;
	}
}

void	pipes_generating(t_shell *shell)
{
	int	i;

	i = -1;
	shell->mpp = malloc(sizeof(int *) * shell->pipes);
	while (++i < shell->pipes)
	{
		shell->mpp[i] = malloc(sizeof(int) * 2);
		pipe(shell->mpp[i]);
	}
}

void	fd_changing(t_cmd	*cmd)
{
	if (cmd->in != 0)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != 1)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
}

void	close_pipes(t_shell *shell)
{
	int	i;

	if (shell->mpp)
	{
		i = -1;
		while (shell->mpp[++i])
		{
			close(shell->mpp[i][0]);
			close(shell->mpp[i][1]);
		}
		i = -1;
		while (shell->mpp[++i])
			free(shell->mpp[i]);
		free(shell->mpp);
	}
}

void	multipipe(t_shell *shell)
{
	t_cmd	*tmp;
	int		i;
	pid_t	*child;
	int		status;

	printf("shell->pipes: %d\n", shell->pipes);
	tmp = shell->cmds;
	i = -1;
	pipes_generating(shell);
	child = (pid_t *)malloc(sizeof(pid_t) * shell->pipes);
	while (++i < shell->pipes)
	{
		child[i] = fork();
		if (child[i] == 0)
		{
			printf("%s\n", tmp->oper[0]);
			if (i != 0)
			{
				waitpid(-1, &status, 0);
				dup2(shell->mpp[i - 1][0], STDIN_FILENO);
			}
			dup2(shell->mpp[i][1], STDOUT_FILENO);
			fd_changing(tmp);
			close_pipes(shell); // close_pipes
			kill(getppid(), 9);
			execute(tmp, shell);
		}
		tmp = tmp->next;
	}
}

void	main_exec(t_shell *shell)
{
	int		status;
	pid_t	child;
	
	shell->paths = paths_pars(shell->envv);
	pipes_check(shell);
	if (shell->cmds)
	{
		if (!shell->pipes)
		{
			child = fork();
			if (child == 0)
				ft_child(shell, shell->cmds);
			waitpid(child, &status, 0);
		}
		else
			multipipe(shell);
	}
}