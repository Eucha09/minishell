/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:57:00 by yim               #+#    #+#             */
/*   Updated: 2023/01/29 17:14:21by yim              ###   ########.fr       */
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
				return (code_error("malloc error"));
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
		return (code_error("malloc error"));
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
		return (code_error("malloc error"));
	while (envp[i])
	{
		envp_key = find_key(envp[i]);
		if (str_key == NULL)
			return (code_error("malloc error"));
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

int	export(char **envp, char **cmd, int file_out_fd)
{
	int		i;
	char	*str;

	i = 1;
	if (cmd[1] == NULL)
		return (print_envp(envp, file_out_fd));
	while (cmd[i])
	{
		str = cmd[i];
		if (check_ep_first(str) == CODE_ERROR)
			return (code_error("export: not an identifier"));
		if (check_key_double(envp, str) == -1)
			return (code_error("malloc error"));
		if (check_key_double(envp, str))
		{
			if (!ft_strchr(str, '='))
				return (CODE_OK);
			if (ep_change_envp(envp, str) == CODE_ERROR)
				return (CODE_ERROR);
		}
		else
			add_envp(envp, str);
		i++;
	}
	return (CODE_OK);
}
