/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:56:07 by yim               #+#    #+#             */
/*   Updated: 2023/01/30 14:34:51 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(void)
{
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * 1024);
	if (cwd == NULL)
		return (code_error("malloc error"));
	ft_memset(cwd, 0, sizeof(char) * 1024);
	getcwd(cwd, sizeof(char) * 1024);
	printf("%s\n", cwd);
	free(cwd);
	return (CODE_OK);
}
