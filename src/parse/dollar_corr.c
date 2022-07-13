/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_corr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:54:12 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/12 16:12:35 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*quot_del_after_dollar(char *str, int start, int *end)
{
	char	*new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (*end == start)
	{
		*end += 1;
		while (str[*end] != 34)
			*end += 1;
	}
	while (str[k])
	{
		if (k == start || k == *end)
			k++;
		else
			new[i++] = str[k++];
	}
	new[i] = '\0';
	*end -= 1;
	free(str);
	return (new);
}

char	*incorrect_dollar(char *str, int *start)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	i = *start - 2;
	k = 0;
	while (str[++i] == '$')
		k++;
	j = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(str) - k + 1));
	k = 0;
	while (str[j])
	{
		if (str[j] == '$' && j >= *start - 1 && j < i)
			j++;
		else
			res[k++] = str[j++];
	}
	res[k] = '\0';
	while (str[i] && str[i] != 34 && str[i] != 39 && str[i] != '$')
		i++;
	*start = i - j + k - 1;
	free(str);
	return (res);
}

char	*dollar_step2(char *str, int *p)
{
	int		k;
	char	*res;

	*p += 1;
	k = 0;
	res = NULL;
	if (str[*p] == '$')
		res = incorrect_dollar(str, p);
	else
	{
		k = *p;
		while (str[*p] && str[*p] != 34 && str[*p] != 39
			&& str[*p] != '$' && str[*p] != ' ' && str[*p - 1] != '?')
			*p += 1;
		if (*p > k)
			res = add_fromenv(str, k, p);
		else
		{
			res = str;
			*p -= 1;
		}
	}
	return (res);
}

char	*dollar(char *str, int *p, int flag)
{
	int		j;

	j = *p;
	if (str[*p] == 34)
		*p += 1;
	while ((flag == 1 && str[*p] && str[*p] != 34)
		|| (flag == 0 && str[*p] && str[*p] != 34 && str[*p] != 39))
	{
		if (str[*p] == '$')
			str = dollar_step2(str, p);
		*p += 1;
	}
	if (flag == 1)
		str = quot_del_after_dollar(str, j, p);
	*p -= 1;
	return (str);
}
