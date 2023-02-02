/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:05:54 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/02 14:13:07 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

void	execute_ioredirect(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	// type에 따라 redirection 처리
	if (astree->type == NODE_REDIRECT_OUT) // > filename
	{
		ft_printf("redirect out > %s\n", astree->data);
	}
	else if (astree->type == NODE_DREDIRECT_OUT) // >> filename
	{
		ft_printf("redirect out >> %s\n", astree->data);
	}
	else if (astree->type == NODE_REDIRECT_IN) // < filename
	{
		ft_printf("redirect in < %s\n", astree->data);
	}
	else if (astree->type == NODE_DREDIRECT_IN) // << here_end
	{
		ft_printf("redirect out << %s\n", astree->data);
	}
}

void	execute_cmdsuffix(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	execute_ioredirect(astree->left, cmd, envp);

	// cmd 인자에 대한 처리
	if (astree->data != NULL) // temp
		ft_printf("%s ", astree->data);
	
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

	// cmdpath 에 대한 처리
	if (astree->data != NULL) // temp
		ft_printf("%s ", astree->data);
	
	execute_cmdsuffix(astree->right, cmd, envp);

	// 실행
	//command(cmd); forkdifweijiewij execve();
	ft_printf("\n");
}

void	execute_command(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	execute_simplecmd(astree, cmd, envp);

	// command 진짜 실행
	
}

void	execute_cmdline(t_astnode *astree, t_command *cmd, char *envp[])
{
	if (astree == NULL)
		return ;
	if (astree->type == NODE_PIPE)
	{
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

	command_init(&cmd);
	execute_cmdline(astree, &cmd, envp);
}