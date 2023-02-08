/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:37:21 by yim               #+#    #+#             */
/*   Updated: 2023/02/08 20:20:27 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
	execve((cmd->cmd)[0], cmd->cmd, envp);
}

void	execve_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (cmd->pipe_after)
	{
		if (pipe(fd) == -1)
			return (perror("pipe error"));
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork error"));
	else if (pid == 0)
		execve_child(cmd, fd, envp);
	else
	{
		if (cmd->pipe_before)
			close(cmd->pipe_fd);
		if (cmd->pipe_after)
		{
			close(fd[1]);
			cmd->pipe_fd = fd[0];
		}
	}
}
