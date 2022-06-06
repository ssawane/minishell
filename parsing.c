/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/06 17:59:27 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_term_check(char *line)
{
	if (!(ft_strcmp(line, "exit")))
		return (0);
	return (1);
}

int	main_parsing()

int	main()
{
	char	*prompt = "minishell $? ";
	char	*line;
	
	while (close_term_check(line = readline(prompt)))
		printf("%s\n", line);
	return (0);
}