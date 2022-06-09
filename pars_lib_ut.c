/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lib_ut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:23:34 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/09 10:37:33 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cell	*ft_celllast(t_cell *cell)
{
	if (!cell)
		return (NULL);
	while (cell -> next)
		cell = cell -> next;
	return (cell);
}

void	ft_celladd_back(t_cell **cell, t_cell *new)
{
	t_cell	*p;

	if (!new)
		return ;
	if (!*cell)
	{
		*cell = new;
		return ;
	}
	p = ft_celllast(*cell);
	p -> next = new;
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	words(char *t, char c)
{
	int	sl;
	int	n;
	int	i;

	sl = 0;
	n = 0;
	i = 0;
	while (t[i])
	{
		if (t[i] != c && !n)
		{
			sl++;
			n = 1;
		}
		if (t[i] == c)
			n = 0;
		i++;
	}
	return (sl);
}

char	*record(char *t, int *start, int finish)
{
	char	*w;
	int		i;

	i = 0;
	w = malloc(sizeof(char) * (finish - *start + 1));
	while (*start < finish)
	{
		w[i] = t[*start];
		*start += 1;
		i++;
	}
	w[i] = '\0';
	*start = -1;
	return (w);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	int		n;
	int		j;

	i = 0;
	n = -1;
	j = 0;
	if (!s)
		return (NULL);
	str = malloc((words((char *)s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (i <= (size_t)ft_strlen((char *)s))
	{
		if (s[i] != c && n < 0)
			n = i;
		else if ((s[i] == c || i == (size_t)ft_strlen((char *)s)) && n >= 0)
			str[j++] = record((char *)s, &n, i);
		i++;
	}
	str[j] = 0;
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

t_cell	*ft_cellnew(char *content)
{
	t_cell	*new;

	new = malloc(sizeof(t_cell));
	if (new == NULL)
		return (NULL);
	new -> word = content;
	new -> type = 1;
	if (!ft_strcmp(content, "|"))
		new -> type = 3;
	else if (!ft_strcmp(content, ">") || !ft_strcmp(content, ">>") || !ft_strcmp(content, "<")
			|| !ft_strcmp(content, "<<"))
		new -> type = 2;
	new -> next = NULL;
	return (new);
}

