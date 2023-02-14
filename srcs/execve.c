/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:37:21 by yim               #+#    #+#             */
/*   Updated: 2023/02/10 14:52:57 yim              ###   ########.fr       */
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
		echo(cmd->cmd, cmd->file_out_fd);
	if (!ft_strcmp((cmd->cmd)[0], "cd"))
		cd(envp, (cmd->cmd)[1]);
	if (!ft_strcmp((cmd->cmd)[0], "pwd"))
		pwd(cmd->file_out_fd);
	if (!ft_strcmp((cmd->cmd)[0], "export"))
		export(envp, cmd->cmd, cmd->file_out_fd);
	if (!ft_strcmp((cmd->cmd)[0], "unset"))
		unset(envp, cmd->cmd);
	if (!ft_strcmp((cmd->cmd)[0], "env"))
		env(envp, cmd->file_out_fd);
	if (!ft_strcmp((cmd->cmd)[0], "exit"))
		ft_exit(cmd);
}

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
	exit(0);
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
	if (!cmd_error_check(cmd))
		execve((cmd->cmd)[0], cmd->cmd, envp);
	exit(0);
}

void	excute_after_cmd(t_command *cmd, char **envp, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork error"));
	else if (pid == 0)
	{
		set_signal(SIG_CHILD_MODE);
		if (check_builtins((cmd->cmd)[0]))
			excute_after_builtins(cmd, envp, fd);
		else
			execve_child(cmd, fd, envp);
	}
	else
	{
		set_signal(SIG_EXECVE_MODE);
		if (cmd->pipe_before)
			close(cmd->pipe_fd);
		if (cmd->pipe_after)
		{
			close(fd[1]);
			cmd->pipe_fd = fd[0];
		}
	}
}

void	execve_command(t_command *cmd, char **envp)
{
	int		fd[2];

	if (cmd->pipe_after)
	{
		if (pipe(fd) == -1)
			return (perror("pipe error"));
	}
	if (check_builtins((cmd->cmd)[0]) && \
		cmd->pipe_before == 0 && cmd->pipe_after == 0)
		excute_first_builtins(cmd, envp, fd);
	else
		excute_after_cmd(cmd, envp, fd);
}
