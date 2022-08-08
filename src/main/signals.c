/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:17:57 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/08 17:20:16 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	inside_pr(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, inside_pr);
	}
	if (signum == SIGQUIT)
	{
		write(1, "\n", 1);
		signal(SIGQUIT, inside_pr);
	}
}

void	sighandler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	echo_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_b.echo = 0;
	signal(SIGINT, sighandler);
}

void	signals_proc(void)
{
	signal(SIGQUIT, SIG_IGN);
	if (g_b.echo == 0)
		signal(SIGINT, sighandler);
	else
		signal(SIGINT, echo_sig);
}
