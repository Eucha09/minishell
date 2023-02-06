/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:45:07 by yim               #+#    #+#             */
/*   Updated: 2023/02/06 16:56:59 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

int	free_return(char *tmp, char *tmp2, int num)
{
	if (tmp != NULL)
		free (tmp);
	if (tmp2 != NULL)
		free (tmp2);
	return (num);
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
			return (-1);
		tmp_after_path = ft_strjoin(tmp_path, simplecmd);
		if (tmp_after_path == NULL)
			return (free_return(tmp_path, NULL, -1));
		if (access (tmp_after_path, F_OK) == 0)
		{
			cmd->access_path = ft_strdup(tmp_after_path);
			if (cmd->access_path == NULL)
				return (free_return(tmp_path, tmp_after_path, -1));
			return (free_return (tmp_path, tmp_after_path, 0));
		}
		free (tmp_path);
		free (tmp_after_path);
		i++;
	}
	return (-1);
}

void	find_access_path(char *simplecmd, t_command *cmd)
{
	if (access (simplecmd, F_OK) == 0)
	{
		cmd->access_path = ft_strdup(simplecmd);
		return ;
	}
	if (find_access_path2(cmd, simplecmd) == -1)
	{
		cmd->access_path = NULL;
		cmd->error_code = 127;
		printf("command not found : %s\n", simplecmd);
	}
}
