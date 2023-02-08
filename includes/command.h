/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:50:11 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/08 15:30:05 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "astree.h"

typedef struct s_command
{
	int		pipe_before;
	int		pipe_after;
	int		pipe_fd;
	int		file_in_fd;
	int		file_out_fd;
	int		argc;
	int		error_code;
	char	**path;
	char	**cmd;
	// int		error;
	// 여기 원하는거 추가
	// 명령어 경로
	// 파이프
	// 리다이렉션
	// 등등
}	t_command;

void	command_init(t_command *cmd, char *envp[]);
int		get_argc(t_astnode *astree);

#endif