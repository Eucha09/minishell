/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:50:11 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/03 20:33:08 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "astree.h"

typedef struct s_command
{
	int		pipe;
	int		pipe_fd;
	int		redirect;
	int		file_in_fd;
	int		file_out_fd;
	int		argc;
	int		total_argc;
	char	*cmd_path;
	char	**cmd;
	// 여기 원하는거 추가
	// 명령어 경로
	// 파이프
	// 리다이렉션
	// 등등
}	t_command;

void	command_init(t_command *cmd);
int		get_argc(t_astnode *astree);

#endif