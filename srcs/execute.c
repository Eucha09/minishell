/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:05:54 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/02 20:50:03 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

void	execute_ioredirect(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	// type에 따라 redirection 처리
	(void)envp;
	if (cmd->file_in_fd != 0)
		close (cmd->file_in_fd);
	if (cmd->file_out_fd != 0)
		close (cmd->file_out_fd);
	if (astree->type == NODE_REDIRECT_OUT) // > filename
	{
		cmd->file_out_fd = open(astree->data, O_RDWR | O_CREAT | O_TRUNC, 0644);
		cmd->redirect = 1;
	}
	else if (astree->type == NODE_DREDIRECT_OUT) // >> filename
	{
		cmd->file_out_fd = open(astree->data, O_RDWR | O_CREAT | O_APPEND, 0644);
		cmd->redirect = 1;
	}
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
	execute_ioredirect(astree->left, cmd, envp);

	// 2중배열에 1칸씩 증가하면서 넣기
	// cmd 인자에 대한 처리
	// if (astree->data != NULL) // temp
	// 	ft_printf("%s ", astree->data);
	
	execute_cmdsuffix(astree->right, cmd, envp);
}

void	execute_cmdprefix(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
 		return ;
	execute_ioredirect(astree->left, cmd, envp);
	execute_cmdprefix(astree->right, cmd, envp);
}

void	execute_simplecmd(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	execute_cmdprefix(astree->left, cmd, envp);
	// if (astree->data != NULL) // temp
	// 	ft_printf("%s ", astree->data);
	
	execute_cmdsuffix(astree->right, cmd, envp);

	// 실행
	//command(cmd); forkdifweijiewij execve();
	// ft_printf("\n");
}

void	execute_command(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	execute_simplecmd(astree, cmd, envp);
	// path 에 대한 처리 -> 못찾으면 바로 return;
	// pipe가 있는지 확인, 있으면 파이프 해서 실행
	// cmd->pipe 값 하나 내리기
	// 리다이렉션 있으면 파이프 닫고 리다이렉션으로 처리
	// pipe가 없고 빌트인 함수이면 부모 프로세스에서 실행
	// 위 상황 외에는 다 fork
	// command 진짜 실행
	// cmd->cmd와 cmd->argc 초기화
}

void	execute_cmdline(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	if (astree->type == NODE_PIPE)
	{
		cmd->pipe++;
		// pipe에 대한 처리

		execute_command(astree->left, cmd, envp);

		execute_cmdline(astree->right, cmd, envp);
	}
	else // 빌트인이면 빌트인 실행?
		execute_command(astree, cmd, envp);
}

void	execute(t_astnode *astree, char *envp[])
{
	t_command	cmd;

	// 2중 배열 malloc 선언
	command_init(&cmd);
	execute_cmdline(astree, &cmd, envp);
	//wait_all();
}