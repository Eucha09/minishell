/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:31:09 by yim               #+#    #+#             */
/*   Updated: 2023/01/30 14:38:05by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**dup_envp(char *envp[])
{
	int		i;
	char	**d_envp;

	i = 0;
	d_envp = (char **)malloc(sizeof(char *) * 250);
	if (d_envp == NULL)
		return (NULL);
	while (envp[i])
	{
		d_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	d_envp[i] = NULL;
	return (d_envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_command cmd;
	char	**d_envp;

	find_access_path(argv[1], &cmd);
	printf("%s\n", cmd.cmd[0]);
	system("leaks minishell");
	
}
