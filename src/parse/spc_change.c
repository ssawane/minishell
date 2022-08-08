/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spc_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:14:38 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/14 15:53:48 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntax_error_mes(void)
{
	printf("minishell: syntax error\n");
	return (1);
}

int	quotes_check1(void)
{
	int	i;

	i = -1;
	while (g_b.line[++i])
	{
		if (g_b.line[i] == 34)
		{
			i++;
			while (g_b.line[i] && g_b.line[i] != 34)
				i++;
			if (g_b.line[i] == '\0')
				return (syntax_error_mes());
		}
		else if (g_b.line[i] == 39)
		{
			i++;
			while (g_b.line[i] && g_b.line[i] != 39)
				i++;
			if (g_b.line[i] == '\0')
				return (syntax_error_mes());
		}
	}
	return (0);
}

int	quotes_check2(void)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (g_b.line[++i])
	{
		if (g_b.line[i] == 34)
		{
			while (g_b.line[i] && g_b.line[i] != 34)
			{
				if (g_b.line[i++] == 39)
					flag = 1;
			}
			while (g_b.line[i])
			{
				if (g_b.line[i++] == 34)
					flag = 0;
				if (g_b.line[i] == 39 && flag == 1)
					return (syntax_error_mes());
			}
		}
	}
	return (0);
}

int	quotes_check3(void)
{
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	while (g_b.line[++i])
	{
		if (g_b.line[i] == 39)
		{
			while (g_b.line[i] && g_b.line[i] != 39)
			{
				if (g_b.line[i++] == 34)
					flag = 1;
			}
			while (g_b.line[i])
			{
				if (g_b.line[i++] == 39)
					flag = 0;
				if (g_b.line[i] == 34 && flag == 1)
					return (syntax_error_mes());
			}
		}
	}
	return (0);
}

int	spaces_changing(void)
{
	int	i;

	i = -1;
	if (quotes_check1() || quotes_check2() || quotes_check3())
		return (1);
	while (g_b.line[++i])
	{
		if (g_b.line[i] == 34)
		{
			i++;
			if (g_b.line[i] != 34)
				while (g_b.line[i] != 34)
					i++;
		}
		else if (g_b.line[i] == 39)
		{
			i++;
			if (g_b.line[i] != 39)
				while (g_b.line[i] != 39)
					i++;
		}
		else if (g_b.line[i] == ' ')
			g_b.line[i] = '\n';
	}
	return (0);
}
