/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:00:44 by yim               #+#    #+#             */
/*   Updated: 2023/02/16 19:05:03 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern int	g_errno;

void	excute_first_builtins(t_command *cmd, char **envp, int fd[2])
{
	int	stdout_fd;

	if (cmd->pipe_after)
	{
		if (cmd->file_out_fd)
			close(fd[1]);
		else
			cmd->file_out_fd = fd[1];
		cmd->pipe_fd = fd[0];
		excute_builtins(cmd, envp);
	}
	else
	{
		if (!cmd->file_out_fd)
		{
			stdout_fd = dup(STDOUT_FILENO);
			cmd->file_out_fd = stdout_fd;
			excute_builtins(cmd, envp);
			close(stdout_fd);
		}
		else
			excute_builtins(cmd, envp);
	}
}

void	excute_after_builtins(t_command *cmd, char **envp, int fd[2])
{
	if (cmd->pipe_after)
		close(fd[0]);
	if (cmd->pipe_before)
		close(cmd->pipe_fd);
	if (cmd->file_out_fd)
	{
		dup2(cmd->file_out_fd, STDOUT_FILENO);
		if (cmd->pipe_after)
			close(fd[1]);
	}
	else
	{
		if (cmd->pipe_after)
		{
			dup2(fd[1], STDOUT_FILENO);
			cmd->file_out_fd = fd[1];
		}
	}
	excute_builtins(cmd, envp);
	exit(g_errno);
}

void	excute_after_cmd2(t_command *cmd, pid_t pid, int fd[2])
{
	if (cmd->pipe_after == 0)
		cmd->pid = (long)pid;
	if (cmd->pipe_before)
		close(cmd->pipe_fd);
	if (cmd->pipe_after)
	{
		close(fd[1]);
		cmd->pipe_fd = fd[0];
	}
}

void	excute_after_cmd(t_command *cmd, char **envp, int fd[2])
{
	pid_t	pid;

	set_signal(IGN, IGN);
	pid = fork();
	if (pid < 0)
		return (perror("fork error"));
	else if (pid == 0)
	{
		set_signal(DFL, DFL);
		if (check_builtins((cmd->cmd)[0]))
			excute_after_builtins(cmd, envp, fd);
		else
			execve_child(cmd, fd, envp);
	}
	else
		excute_after_cmd2(cmd, pid, fd);
}

void	execve_command(t_command *cmd, char **envp)
{
	int		fd[2];

	if (cmd->pipe_after)
	{
		if (pipe(fd) == -1)
			return (perror("pipe error"));
	}
	if ((cmd->cmd)[0] != NULL && check_builtins((cmd->cmd)[0]) && \
		cmd->pipe_before == 0 && cmd->pipe_after == 0)
		excute_first_builtins(cmd, envp, fd);
	else
		excute_after_cmd(cmd, envp, fd);
}
