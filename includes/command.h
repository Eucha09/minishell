/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:50:11 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/02 14:05:44 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_command
{
	// 여기 원하는거 추가
	// 명령어 경로
	// 파이프
	// 리다이렉션
	// 등등
}	t_command;

void	command_init(t_command *cmd);

#endif