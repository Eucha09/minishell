/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:58:29 by yim               #+#    #+#             */
/*   Updated: 2023/02/09 14:26:40by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo_check_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	init_variable(int *i, int *tmp, int *flag, int *flag2)
{
	*i = 0;
	*tmp = 0;
	*flag = 0;
	*flag2 = 0;
}

int	echo(char **cmd, int file_out_fd)
{
	int	i;
	int	tmp;
	int	flag;
	int	flag2;

	init_variable(&i, &tmp, &flag, &flag2);
	while (cmd[++i])
	{
		if (echo_check_flag(cmd[i]))
			flag = 1;
		else
			flag2 = 1;
		if (flag2)
		{
			ft_putstr_fd (cmd[i], file_out_fd);
			if (cmd[i + 1] != NULL)
				ft_putstr_fd (" ", file_out_fd);
		}
	}
	if (!flag)
		ft_putstr_fd ("\n", file_out_fd);
	return (1);
}
