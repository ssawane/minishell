/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:37:23 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/14 15:54:27 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	procs_wait(void)
{
	int	i;

	i = -1;
	while (++i < g_b.pipes + 1)
		waitpid(g_b.pids[i], &g_b.exit_code, 0);
	if (WEXITSTATUS(g_b.exit_code))
		g_b.exit_code = WEXITSTATUS(g_b.exit_code);
}

void	cmd_free(t_cmd *cmd)
{
	int	i;

	if (cmd->oper)
	{
		i = -1;
		while (cmd->oper[++i])
			free(cmd->oper[i]);
		free(cmd->oper);
	}
	free(cmd);
}

t_cmd	*first_pr(t_cmd *cmd, int *i, int fdp[2][2])
{
	t_cmd	*tmp;

	pipe(fdp[0]);
	g_b.pids[*i] = fork();
	if (!g_b.pids[*i])
	{
		if (cmd->in != 0)
			dup2(cmd->in, STDIN_FILENO);
		else if (*i > 0)
			dup2(fdp[1][0], STDIN_FILENO);
		if (cmd->out != 1)
			dup2(cmd->out, STDOUT_FILENO);
		else if (*i < g_b.pipes)
			dup2(fdp[0][1], STDOUT_FILENO);
		close(fdp[1][0]);
		close(fdp[0][1]);
		builtins_child(cmd);
	}
	close(fdp[0][1]);
	close(fdp[1][0]);
	tmp = cmd;
	cmd = cmd->next;
	cmd_free(tmp);
	*i += 1;
	return (cmd);
}

t_cmd	*second_pr(t_cmd *cmd, int *i, int fdp[2][2])
{
	t_cmd	*tmp;

	pipe(fdp[1]);
	g_b.pids[*i] = fork();
	if (!g_b.pids[*i])
	{
		if (cmd->in != 0)
			dup2(cmd->in, STDIN_FILENO);
		else if (*i > 0)
			dup2(fdp[0][0], STDIN_FILENO);
		if (cmd->out != 1)
			dup2(cmd->out, STDOUT_FILENO);
		else if (*i < g_b.pipes)
			dup2(fdp[1][1], STDOUT_FILENO);
		close(fdp[0][0]);
		close(fdp[1][1]);
		builtins_child(cmd);
	}
	close(fdp[1][1]);
	close(fdp[0][0]);
	tmp = cmd;
	cmd = cmd->next;
	cmd_free(tmp);
	*i += 1;
	return (cmd);
}

void	main_exe(void)
{
	int		fdp[2][2];
	int		i;

	signal(SIGQUIT, inside_pr);
	signal(SIGINT, inside_pr);
	pipes_check();
	builtins_parent();
	g_b.pids = malloc(sizeof(int *) * (g_b.pipes + 1));
	i = 0;
	while (i <= g_b.pipes)
	{
		if (i == 0 || i % 2 == 0)
			g_b.cmds = first_pr(g_b.cmds, &i, fdp);
		if (i <= g_b.pipes && i % 2 != 0)
			g_b.cmds = second_pr(g_b.cmds, &i, fdp);
	}
	close(fdp[0][1]);
	close(fdp[1][0]);
	procs_wait();
	free(g_b.pids);
}
