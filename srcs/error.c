/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:55:20 by yim               #+#    #+#             */
/*   Updated: 2023/02/15 14:34:10 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

extern int	g_errno;

int	code_error(char *str, int errno)
{
	g_errno = errno;
	printf("%s\n", str);
	return (errno);
}

int	free_code_error(char *free_str, int i)
{
	free(free_str);
	return (i);
}
