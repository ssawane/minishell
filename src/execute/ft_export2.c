/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:43:38 by tandrea           #+#    #+#             */
/*   Updated: 2022/07/25 21:08:40 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_str(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	print_cont(int fd, char *str)
{
	write(fd, "=", 1);
	write(fd, "\"", 1);
	write(fd, ft_strchr(str, '=') + 1,
		ft_strlen(ft_strchr(str, '=')) - 1);
	write(fd, "\"", 1);
}

void	ft_print(char **env)
{
	int		i;
	int		fd;
	char	**str;

	fd = 1;
	i = -1;
	ft_check_builtin(&fd);
	while (env[++i])
	{
		str = ft_split(env[i], '=');
		write(fd, "declare -x ", 11);
		write(fd, str[0], ft_strlen(str[0]));
		if (ft_strchr(env[i], '=') && !str[1])
		{
			write(fd, "=", 1);
			write(fd, "\"", 1);
			write(fd, "\"", 1);
		}
		else if (str[1])
			print_cont(fd, env[i]);
		write(fd, "\n", 1);
		ft_free_str(str);
	}
}

int	ft_masslen(char **str)
{
	int	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	return (len);
}

void	expenv_sort(void)
{
	int		i;
	int		j;
	char	*en;

	i = 0;
	while (i < ft_masslen(g_b.expenv) - 1)
	{
		j = i + 1;
		while (j < ft_masslen(g_b.expenv))
		{
			if (ft_strcmp(g_b.expenv[i], g_b.expenv[j]) > 0)
			{
				en = g_b.expenv[i];
				g_b.expenv[i] = g_b.expenv[j];
				g_b.expenv[j] = en;
			}
			j++;
		}
		i++;
	}
	ft_print(g_b.expenv);
}
