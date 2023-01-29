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

int	print_envp(char **envp)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (envp[i])
	{
		tmp = find_key(envp[i]);
		if (tmp == NULL)
			return (code_error("malloc error"));
		tmp2 = ft_strchr(envp[i], '=');
		if (tmp2 == NULL)
			printf("declare -x %s", envp[i]);
		else
			printf("declare -x %s=\"%s\"\n", tmp, tmp2 + 1);
		free (tmp);
		i++;
	}
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
			free(envp_key);
			free(str_key);
			envp[i] = str;
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

	i = 0;
	str_key = find_key(str);
	while (envp[i])
	{
		envp_key = find_key(envp[i]);
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

	while (envp[i])
		i++;
	envp[i] = str;
	envp[i + 1] = NULL;
}

int	export(char **envp, char *str)
{
	if (str == NULL)
		return (print_envp(envp));
	if (check_ep_first(str) == CODE_ERROR)
		return (code_error("export: not an identifier"));
	if (check_key_double(envp, str))
	{
		if (!ft_strchr(str, '='))
			return (CODE_OK);
		if (ep_change_envp(envp, str) == CODE_ERROR)
			return (CODE_ERROR);
	}
	else
		add_envp(envp, str);
	return (CODE_OK);
}
