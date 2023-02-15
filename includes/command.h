/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:50:11 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/15 15:44:00 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "astree.h"
# include "libft.h"
# include <stdio.h>

typedef struct s_command
{
	int		pipe_before;
	int		pipe_after;
	int		pipe_fd;
	int		file_in_fd;
	int		file_out_fd;
	int		argc;
	int		error_code;
	long	pid;
	char	**path;
	char	**cmd;
}	t_command;

void	command_init(t_command *cmd, char *envp[]);
int		get_argc(t_astnode *astree);

#endif