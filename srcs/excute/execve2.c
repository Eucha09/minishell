/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:01:20 by yim               #+#    #+#             */
/*   Updated: 2023/02/16 19:41:22 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern int	g_errno;

void	rezero_cmd(t_command *cmd)
{
	free_double_array(cmd->cmd);
	if (cmd->file_in_fd != 0)
		close (cmd->file_in_fd);
	if (cmd->file_out_fd != 0)
		close (cmd->file_out_fd);
	cmd->argc = 1;
	cmd->file_in_fd = 0;
	cmd->file_out_fd = 0;
	cmd->error_code = 0;
}

int	cmd_error_check(t_command *cmd)
{
	if (cmd->file_in_fd == -1 || cmd->file_out_fd == -1)
	{
		rezero_cmd(cmd);
		return (1);
	}
	if (cmd->error_code != 0)
	{
		rezero_cmd(cmd);
		return (1);
	}
	return (0);
}

void	excute_builtins(t_command *cmd, char **envp)
{
	if (!ft_strcmp((cmd->cmd)[0], "echo"))
		g_errno = echo(cmd->cmd, cmd->file_out_fd);
	if (!ft_strcmp((cmd->cmd)[0], "cd"))
		g_errno = cd(envp, (cmd->cmd)[1]);
	if (!ft_strcmp((cmd->cmd)[0], "pwd"))
		g_errno = pwd(cmd->file_out_fd);
	if (!ft_strcmp((cmd->cmd)[0], "export"))
		g_errno = export(envp, cmd->cmd, cmd->file_out_fd);
	if (!ft_strcmp((cmd->cmd)[0], "unset"))
		g_errno = unset(envp, cmd->cmd);
	if (!ft_strcmp((cmd->cmd)[0], "env"))
		g_errno = env(envp, cmd->file_out_fd);
	if (!ft_strcmp((cmd->cmd)[0], "exit"))
		ft_exit(cmd);
}

void	execve_child2(t_command *cmd, int fd[2], char **envp)
{
	if (cmd->file_out_fd)
	{
		dup2(cmd->file_out_fd, STDOUT_FILENO);
		if (cmd->pipe_after)
			close(fd[1]);
	}
	else
	{
		if (cmd->pipe_after)
			dup2(fd[1], STDOUT_FILENO);
	}
	if (!cmd_error_check(cmd))
		execve((cmd->cmd)[0], cmd->cmd, envp);
	exit(g_errno);
}

void	execve_child(t_command *cmd, int fd[2], char **envp)
{
	if (cmd->pipe_after)
		close(fd[0]);
	if (cmd->file_in_fd)
	{
		dup2(cmd->file_in_fd, STDIN_FILENO);
		if (cmd->pipe_before)
			close(cmd->pipe_fd);
	}
	else
	{
		if (cmd->pipe_before)
			dup2(cmd->pipe_fd, STDIN_FILENO);
	}
	execve_child2(cmd, fd, envp);
}
