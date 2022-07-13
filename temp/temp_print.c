/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:15:38 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/07 11:04:43 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print(void)
{
	int	i = -1;
	printf("line: %s\n", shl.line);
	if (shl.words)
	{
		while (shl.words[++i])
			printf("%s\n", shl.words[i]);
	}
	else
		printf("%s\n", "nowords");
}

void	print2()
{
	t_cell	*tmp;
	
	tmp = shl.cells;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->word);
		printf("%d\n", tmp->type);
		tmp = tmp->next;
	}
}

void	print3()
{
	t_cmd	*tmp;
	int		i;

	tmp = shl.cmds;
	while (tmp != NULL)
	{
		printf("in: %d\n", tmp->in);
		printf("out: %d\n", tmp->out);
		// printf("stop: %s\n", tmp->stop);
		if (tmp->oper)
		{
			i = -1;
			while (tmp->oper[++i])
			{
				printf("i: %d\n", i);
				printf("cmd: %s\n", tmp->oper[i]);
				// printf("strlen: %d\n", ft_strlen(tmp->oper[i]));
			}
		}
		printf("%c", '\n');
		tmp = tmp->next;
	}
}

// sdfsd><djds|sd|>>dsfdg<<ds|||>>>>>>>|
// < file1 cmd key1 key2 > file2