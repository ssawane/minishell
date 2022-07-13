/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:50:04 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/13 18:36:19 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	digscheck(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
	}
	return (0);
}

void	exit_pr(t_cmd *cmd)
{
	if (!cmd->oper[1])
		exit(0);
	else if (cmd->oper[1])
	{
		if (cmd->oper[2])
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			exit(1);
		}
		else if (!cmd->oper[2])
		{
			if (!digscheck(cmd->oper[1]))
				exit(ft_atoi(cmd->oper[1]));
			else if (digscheck(cmd->oper[1]))
			{
				write(2, "minishell: exit: ", 17);
				write(2, cmd->oper[1], ft_strlen(cmd->oper[1]));
				write(2, ": numeric argument required\n", 28);
				exit(255);
			}
		}
	}
}

void	env_pr(void)
{
	int	i;

	i = -1;
	while (shl.envv[++i])
	{
		write(1, shl.envv[i], ft_strlen(shl.envv[i]));
		write(1, "\n", 1);
	}
	exit (0);
}

void	echo_pr(t_cmd *cmd)
{
	printf("echo here: %s\n", cmd->oper[0]);
	exit(0);
}

void	isbuildin(t_cmd *cmd)
{
	if (cmd->oper)
	{
		if (cmd->oper[0])
		{
			if (!ft_strcmp(cmd->oper[0], "echo"))
				echo_pr(cmd);
			// else if (!ft_strcmp(cmd->oper[0], "cd"))
			// 	cd_pr(cmd);
			// else if (!ft_strcmp(cmd->oper[0], "pwd"))
			// 	pwd_pr(cmd);
			// else if (!ft_strcmp(cmd->oper[0], "export"))
			// 	export_pr(cmd);
			// else if (!ft_strcmp(cmd->oper[0], "unset"))
			// 	unset_pr(cmd);
			else if (!ft_strcmp(cmd->oper[0], "env"))
				env_pr();
			else if (!ft_strcmp(cmd->oper[0], "exit"))
				exit_pr(cmd);
			else
				execute(cmd);
		}
	}
	else
		execute(cmd);
}