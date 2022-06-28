/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line_corr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:14:38 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/20 19:46:25 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

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
		else if (line[i] == '$')
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

int	isquoted(char *line, int i)
{
	int	j;
	int	k;

	j = -1;
	while (line[++j])
	{
		if (line[j] == 34)
		{
			k = j;
			while (line[++j])
				if (line[j] == 34)
					break;
			if (i > k && i < j)
				return (1);
		}
		if (line[j] == 39)
		{
			k = j;
			while (line[++j])
				if (line[j] == 39)
					break;
			if (i > k && i < j)
				return (1);
		}
		k = 0;
	}
	return (0);
}

int	spaces_adding(t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	j = redirects_counter(shell->line);
	if (j > 0)
	{
		i = 0;
		j = 0;
		tmp = malloc(sizeof(char *) * (ft_strlen(shell->line) + (j * 2)));
		while (shell->line[i])
		{
			if (shell->line[i] == '|' && !isquoted(shell->line, i))
				{
					tmp[j++] = ' ';
					tmp[j++] = shell->line[i++];
					tmp[j++] = ' ';
				}
			else if (shell->line[i] == '>' && !isquoted(shell->line, i))
			{
				tmp[j++] = ' ';
				tmp[j++] = shell->line[i++];
				if (shell->line[i] == '>')
					tmp[j++] = shell->line[i++];
				tmp[j++] = ' ';
			}
			else if (shell->line[i] == '<' && !isquoted(shell->line, i))
			{
				tmp[j++] = ' ';
				tmp[j++] = shell->line[i++];
				if (shell->line[i] == '<')
					tmp[j++] = shell->line[i++];
				tmp[j++] = ' ';
			}
			else if (shell->line[i] == '$' && !isquoted(shell->line, i))
			{
				tmp[j++] = ' ';
				tmp[j++] = shell->line[i++];
			}
			else
				tmp[j++] = shell->line[i++];
		}
		tmp[j] = '\0';
		free(shell->line);
		shell->line = tmp;
	}
	return (0);
}

int	syntax_error_mes(void)
{
	printf("minishell: syntax error\n");
	return (1);
}

int	quotes_check(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->line[++i])
	{
		if (shell->line[i] == 34)
		{
			i++;
			while (shell->line[i] && shell->line[i] != 34)
				i++;
			if (shell->line[i] == '\0')
				return(syntax_error_mes());
		}
		else if (shell->line[i] == 39)
		{
			i++;
			while (shell->line[i] && shell->line[i] != 39)
				i++;
			if (shell->line[i] == '\0')
				return(syntax_error_mes());
		}
	}
	return (0);
}

int	quotes_check2(t_shell *shell)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (shell->line[++i])
	{
		if (shell->line[i] == 34)
		{
			while (shell->line[i] && shell->line[i] != 34)
			{
				if (shell->line[i++] == 39)
					flag = 1;
			}
			while (shell->line[i])
			{
				if (shell->line[i++] == 34)
					flag = 0;
				if (shell->line[i] == 39 && flag == 1)
					return(syntax_error_mes());
			}
		}
	}
	return (0);
}

int	quotes_check3(t_shell *shell)
{
	int	i;
	int	flag;
	
	i = -1;
	flag = 0;
	while (shell->line[++i])
	{
		if (shell->line[i] == 39)
		{
			while (shell->line[i] && shell->line[i] != 39)
			{
				if (shell->line[i++] == 34)
					flag = 1;
			}
			while (shell->line[i])
			{
				if (shell->line[i++] == 39)
					flag = 0;
				if (shell->line[i] == 34 && flag == 1)
					return(syntax_error_mes());
			}
		}
	}
	return (0);
}

int	spaces_changing(t_shell *shell)
{
	int	i;

	i = 0;
	if (quotes_check(shell) || quotes_check2(shell) || quotes_check3(shell))
		return (1);
	while (shell->line[i])
	{
		if (shell->line[i] == 34)
		{
			i++;
			while (shell->line[i] != 34)
				i++;
			i++;
		}
		if (shell->line[i] == 39)
		{
			i++;
			while (shell->line[i] != 39)
				i++;
			i++;
		}
		if (shell->line[i] == ' ')
			shell->line[i] = '\n';
		i++;
	}
	return (0);
}