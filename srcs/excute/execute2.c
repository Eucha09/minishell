/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:56:48 by yim               #+#    #+#             */
/*   Updated: 2023/02/16 20:50:35 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern int	g_errno;

void	wait_all(t_command *cmd)
{
	pid_t	pid;
	int		status;
	int		flag;

	flag = 0;
	pid = 1;
	while (pid != -1)
	{
		pid = wait(&status);
		if (pid == cmd->pid)
		{
			g_errno = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				sig_errno(WTERMSIG(status));
		}
		if (WIFSIGNALED(status) && flag == 0)
		{
			flag = 1;
			termsig_handler(WTERMSIG(status));
		}
	}
}

void	execute_ioredirect(t_astnode *astree, t_command *cmd)
{
	if (astree == NULL)
		return ;
	if (cmd->file_in_fd != -1 && cmd->file_out_fd != -1 && g_errno != 130)
	{
		if (astree->type == NODE_REDIRECT_OUT)
			cmd->file_out_fd = \
				open(astree->data, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (astree->type == NODE_DREDIRECT_OUT)
			cmd->file_out_fd = \
				open(astree->data, O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (astree->type == NODE_REDIRECT_IN)
			cmd->file_in_fd = open(astree->data, O_RDWR);
		else if (astree->type == NODE_DREDIRECT_IN)
			cmd->file_in_fd = make_here_doc(astree->data);
		if (cmd->file_in_fd == -1 || cmd->file_out_fd == -1)
		{
			if (g_errno != 130)
			{
				perror("minishell");
				g_errno = 1;
			}
		}
	}
}

void	execute_cmdsuffix(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	execute_ioredirect(astree->left, cmd);
	if (astree->data != NULL)
	{
		(cmd->cmd)[cmd->argc] = ft_strdup(astree->data);
		cmd->argc++;
	}
	execute_cmdsuffix(astree->right, cmd, envp);
}
