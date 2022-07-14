/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_corr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:13:34 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/14 15:51:41 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*quot_del(char *str, int *start, int symb)
{
	int		j;
	int		k;
	int		t;
	char	*new;

	j = 0;
	k = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	t = *start + 1;
	while (str[t] != symb && str[t] != '\0')
			t++;
	while (k <= t)
	{
		if (str[k] == symb && j >= *start)
			k++;
		else
			new[j++] = str[k++];
	}
	while (str[k] != '\0')
		new[j++] = str[k++];
	new[j] = '\0';
	*start = pointer(t);
	free(str);
	return (new);
}

char	*word_from_env2(char *toenv)
{
	char	*fromenv;
	int		i;

	i = -1;
	fromenv = NULL;
	while (g_b.envv[++i])
	{
		if (!ft_strncmp(g_b.envv[i], toenv, ft_strlen(toenv)))
		{
			fromenv = ft_substr(g_b.envv[i], ft_strlen(toenv),
					ft_strlen(g_b.envv[i]) - ft_strlen(toenv));
			break ;
		}
	}
	return (fromenv);
}

char	*word_from_env(char *str, int k, int j)
{
	char	*toenv;
	char	*fromenv;
	int		i;

	i = 0;
	fromenv = NULL;
	toenv = (char *)malloc(sizeof(char) * (j - k + 2));
	while (k < j)
		toenv[i++] = str[k++];
	toenv[i++] = '=';
	toenv[i] = '\0';
	if (!ft_strcmp(toenv, "?="))
		fromenv = ft_itoa(g_b.exit_code);
	else
		fromenv = word_from_env2(toenv);
	free(toenv);
	return (fromenv);
}

char	*add_fromenv(char *str, int k, int *j)
{
	char	*fromenv;
	char	*tmp;
	char	*res;

	res = NULL;
	fromenv = word_from_env(str, k, *j);
	tmp = ft_substr(str, 0, k - 1);
	if (fromenv)
	{
		res = ft_strjoin(tmp, fromenv);
		free(tmp);
		tmp = res;
		res = ft_strjoin(res, (char *)&str[*j]);
		free(fromenv);
	}
	else
		res = ft_strjoin(tmp, (char *)&str[*j]);
	*j = pointer(ft_strlen(tmp));
	free(tmp);
	free(str);
	return (res);
}

void	quot_correct(void)
{
	g_b.t1 = g_b.cells;
	while (g_b.t1)
	{
		g_b.i = 0;
		while (g_b.t1->word[g_b.i])
		{
			if (g_b.t1->word[g_b.i] == '$')
				g_b.t1->word = dollar(g_b.t1->word, &(g_b.i), 0);
			else if (g_b.t1->word[g_b.i] == 34 || g_b.t1->word[g_b.i] == 39)
			{
				if (g_b.t1->word[g_b.i] == 34)
				{
					if (!dollar_check(g_b.t1->word, g_b.i))
						g_b.t1->word = quot_del(g_b.t1->word, &(g_b.i), 34);
					else
						g_b.t1->word = dollar(g_b.t1->word, &(g_b.i), 1);
				}
				else if (g_b.t1->word[g_b.i] == 39)
					g_b.t1->word = quot_del(g_b.t1->word, &(g_b.i), 39);
			}
			g_b.i++;
		}
		g_b.t1 = g_b.t1->next;
	}
}
