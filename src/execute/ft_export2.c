/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:43:38 by tandrea           #+#    #+#             */
/*   Updated: 2022/07/20 13:35:04 by ssawane          ###   ########.fr       */
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
		if (str[1])
		{
			write(fd, "=", 1);
			write(fd, "\"", 1);
			write(fd, ft_strchr(env[i], '=') + 1,
					ft_strlen(ft_strchr(env[i], '=')) - 1);
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		ft_free_str(str);
	}
}

int	ft_export_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[0]) && str[0] != '_')
		{
			printf("export: `%s': not a valid identifier\n", str);
			g_b.exit_code = 1;
			return (1);
		}
		if (!ft_isprint(str[i]))
		{
			printf("export: `%s': not a valid identifier\n", str);
			g_b.exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
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
