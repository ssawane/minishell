/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:37:23 by tandrea           #+#    #+#             */
/*   Updated: 2022/08/05 12:06:48 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_error(char *arg)
{
	write(2, "minishell: cd: ", 15);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, "No such file or directory", 25);
	write(2, "\n", 1);
}

void	empty_arg(char *old)
{
	char	*s;
	char	*tmp;
	int		i;

	i = 0;
	while (!ft_strnstr(g_b.envv[i], "HOME=", 5))
		if (!g_b.envv[++i])
			s = NULL;
	s = ft_strdup(g_b.envv[i]);
	tmp = s;
	s = ft_strtrim(s, "HOME=");
	if (tmp)
		free(tmp);
	chdir(s);
	tmp = ft_strcat("PWD=", s);
	add_toenv(tmp, 3);
	add_toexpenv(tmp, 3);
	free(tmp);
	tmp = ft_strcat("OLDPWD=", old);
	add_toenv(tmp, 6);
	add_toexpenv(tmp, 6);
	free(s);
	free(tmp);
	free(old);
	return ;
}

void	ft_change(char **new, int i, char *str)
{
	char	*tmp;

	tmp = ft_strcat(str, *new);
	free(*new);
	add_toenv(tmp, i);
	add_toexpenv(tmp, i);
	free(tmp);
}

void	ft_cd(void)
{
	int		temp;
	char	*new;
	char	*old;

	old = NULL;
	new = NULL;
	temp = 0;
	old = getcwd(old, 1000);
	if (!g_b.cmds->oper[1] || g_b.cmds->oper[1][0] == '~')
		return (empty_arg(old));
	if (ft_strcmp(old, "/Users") == 0
		&& ft_strcmp(g_b.cmds->oper[1], "..") == 0)
		chdir("/");
	else
		temp = chdir(g_b.cmds->oper[1]);
	new = getcwd(new, 1000);
	ft_change(&new, 3, "PWD=");
	ft_change(&old, 6, "OLDPWD=");
	if (temp < 0)
		cd_error(g_b.cmds->oper[1]);
}
