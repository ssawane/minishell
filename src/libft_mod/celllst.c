/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   celllst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:23:34 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/03 14:45:30 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_cell	*ft_cellnew(char *content)
{
	t_cell	*new;

	new = malloc(sizeof(t_cell));
	if (new == NULL)
		return (NULL);
	new -> word = ft_strdup(content);
	new -> type = 1;
	if (!ft_strcmp(content, "|"))
		new -> type = 3;
	else if (!ft_strcmp(content, ">") || !ft_strcmp(content, ">>")
		|| !ft_strcmp(content, "<") || !ft_strcmp(content, "<<"))
		new -> type = 2;
	new -> next = NULL;
	return (new);
}
