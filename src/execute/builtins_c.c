/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:50:04 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/08 17:47:10 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_pr_child(t_cmd *cmd)
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

void	export_check_ch(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((!ft_isalpha(str[0]) && str[0] != '_') || !ft_isprint(str[i]))
		{
			if (g_b.pipes > 0)
				printf("export: `%s': not a valid identifier\n", str);
			exit(1);
		}
		i++;
	}
}

void	env_export_pr(char **str)
{
	int	i;

	i = 0;
	if (!ft_strcmp(str[0], "export"))
	{
		if (str[1])
		{
			while (str[++i])
			{
				if (ft_strncmp(str[i], "_=", 2)
					&& ft_strcmp(str[i], "_"))
					export_check_ch(str[i]);
			}
		}
	}
	else if (!ft_strcmp(str[0], "env"))
	{
		i = -1;
		while (g_b.envv[++i])
		{
			write(1, g_b.envv[i], ft_strlen(g_b.envv[i]));
			write(1, "\n", 1);
		}
	}
	exit (0);
}

void	echo_pr(t_cmd *com)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	if (!com->oper[1])
		write (com->out, " \n", 2);
	while (com->oper[k])
			k++;
	if (!ft_strcmp(com->oper[i], "-n"))
		while (!ft_strcmp(com->oper[i], "-n"))
			i++;
	while (com->oper[i])
	{
		write (com->out, com->oper[i], ft_strlen(com->oper[i]));
		if (i != k - 1)
			write (com->out, " ", 1);
		i++;
	}
	if (ft_strcmp(com->oper[1], "-n"))
		write (com->out, "\n", 1);
	exit(0);
}

void	builtins_child(t_cmd *cmd)
{
	if (cmd->oper)
	{
		if (cmd->oper[0])
		{
			if (!ft_strcmp(cmd->oper[0], "echo"))
				echo_pr(cmd);
			else if (!ft_strcmp(cmd->oper[0], "cd")
				|| !ft_strcmp(cmd->oper[0], "unset"))
				exit(0);
			else if (!ft_strcmp(cmd->oper[0], "pwd"))
				ft_pwd();
			else if (!ft_strcmp(cmd->oper[0], "env")
				|| !ft_strcmp(cmd->oper[0], "export"))
				env_export_pr(cmd->oper);
			else if (!ft_strcmp(cmd->oper[0], "exit"))
				exit_pr_child(cmd);
			else
				execute(cmd);
		}
		else
			execute(cmd);
	}
	else
		execute(cmd);
}
