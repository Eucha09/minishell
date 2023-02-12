/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:33:54 by yim               #+#    #+#             */
/*   Updated: 2023/02/12 15:19:15 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	us_delete_envp(char **envp, char *str)
{
	int		delete_index;

	delete_index = (check_key_double(envp, str) - 1);
	while (envp[delete_index + 1])
	{
		free (envp[delete_index]);
		envp[delete_index] = ft_strdup(envp[delete_index + 1]);
		delete_index++;
	}
	free (envp[delete_index]);
	envp[delete_index] = NULL;
}

int	unset(char **envp, char **cmd)
{
	int		i;
	char	*str;

	i = 1;
	while (cmd[i])
	{
		str = cmd[i];
		if (str == NULL)
			return (code_error("unset: not enough arguments"));
		if (ft_strchr(str, '=') || check_ep_first(str))
			return (code_error("unset: invalid parameter name"));
		if (check_key_double(envp, str) == -1)
			return (code_error("malloc error"));
		if (check_key_double(envp, str) == FALSE)
			return (CODE_OK);
		us_delete_envp(envp, str);
		i++;
	}
	return (CODE_OK);
}
