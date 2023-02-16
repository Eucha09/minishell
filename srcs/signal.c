/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:01:52 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/16 20:45:37 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

extern int	g_errno;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_errno = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_errno(int sig)
{
	if (sig == SIGINT)
		g_errno = 130;
	else if (sig == SIGQUIT)
		g_errno = 131;
}

void	termsig_handler(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

void	set_signal(int sigint, int sigquit)
{
	if (sigint == DFL)
		signal(SIGINT, SIG_DFL);
	else if (sigint == IGN)
		signal(SIGINT, SIG_IGN);
	else if (sigint == HDL)
		signal(SIGINT, sig_handler);
	if (sigquit == DFL)
		signal(SIGQUIT, SIG_DFL);
	else if (sigquit == IGN)
		signal(SIGQUIT, SIG_IGN);
	else if (sigquit == HDL)
		signal(SIGQUIT, sig_handler);
}
