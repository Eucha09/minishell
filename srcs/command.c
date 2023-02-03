/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:04:20 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/03 20:30:55 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"

void	command_init(t_command *cmd)
{
	// t_command 초기화
	ft_memset(cmd, 0, sizeof(t_command));
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