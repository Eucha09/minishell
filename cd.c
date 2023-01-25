/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:07:56 by yim               #+#    #+#             */
/*   Updated: 2023/01/25 19:11:28 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}

char	*find_home(char **envp)
{
	int		i;
	char	*home;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("HOME=", envp[i], 5) == 0)
			home = envp[i] + 5;
		i++;
	}
	return (home);
}

void	check_cd_error(char **cwd, char **envp, char **str)
{
	char	*home;

	home = find_home(envp);
	if (*str == NULL || (*str)[0] == '~')
	{
		free (*cwd);
		*cwd = ft_strdup(home);
		if (*str == NULL)
			*str = "";
		if (*str != NULL)
			(*str)++;
	}
	if (*str[0] == '/')
	{
		free (*cwd);
		*cwd = ft_strdup("/");
	}
}

void	cd(char *str, char **envp)
{
	char	*cwd;
	char	*c_dir;
	char	*str_slash;
	int		result;

	cwd = (char *)malloc(sizeof(char) * 1024);
	ft_memset(cwd, 0, sizeof(char) * 1024);
	getcwd(cwd, sizeof(char) * 1024);
	check_cd_error(&cwd, envp, &str);
	str_slash = ft_strjoin("/", str);
	c_dir = ft_strjoin(cwd, str_slash);
	result = chdir(c_dir);
	if (result == CODE_ERROR)
		perror("cd error");
	free (cwd);
	free (c_dir);
	free (str_slash);
}
