/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:08:31 by yim               #+#    #+#             */
/*   Updated: 2023/02/15 15:44:08 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern int	g_errno;

void	execute_cmdprefix(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	execute_ioredirect(astree->left, cmd);
	execute_cmdprefix(astree->right, cmd, envp);
}

void	execute_simplecmd(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	execute_cmdprefix(astree->left, cmd, envp);
	execute_cmdsuffix(astree->right, cmd, envp);
	if (astree->data != NULL)
	{
		(cmd->cmd)[0] = ft_strdup(astree->data);
		if ((cmd->cmd)[0] == NULL)
		{
			printf ("malloc error");
			return ;
		}
		find_access_path(astree->data, cmd);
		if (cmd->cmd == NULL)
			return ;
		(cmd->cmd)[cmd->argc] = NULL;
	}
}

void	execute_command(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	cmd->cmd = (char **)malloc (sizeof(char *) * (get_argc(astree) + 1));
	if (cmd->cmd == NULL)
		return ;
	ft_memset(cmd->cmd, 0, sizeof(char *) * (get_argc(astree) + 1));
	execute_simplecmd(astree, cmd, envp);
	if ((cmd->cmd)[0] != NULL)
		execve_command(cmd, envp);
	rezero_cmd(cmd);
}

void	execute_cmdline(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	if (cmd->pipe_after)
		cmd->pipe_before = 1;
	if (astree->type == NODE_PIPE)
	{
		cmd->pipe_after = 1;
		execute_command(astree->left, cmd, envp);
		execute_cmdline(astree->right, cmd, envp);
	}
	else
	{
		cmd->pipe_after = 0;
		execute_command(astree, cmd, envp);
	}
}

void	execute(t_astnode *astree, char *envp[])
{
	t_command	cmd;

	command_init(&cmd, envp);
	execute_cmdline(astree, &cmd, envp);
	wait_all(&cmd);
	set_signal(SIG_SHELL);
	free_double_array(cmd.path);
}
