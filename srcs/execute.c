/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:05:54 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/08 15:18:10by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

void	execute_ioredirect(t_astnode *astree, t_command *cmd)
{
	if (astree == NULL)
		return ;
	// type에 따라 redirection 처리
	if (astree->type == NODE_REDIRECT_OUT) // > filename
		cmd->file_out_fd = open(astree->data, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (astree->type == NODE_DREDIRECT_OUT) // >> filename
		cmd->file_out_fd = open(astree->data, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (astree->type == NODE_REDIRECT_IN) // < filename
		cmd->file_in_fd = open(astree->data, O_RDWR);
	else if (astree->type == NODE_DREDIRECT_IN) // << here_end
		cmd->file_in_fd = make_here_doc(astree->data);
	if (cmd->file_in_fd == -1 || cmd->file_out_fd == -1)
		perror("minishell");
}

void	execute_cmdsuffix(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	execute_ioredirect(astree->left, cmd);
	
	// 2중배열에 1칸씩 증가하면서 넣기
	// cmd 인자에 대한 처리
	if (astree->data != NULL)
	{
		(cmd->cmd)[cmd->argc] = ft_strdup(astree->data);
		cmd->argc++;
	}
	// if (astree->data != NULL) // temp
	// 	ft_printf("%s ", astree->data);
	
	execute_cmdsuffix(astree->right, cmd, envp);
}

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
	// if (astree->data != NULL) // temp
	// 	ft_printf("%s ", astree->data);
	
	//cmd->cmd 이중배열의 가장 첫번째 인자 넣고 이후 suffix로 반복해서 넣음
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
	execute_simplecmd(astree, cmd, envp);
	if (cmd_error_check(cmd))
		return ;
	if (check_builtins((cmd->cmd)[0]) && cmd->pipe_before == 0)
		excute_builtins(cmd, envp);
	else
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

void	wait_all(void)
{
	pid_t	pid;
	int		temp;

	pid = 1;
	while (pid != -1)
		pid = wait(&temp);
}

void	execute(t_astnode *astree, char *envp[])
{
	t_command	cmd;

	command_init(&cmd, envp);
	execute_cmdline(astree, &cmd, envp);
	wait_all();
	// (cmd->cmd, cmd->path, cmd->access_path) free하기
}
