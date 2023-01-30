/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:55:20 by yim               #+#    #+#             */
/*   Updated: 2023/01/29 21:45:25 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	code_error(char *str)
{
	printf("%s\n", str);
	return (CODE_ERROR);
}

int	free_code_error(char *free_str, int i)
{
	free(free_str);
	return (i);
}
