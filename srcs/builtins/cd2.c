/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:13:50 by yim               #+#    #+#             */
/*   Updated: 2023/02/15 14:14:26 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_cd(char *cwd, char *c_dir, char *str_slash, char *str)
{
	if (cwd != NULL)
		free (cwd);
	if (c_dir != NULL)
		free (c_dir);
	if (str)
		free (str_slash);
}

int	free_cd_error(char *str, char *cwd, char *str_slash)
{
	if (cwd != NULL)
		free (cwd);
	if (str_slash != NULL)
		free(str_slash);
	if (str != NULL)
		perror(str);
	return (CODE_ERROR);
}
