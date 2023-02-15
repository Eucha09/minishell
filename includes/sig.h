/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:36:53 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/15 14:42:06 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <stdio.h>
# include <signal.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define SIG_SHELL			0
# define SIG_EXECVE_PARENT	1
# define SIG_EXECVE_CHILD	2
# define SIG_HEREDOC_PARENT	3
# define SIG_HEREDOC_CHILD	4

void	set_signal(int mode);

#endif