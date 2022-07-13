/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:37:23 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/12 23:09:19 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	procs_wait(void)
{
	int	i;

	i = -1;
	while (++i < shl.pipes + 1)
		waitpid(shl.pids[i], &shl.exit_code, 0);
	if (WEXITSTATUS(shl.exit_code))
		shl.exit_code = WEXITSTATUS(shl.exit_code);
	else if (WIFSIGNALED(shl.pids[i]))
	{
		shl.exit_code = WTERMSIG(shl.exit_code);
		if (shl.exit_code != 131 && shl.exit_code != 0)
			shl.exit_code += 128;
	}
}

t_cmd	*first_pr(t_cmd *cmd, int *i, int fdp[2][2])
{
	pipe(fdp[0]);
	shl.pids[*i] = fork();
	if (!shl.pids[*i])
	{
		if (cmd->in != 0)
			dup2(cmd->in, STDIN_FILENO);
		else if (*i > 0)
			dup2(fdp[1][0], STDIN_FILENO);
		if (cmd->out != 1)
			dup2(cmd->out, STDOUT_FILENO);
		else if (*i < shl.pipes)
			dup2(fdp[0][1], STDOUT_FILENO);
		close(fdp[1][0]);
		close(fdp[0][1]);
		isbuildin(cmd);
	}
	close(fdp[0][1]);
	close(fdp[1][0]);
	cmd = cmd->next;
	*i += 1;
	return (cmd);
}

t_cmd	*second_pr(t_cmd *cmd, int *i, int fdp[2][2])
{
	pipe(fdp[1]);
	shl.pids[*i] = fork();
	if (!shl.pids[*i])
	{
		if (cmd->in != 0)
			dup2(cmd->in, STDIN_FILENO);
		else if (*i > 0)
			dup2(fdp[0][0], STDIN_FILENO);
		if (cmd->out != 1)
			dup2(cmd->out, STDOUT_FILENO);
		else if (*i < shl.pipes)
			dup2(fdp[1][1], STDOUT_FILENO);
		close(fdp[0][0]);
		close(fdp[1][1]);
		isbuildin(cmd);
	}
	close(fdp[1][1]);
	close(fdp[0][0]);
	cmd = cmd->next;
	*i += 1;
	return (cmd);
}

void	exit_check(void)
{
	if (shl.pipes == 0 && shl.cmds->oper && shl.cmds->oper[0]
		&& !ft_strcmp(shl.cmds->oper[0], "exit"))
	{
		if (!shl.cmds->oper[1])
			shl.exit = shl.exit_code;
		else if (shl.cmds->oper[1] && !shl.cmds->oper[2])
		{
			if (!digscheck(shl.cmds->oper[1]))
				shl.exit = ft_atoi(shl.cmds->oper[1]);
			else if (digscheck(shl.cmds->oper[1]))
				shl.exit = 255;
		}
	}
}

void	main_exe(void)
{
	t_cmd	*tmp;
	int		fdp[2][2];
	int		i;
	
	pipes_check();
	shl.pids = malloc(sizeof(int *) * (shl.pipes + 1));
	i = 0;
	tmp = shl.cmds;
	exit_check();
	while (i <= shl.pipes)
	{
		if (i == 0 || i%2 == 0)
			tmp = first_pr(tmp, &i, fdp);
		if (i <= shl.pipes && i%2 != 0)
			tmp = second_pr(tmp, &i, fdp);
	}
	close(fdp[0][1]);
	close(fdp[1][0]);
	procs_wait();
	free(shl.pids);
}
