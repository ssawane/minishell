/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:43:38 by tandrea           #+#    #+#             */
/*   Updated: 2022/07/19 21:26:13 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_builtin(int *fd)
{
	t_cmd	*com;

	com = g_b.cmds;
	if (com->out != 1)
	{
		*fd = com->out;
	}
}

void	ft_pwd(void)
{
	char	*p;
	int		fd;

	p = NULL;
	fd = 1;
	ft_check_builtin(&fd);
	p = getcwd(p, 10000);
	write (fd, p, ft_strlen(p));
	write (fd, "\n", 1);
	exit(0);
}
