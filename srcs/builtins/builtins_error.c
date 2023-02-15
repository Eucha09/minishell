/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:55:20 by yim               #+#    #+#             */
/*   Updated: 2023/02/15 14:25:36 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int	g_errno;

int	code_error(char *str)
{
	g_errno = 1;
	printf("%s\n", str);
	return (CODE_ERROR);
}

int	free_code_error(char *free_str, int i)
{
	free(free_str);
	return (i);
}
