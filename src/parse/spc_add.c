/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spc_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:37:27 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/14 15:52:39 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	rdirects(char *line)
{
	int	i;
	int	k;

	k = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
			k++;
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
				i++;
			k++;
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
				i++;
			k++;
		}
	}
	return (k);
}

int	isquoted(char *line, int i, int k)
{
	int	j;

	j = -1;
	while (line[++j])
	{
		if (line[j] == 34)
		{
			k = j;
			while (line[++j])
				if (line[j] == 34)
					break ;
			if (i > k && i < j)
				return (1);
		}
		if (line[j] == 39)
		{
			k = j;
			while (line[++j])
				if (line[j] == 39)
					break ;
			if (i > k && i < j)
				return (1);
		}
	}
	return (0);
}

void	spaces_adding_step2(int *j, int *i, char *tmp)
{
	tmp[*j] = ' ';
	*j += 1;
	tmp[*j] = g_b.line[*i];
	*j += 1;
	*i += 1;
	tmp[*j] = ' ';
	*j += 1;
}

void	spaces_adding_step3(int *j, int *i, char symb, char *tmp)
{
	tmp[*j] = ' ';
	*j += 1;
	tmp[*j] = g_b.line[*i];
	*j += 1;
	*i += 1;
	if (g_b.line[*i] == symb)
	{
		tmp[*j] = g_b.line[*i];
		*j += 1;
		*i += 1;
	}
	tmp[*j] = ' ';
	*j += 1;
}

int	spaces_adding(void)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (rdirects(g_b.line) > 0)
	{
		tmp = malloc(sizeof(char *) * (ft_strlen(g_b.line)
					+ (rdirects(g_b.line) * 2)));
		while (g_b.line[i])
		{
			if (g_b.line[i] == '|' && !isquoted(g_b.line, i, j))
				spaces_adding_step2(&j, &i, tmp);
			else if (!isquoted(g_b.line, i, j) && (g_b.line[i] == '<'
					|| g_b.line[i] == '>'))
				spaces_adding_step3(&j, &i, g_b.line[i], tmp);
			else
				tmp[j++] = g_b.line[i++];
		}
		tmp[j] = '\0';
		free(g_b.line);
		g_b.line = tmp;
	}
	return (0);
}
