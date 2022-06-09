/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:15:38 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/08 12:30:30 by ssawane          ###   ########.fr       */
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
		printf("%d\n", tmp->flag_pipe);
		tmp = tmp->next;
	}
}

// sdfsd><djds|sd|>>dsfdg<<ds|||>>>>>>>|