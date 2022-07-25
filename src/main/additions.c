/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:04:49 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/25 21:11:10 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*digitfirst(char *str, int k, int *j)
{
	char	*res;
	char	*tmp;

	res = NULL;
	tmp = ft_substr(str, 0, k - 1);
	if (str[k] == '0')
	{
		res = ft_strjoin(tmp, "minishell");
		free(tmp);
		tmp = res;
		res = ft_strjoin(res, (char *)&str[*j + 1]);
	}
	else
		res = ft_strjoin(tmp, (char *)&str[*j + 1]);
	*j = pointer(ft_strlen(tmp));
	free(tmp);
	free(str);
	return (res);
}

void	tilda_proc(void)
{
	t_cell	*tmp;
	int		i;

	tmp = g_b.cells;
	while (tmp)
	{
		if (!ft_strcmp(tmp->word, "~"))
		{
			i = 0;
			while (ft_strnstr(g_b.envv[i], "HOME=", 5) == NULL)
			{
				if (g_b.envv[++i] == NULL)
				{
					write(2, "error: home folder not set\n", 27);
					return ;
				}
			}
			free(tmp->word);
			tmp->word = ft_substr(g_b.envv[i], 5, ft_strlen(g_b.envv[i]) - 4);
		}
		tmp = tmp->next;
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

void	local_expenv(void)
{
	int		i;

	i = -1;
	g_b.expenv = malloc(sizeof(char *) * (g_b.envnum + 1));
	while (++i < g_b.envnum)
		g_b.expenv[i] = ft_strdup(g_b.envv[i]);
	g_b.expenv[i] = NULL;
}

int	dollar_check(char *word, int i)
{
	i++;
	while (word[i] && word[i] != 34)
	{
		if (word[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
