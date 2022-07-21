/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:43:38 by tandrea           #+#    #+#             */
/*   Updated: 2022/07/21 15:00:06 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arg_exist(char **en, char *str, int j, int i)
{
	char	*tmp;

	i = 0;
	tmp = ft_substr(str, 0, j + 1);
	while ((en[i] && !ft_strnstr(en[i], tmp, j + 1)))
		i++;
	free(tmp);
	if (en[i] != NULL)
	{
		free(en[i]);
		en[i] = ft_strdup(str);
		return (1);
	}
	i = 0;
	tmp = ft_substr(str, 0, j);
	while (en[i] && !ft_strnstr(en[i], tmp, j))
			i++;
	free(tmp);
	if (en[i] != NULL && ft_strlen(en[i]) == j)
	{
		free(en[i]);
		en[i] = ft_strdup(str);
		return (1);
	}
	return (0);
}

void	add_toenv(char *str, int j)
{
	char	**new_env;
	int		len;
	int		i;

	i = -1;
	if (arg_exist(g_b.envv, str, j, i))
		return ;
	len = ft_masslen(g_b.envv);
	new_env = malloc(sizeof(char *) * (len + 2));
	while (++i < len)
		new_env[i] = g_b.envv[i];
	new_env[i++] = ft_strdup(str);
	new_env[i] = NULL;
	free(g_b.envv);
	g_b.envv = new_env;
}

void	add_toexpenv(char *str, int j)
{
	char	**new_env;
	int		len;
	int		i;

	i = 0;
	if (j > 0 && arg_exist(g_b.expenv, str, j, i))
		return ;
	len = ft_masslen(g_b.expenv);
	while (g_b.expenv[i] && ft_strnstr(g_b.expenv[i],
			str, ft_strlen(str)) == NULL)
			i++;
	if (i != len)
		return ;
	i = -1;
	new_env = malloc(sizeof(char *) * (len + 2));
	while (++i < len)
		new_env[i] = g_b.expenv[i];
	new_env[i++] = ft_strdup(str);
	new_env[i] = NULL;
	free(g_b.expenv);
	g_b.expenv = new_env;
}

void	add_envexpenv(char *str)
{
	int		i;
	int		flag;

	flag = 0;
	if (ft_export_check(str))
		return ;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			flag = 1;
			break ;
		}
	}
	if (flag)
	{
		add_toenv(str, i);
		add_toexpenv(str, i);
	}
	else
		add_toexpenv(str, 0);
}

void	export_pr(void)
{
	int	i;

	i = 0;
	if (!g_b.cmds->oper[1])
		expenv_sort();
	else if (g_b.cmds->oper[1])
	{
		while (g_b.cmds->oper[++i])
		{
			if (ft_strncmp(g_b.cmds->oper[i], "_=", 2)
				&& ft_strcmp(g_b.cmds->oper[i], "_"))
				add_envexpenv(g_b.cmds->oper[i]);
		}
	}
}
