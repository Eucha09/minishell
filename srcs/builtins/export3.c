/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:10:47 by yim               #+#    #+#             */
/*   Updated: 2023/02/17 13:41:50 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int	g_errno;

void	add_envp(char **envp, char *str)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	if (i > 241)
	{
		printf ("envp max error");
		g_errno = 1;
		return ;
	}
	envp[i] = ft_strdup(str);
	envp[i + 1] = NULL;
}

int	check_key_double(char **envp, char *str)
{
	char	*envp_key;
	char	*str_key;
	int		i;

	str_key = find_key(str);
	i = 0;
	if (str_key == NULL)
		return (-1);
	while (envp[i])
	{
		envp_key = find_key(envp[i]);
		if (envp_key == NULL)
			free_code_error(str_key, -1);
		if (!ft_strcmp(envp_key, str_key))
		{
			free(envp_key);
			free(str_key);
			return (i + 1);
		}
		free(envp_key);
		i++;
	}
	free(str_key);
	return (FALSE);
}
