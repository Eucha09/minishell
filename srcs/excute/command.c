/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:04:20 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/16 19:56:29 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	find_path(t_command *cmd, char *envp[])
{
	int		i;
	char	*tmp_path;

	i = 0;
	tmp_path = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			tmp_path = envp[i] + 5;
		i++;
	}
	if (tmp_path == NULL)
	{
		cmd->path = NULL;
		return ;
	}
	cmd->path = ft_split(tmp_path, ':');
	if (cmd->path == NULL)
	{
		cmd->error_code = 1;
		perror("malloc error");
	}
}

void	command_init(t_command *cmd, char *envp[])
{
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->argc = 1;
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
