/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:36:53 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/16 20:46:31 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <stdio.h>
# include <signal.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define DFL 1
# define IGN 2
# define HDL 3

void	set_signal(int sigint, int sigquit);
void	termsig_handler(int sig);
void	sig_errno(int sig);

#endif