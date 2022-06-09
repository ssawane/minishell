/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line_corr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:14:38 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/08 13:47:31 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirects_counter(char *line)
{
	int	i;
	int	k;

	k = 0;
	i = -1;
	while(line[++i])
	{
		if (line[i] == '|')
			k++;
		else if(line[i] == '>')
		{
			if (line[i + 1] == '>')
				i++;
			k++;
		}
		else if(line[i] == '<')
		{
			if (line[i + 1] == '<')
				i++;
			k++;
		}
	}
	return (k);
}

void	line_correcting(t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = redirects_counter(shell->line);
	if (j > 0)
	{
		i = 0;
		j = 0;
		tmp = malloc(sizeof(char *) * (ft_strlen(shell->line) + (j * 2)));
		while (shell->line[i])
		{
			if (shell->line[i] == '|')
				{
					tmp[j++] = ' ';
					tmp[j++] = shell->line[i++];
					tmp[j++] = ' ';
				}
			else if (shell->line[i] == '>')
			{
				tmp[j++] = ' ';
				tmp[j++] = shell->line[i++];
				if (shell->line[i] == '>')
					tmp[j++] = shell->line[i++];
				tmp[j++] = ' ';
			}
			else if (shell->line[i] == '<')
			{
				tmp[j++] = ' ';
				tmp[j++] = shell->line[i++];
				if (shell->line[i] == '<')
					tmp[j++] = shell->line[i++];
				tmp[j++] = ' ';
			}
			else
				tmp[j++] = shell->line[i++];
		}
		tmp[j] = '\0';
		free(shell->line);
		shell->line = tmp;
	}
}