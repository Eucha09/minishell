/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:36:53 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/15 14:38:03 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>

# define SIG_SHELL			0
# define SIG_EXECVE_PARENT	1
# define SIG_EXECVE_CHILD	2
# define SIG_HEREDOC_PARENT	3
# define SIG_HEREDOC_CHILD	4

void	set_signal(int mode);

#endif