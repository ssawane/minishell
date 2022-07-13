/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:17:57 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/12 14:03:16 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sighandler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_proc(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	sa.sa_handler = sighandler;
	sigaction(SIGINT, &sa, NULL);
}