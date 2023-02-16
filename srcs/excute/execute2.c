/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:56:48 by yim               #+#    #+#             */
/*   Updated: 2023/02/16 16:35:41 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern int	g_errno;

void	wait_all(t_command *cmd)
{
	pid_t	pid;
	int		temp;

	pid = 1;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (pid == cmd->pid)
			g_errno = WEXITSTATUS(temp);
	}
}

void	execute_ioredirect(t_astnode *astree, t_command *cmd)
{
	if (astree == NULL)
		return ;
	if (cmd->file_in_fd != -1 && cmd->file_out_fd != -1)
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
			perror("minishell");
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
