/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:50:14 by yim               #+#    #+#             */
/*   Updated: 2023/02/14 13:02:38by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int	g_errno;

int	check_digit(t_command *cmd)
{
	int	i;

	i = 0;
	if ((cmd->cmd)[1] == NULL)
		return (0);
	while ((cmd->cmd)[1][i])
	{
		if (!ft_isdigit((cmd->cmd[1][i])))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_command *cmd)
{
	if (cmd->pipe_after == 0 && cmd->pipe_before == 0)
		ft_putstr_fd("exit\n", cmd->file_out_fd);
	if (check_digit(cmd))
	{
		g_errno = 255;
		ft_putstr_fd("exit: numeric argument required\n", 2);
	}
	else if ((cmd->cmd)[1] != NULL && (cmd->cmd)[2] != NULL)
	{
		g_errno = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
	}
	if ((cmd->cmd)[1] == NULL)
		exit(0);
	if (check_digit(cmd) || !((cmd->cmd)[1] != NULL && (cmd->cmd)[2] != NULL))
		exit(ft_atoi((cmd->cmd)[1]));
}
