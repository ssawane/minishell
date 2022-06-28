/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quotes_corr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:13:34 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/17 15:13:43 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		whichquote(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34)
			return (1);
		else if (str[i] == 39)
			return (2);
	}
	return (0);
}

int		quotes_counter(char *str, int a)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	if (a == 1)
	{
		while (str[++i])
			if (str[i] == 34)
				k++;
	}
	else if (a == 2)
	{
		while (str[++i])
			if (str[i] == 39)
				k++;
	}
	return (k);
}

char	*quotes_deleting(char *str, int a)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) - quotes_counter(str, a) + 1));
	if (a == 1)
	{
		while (str[i])
		{
			while (str[i] == 34)
				i++;
			tmp[j++] = str[i++];
		}
	}
	else if (a == 2)
	{
		while (str[i])
		{
			while (str[i] == 39)
				i++;
			tmp[j++] = str[i++];
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

void	quotes_correcting(t_shell *shell)
{
	t_cell	*tmp;
	char	*tmp2;

	tmp = shell->cells;
	while (tmp)
	{
		if (whichquote(tmp->word) == 1)
			{
				tmp2 = tmp->word;
				tmp->word = quotes_deleting(tmp->word, 1);
				free(tmp2);
			}
		else if (whichquote(tmp->word) == 2)
			{
				tmp2 = tmp->word;
				tmp->word = quotes_deleting(tmp->word, 2);
				free(tmp2);
			}
		tmp = tmp->next;
	}
}