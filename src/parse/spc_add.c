/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spc_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:37:27 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/03 12:40:08 by ssawane          ###   ########.fr       */
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
	tmp[*j] = shl.line[*i];
	*j += 1;
	*i += 1;
	tmp[*j] = ' ';
	*j += 1;
}

void	spaces_adding_step3(int *j, int *i, char symb, char *tmp)
{
	tmp[*j] = ' ';
	*j += 1;
	tmp[*j] = shl.line[*i];
	*j += 1;
	*i += 1;
	if (shl.line[*i] == symb)
	{
		tmp[*j] = shl.line[*i];
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
	if (rdirects(shl.line) > 0)
	{
		tmp = malloc(sizeof(char *) * (ft_strlen(shl.line)
					+ (rdirects(shl.line) * 2)));
		while (shl.line[i])
		{
			if (shl.line[i] == '|' && !isquoted(shl.line, i, j))
				spaces_adding_step2(&j, &i, tmp);
			else if (!isquoted(shl.line, i, j) && (shl.line[i] == '<'
					|| shl.line[i] == '>'))
				spaces_adding_step3(&j, &i, shl.line[i], tmp);
			else
				tmp[j++] = shl.line[i++];
		}
		tmp[j] = '\0';
		free(shl.line);
		shl.line = tmp;
	}
	return (0);
}
