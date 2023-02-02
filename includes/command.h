/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:50:11 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/02 16:42:39 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_command
{
	int		pipe;
	int		pipe_fd;
	int		file_in_fd;
	int		file_out_fd;
	char	*cmd_path;
	char	**cmd;
	// 여기 원하는거 추가
	// 명령어 경로
	// 파이프
	// 리다이렉션
	// 등등
}	t_command;

void	command_init(t_command *cmd);

#endif