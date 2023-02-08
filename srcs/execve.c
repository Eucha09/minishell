/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:37:21 by yim               #+#    #+#             */
/*   Updated: 2023/02/08 16:00:05 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	rezero_cmd(t_command *cmd)
{
	free_double_array(cmd->cmd);
	cmd->argc = 0;
}

int	cmd_error_check(t_command *cmd)
{
	if (cmd->file_in_fd == -1 || cmd->file_out_fd == -1)
		return (1);
	if (cmd->error_code != 0)
		return (1);
	return (0);
}

void	excute_builtins(t_command *cmd, char **envp)
{		
	// if (cmd->file_in_fd != 0)
	// 	dup2(cmd->file_in_fd, STDIN_FILENO);
	// if (cmd->file_out_fd != 0)
	// 	dup2(cmd->file_out_fd, STDOUT_FILENO);
	// if (ft_strcmp(simplecmd, "export"))
	// 	export();
	// if (ft_strcmp(simplecmd, "unset"))
	// 	unset();
	// if (ft_strcmp(simplecmd, "env"))
	// 	env(envp);
	// if (ft_strcmp(simplecmd, "cd"))
	// 	cd();
	// if (ft_strcmp(simplecmd, "pwd"))
	// 	pwd();
	// if (ft_strcmp(simplecmd, "echo"))
	// 	echo();
	// if (cmd->file_in_fd != 0)
	// 	dup2(STDIN_FILENO, cmd->file_in_fd);
	// if (cmd->file_out_fd != 0)
	// 	dup2(STDOUT_FILENO, cmd->file_out_fd);
}
