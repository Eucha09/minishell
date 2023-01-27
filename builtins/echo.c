/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:58:29 by yim               #+#    #+#             */
/*   Updated: 2023/01/27 14:48:59 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo(char *str, int flag)
{
	ft_putstr_fd(str, 1);
	if (flag != TRUE)
		write (1, "\n", 1);
	return (CODE_OK);
}
