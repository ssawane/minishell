/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:37:23 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/05 13:44:08 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	ft_child(t_cmd *cmd)
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
	execute(cmd);
}

void	pipes_check(void)
{
	t_cmd	*tmp;

	tmp = shl.cmds;
	shl.pipes = -1;
	while (tmp)
	{
		shl.pipes++;
		tmp = tmp->next;
	}
}

void	pipes_generating(void)
{
	int	i;

	i = -1;
	shl.mpp = malloc(sizeof(int *) * shl.pipes);
	while (++i < shl.pipes)
	{
		shl.mpp[i] = malloc(sizeof(int) * 2);
		pipe(shl.mpp[i]);
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

void	close_pipes(void)
{
	int	i;

	if (shl.mpp)
	{
		i = -1;
		while (shl.mpp[++i])
		{
			close(shl.mpp[i][0]);
			close(shl.mpp[i][1]);
		}
		i = -1;
		while (shl.mpp[++i])
			free(shl.mpp[i]);
		free(shl.mpp);
	}
}

void	multipipe(void)
{
	t_cmd	*tmp;
	int		i;
	pid_t	*child;
	int		status;

	printf("shell->pipes: %d\n", shl.pipes);
	tmp = shl.cmds;
	i = -1;
	pipes_generating();
	child = (pid_t *)malloc(sizeof(pid_t) * shl.pipes);
	while (++i < shl.pipes)
	{
		child[i] = fork();
		if (child[i] == 0)
		{
			printf("%s\n", tmp->oper[0]);
			if (i != 0)
			{
				waitpid(-1, &status, 0);
				dup2(shl.mpp[i - 1][0], STDIN_FILENO);
			}
			dup2(shl.mpp[i][1], STDOUT_FILENO);
			fd_changing(tmp);
			close_pipes(); // close_pipes
			kill(getppid(), 9);
			execute(tmp);
		}
		tmp = tmp->next;
	}
}

void	main_exec(void)
{
	// int		status;
	pid_t	child;
	
	shl.paths = paths_pars(shl.envv);
	pipes_check();
	if (shl.cmds)
	{
		if (shl.pipes == 0)
		{
			child = fork();
			if (child == 0)
				ft_child(shl.cmds);
			// waitpid(child, &status, 0);
		}
		else if (shl.pipes > 0)
			multipipe();
	}
}