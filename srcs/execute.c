/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:05:54 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/06 20:50:39 by yim              ###   ########.fr       */
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
	cmd->cmd[cmd->argc] = ft_strdup(astree->data);
	cmd->argc++;
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
	
	//cmd->cmd 이중배열의 가장 첫번째 인자 넣고 이후 suffix로 반복해서 넣음
	cmd->cmd[0] = ft_strdup(astree->data);
	if (cmd->cmd[0] == NULL)
	{
		printf ("malloc error");
		return ;
	}
	cmd->argc++;
	//cmd->path 찾는 과정
	find_access_path(astree->data, cmd);
	if (cmd->cmd == NULL)
		return ;
	execute_cmdsuffix(astree->right, cmd, envp);
	cmd->cmd[cmd->argc] = NULL;

	// 실행
	//command(cmd); forkdifweijiewij execve();
	// ft_printf("\n");
}

int	cmd_error_check(t_command *cmd)
{
	if (cmd->file_in_fd == -1 || cmd->file_out_fd == -1)
		return (1);
	if (cmd->cmd == NULL)
		return (1);
	return (0);
}

void	execute_command(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	cmd->cmd = (char **)malloc (sizeof(char *) * (get_argc(astree) + 1));
	execute_simplecmd(astree, cmd, envp);
	// cmd->file_in_fd == -1 || cmd->file_out_fd == -1 return ;
	// path 에 대한 처리 -> 못찾으면 바로 return;
	if (cmd_error_check(cmd))
		return ;
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

//cmd 이중배열에 넣을 개수 구해서 num 인자로 받기
void	execute(t_astnode *astree, char *envp[])
{
	t_command	cmd;

	command_init(&cmd, envp);
	execute_cmdline(astree, &cmd, envp);
	//wait_all();
	// (cmd->cmd, cmd->path, cmd->access_path) free하기
}
