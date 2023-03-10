/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:45:07 by yim               #+#    #+#             */
/*   Updated: 2023/02/16 19:40:44 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern int	g_errno;

void	free_double_array(char **double_array)
{
	int	i;

	if (double_array == NULL)
		return ;
	i = 0;
	while (double_array[i])
	{
		free (double_array[i]);
		double_array[i] = NULL;
		i++;
	}
	free (double_array);
	double_array = NULL;
}

int	check_builtins(char *simplecmd)
{
	if (simplecmd == NULL)
		return (0);
	if (!ft_strcmp(simplecmd, "env"))
		return (1);
	if (!ft_strcmp(simplecmd, "echo"))
		return (1);
	if (!ft_strcmp(simplecmd, "cd"))
		return (1);
	if (!ft_strcmp(simplecmd, "export"))
		return (1);
	if (!ft_strcmp(simplecmd, "pwd"))
		return (1);
	if (!ft_strcmp(simplecmd, "unset"))
		return (1);
	if (!ft_strcmp(simplecmd, "exit"))
		return (1);
	return (0);
}

int	find_access_path2(t_command *cmd, char *simplecmd)
{
	int		i;
	char	*tmp_path;
	char	*tmp_after_path;

	i = 0;
	while (cmd->path[i])
	{
		tmp_path = ft_strjoin(cmd->path[i], "/");
		if (tmp_path == NULL)
			return (-2);
		tmp_after_path = ft_strjoin(tmp_path, simplecmd);
		if (tmp_after_path == NULL)
			return (free_return(tmp_path, NULL, -2));
		if (access (tmp_after_path, F_OK) == 0)
		{
			free ((cmd->cmd)[0]);
			(cmd->cmd)[0] = ft_strdup(tmp_after_path);
			if ((cmd->cmd)[0] == NULL)
				return (free_return(tmp_path, tmp_after_path, -2));
			return (free_return (tmp_path, tmp_after_path, 0));
		}
		free_return(tmp_path, tmp_after_path, 0);
		i++;
	}
	return (-1);
}

void	find_access_path(char *simplecmd, t_command *cmd)
{
	int	error_num;

	error_num = 0;
	if (check_builtins(simplecmd))
		return ;
	if (access (simplecmd, F_OK) == 0)
		return ;
	if ((cmd->cmd)[0][0] == '\0' || cmd->path == NULL)
	{
		cmd->error_code = 127;
		g_errno = 127;
		printf ("command not found : %s\n", simplecmd);
		return ;
	}
	error_num = find_access_path2(cmd, simplecmd);
	if (error_num == -2)
		printf ("malloc error");
	else if (error_num == -1)
	{
		cmd->error_code = 127;
		g_errno = 127;
		printf ("command not found : %s\n", simplecmd);
	}
}
