/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:09:56 by yim               #+#    #+#             */
/*   Updated: 2023/02/15 14:45:21 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int	g_errno;

int	print_envp2(int file_out_fd, char **sort_envp)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = -1;
	while (sort_envp[++i])
	{
		tmp2 = ft_strchr(sort_envp[i], '=');
		ft_putstr_fd("declar -x ", file_out_fd);
		if (tmp2 == NULL)
			ft_putstr_fd(sort_envp[i], file_out_fd);
		else
		{
			tmp = find_key(sort_envp[i]);
			if (tmp == NULL)
				return (code_error("malloc error", 1));
			ft_putstr_fd(tmp, file_out_fd);
			ft_putstr_fd("=\"", file_out_fd);
			ft_putstr_fd(tmp2 + 1, file_out_fd);
			ft_putstr_fd("\"", file_out_fd);
			free (tmp);
		}
		ft_putstr_fd("\n", file_out_fd);
	}
	return (CODE_OK);
}

int	print_envp(char **envp, int file_out_fd)
{
	char	**sort_envp;

	sort_envp = sorting_envp(envp);
	if (sort_envp == NULL)
		return (code_error("malloc error", 1));
	if (print_envp2(file_out_fd, sort_envp) == CODE_ERROR)
	{
		free (sort_envp);
		return (CODE_ERROR);
	}
	free (sort_envp);
	return (CODE_OK);
}

int	ep_change_envp(char **envp, char *str)
{
	int		i;
	char	*envp_key;
	char	*str_key;

	i = 0;
	str_key = find_key(str);
	if (str_key == NULL)
		return (code_error("malloc error", 1));
	while (envp[i])
	{
		envp_key = find_key(envp[i]);
		if (str_key == NULL)
			return (code_error("malloc error", 1));
		if (!ft_strcmp(str_key, envp_key))
		{
			free_return(envp_key, str_key, 0);
			free (envp[i]);
			envp[i] = ft_strdup(str);
			return (CODE_OK);
		}
		free(envp_key);
		i++;
	}
	free(str_key);
	return (CODE_OK);
}

int	export2(int i, char **cmd, char **envp)
{
	char	*str;

	while (cmd[i])
	{
		str = cmd[i];
		if (check_ep_first(str) == CODE_ERROR)
			return (code_error("export: not an identifier", 1));
		if (check_key_double(envp, str) == -1)
			return (code_error("malloc error", 1));
		if (check_key_double(envp, str))
		{
			if (!ft_strchr(str, '='))
			{
				i++;
				continue ;
			}
			if (ep_change_envp(envp, str) == CODE_ERROR)
				return (CODE_ERROR);
		}
		else
			add_envp(envp, str);
		i++;
	}
	return (CODE_OK);
}

int	export(char **envp, char **cmd, int file_out_fd)
{
	int		i;

	i = 1;
	if (cmd[1] == NULL)
		return (print_envp(envp, file_out_fd));
	if (export2(i, cmd, envp) == CODE_ERROR)
		return (CODE_ERROR);
	return (CODE_OK);
}
