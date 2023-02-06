/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:04:20 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/06 16:48:02 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"

void	find_path(t_command *cmd, char *envp[])
{
	int		i;
	char	*tmp_path;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			tmp_path = envp[i] + 5;
		i++;
	}
	cmd->path = ft_split(tmp_path, ':');
	// if (cmd->path == NULL)
	// {
	// 	cmd->error = 1; || return (1);
	// 	perror("malloc error");
	// }
}

void	command_init(t_command *cmd, char *envp[])
{
	// t_command 초기화
	ft_memset(cmd, 0, sizeof(t_command));
	find_path(cmd, envp);
}

int	get_argc(t_astnode *astree)
{
	int	argc;

	if (astree == NULL)
		return (0);
	if (astree->type != NODE_SIMPLE_CMD && astree->type != NODE_CMD_SUFFIX)
		return (0);
	argc = 0;
	if (astree->data != NULL)
		argc = 1;
	return (argc + get_argc(astree->right));
}