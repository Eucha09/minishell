/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:50:14 by yim               #+#    #+#             */
/*   Updated: 2023/02/13 20:55:07 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_digit(t_command *cmd)
{
	int	i;

	i = 0;
	while ((cmd->cmd)[1][i])
	{
		if (!ft_isdigit((cmd->cmd[1][i])))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->pipe_after == 0 && cmd->pipe_before == 0)
		ft_putstr_fd("exit\n", cmd->file_out_fd);
	if (check_digit(cmd))
		ft_putstr_fd("exit: numeric argument required\n", 2);
	else if ((cmd->cmd)[2] != NULL)
		ft_putstr_fd("exit: too many arguments\n", 2);
	else
		exit(0);
}
