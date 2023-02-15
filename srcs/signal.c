/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:01:52 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/15 14:39:21 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

void	sig_handler1(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler2(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	set_signal(int mode)
{
	if (mode == SIG_SHELL)
	{
		signal(SIGINT, sig_handler1);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_EXECVE_PARENT)
	{
		signal(SIGINT, sig_handler2);
		signal(SIGQUIT, sig_handler2);
	}
	else if (mode == SIG_EXECVE_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == SIG_HEREDOC_PARENT)
	{
		signal(SIGINT, sig_handler2);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_HEREDOC_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}
