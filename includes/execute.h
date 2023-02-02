/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:06:14 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/02 17:35:57 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "astree.h"
# include "command.h"
# include <fcntl.h>
# include <stdio.h>

void	execute(t_astnode *astree, char *envp[]);
//here_doc
int		make_here_doc(char *limiter_bf);
int		make_here_doc2(char *limiter, int fd);

#endif