/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:15:38 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/09 15:47:40 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(t_shell *shell)
{
	int	i = -1;
	printf("line2: %s\n", shell->line);
	while (shell->words[++i])
		printf("%s\n", shell->words[i]);
}

void	print2(t_shell *shell)
{
	t_cell	*tmp;
	
	tmp = shell->cells;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->word);
		printf("%d\n", tmp->type);
		tmp = tmp->next;
	}
}

void	print3(t_shell *shell)
{
	t_cmd	*tmp;
	int		i;

	tmp = shell->cmds;
	while (tmp != NULL)
	{
		printf("in: %d\n", tmp->in);
		printf("out: %d\n", tmp->out);
		printf("stop: %s\n", tmp->stop);
		i = -1;
		while (tmp->oper[++i])
			printf("cmd: %s\n", shell->words[i]);
		tmp = tmp->next;
	}
}

// sdfsd><djds|sd|>>dsfdg<<ds|||>>>>>>>|