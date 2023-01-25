/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:07:56 by yim               #+#    #+#             */
/*   Updated: 2023/01/25 19:48:10 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cd(char *cwd, char *c_dir, char *str_slash)
{
	free (cwd);
	free (c_dir);
	free (str_slash);
}

static void	free_cd_error(char *str, char *cwd)
{
	free (cwd);
	perror(str);
}

static char	*find_home(char **envp)
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

static int	check_cd(char **cwd, char **envp, char **str)
{
	char	*home;

	home = find_home(envp);
	if (*str == NULL || (*str)[0] == '~')
	{
		free (*cwd);
		*cwd = ft_strdup(home);
		if (cwd == NULL)
			return (CODE_ERROR);
		if (*str == NULL)
			*str = "";
		if (*str != NULL)
			(*str)++;
	}
	if (*str[0] == '/')
	{
		free (*cwd);
		*cwd = ft_strdup("/");
		if (cwd == NULL)
			return (CODE_ERROR);
	}
	return (CODE_OK);
}

void	cd(char *str, char **envp)
{
	char	*cwd;
	char	*c_dir;
	char	*str_slash;
	int		result;

	cwd = (char *)malloc(sizeof(char) * 1024);
	if (cwd == NULL)
		return (perror("malloc error"));
	ft_memset(cwd, 0, sizeof(char) * 1024);
	getcwd(cwd, sizeof(char) * 1024);
	if (check_cd(&cwd, envp, &str) == CODE_ERROR)
		return (free_cd_error("malloc error", cwd));
	str_slash = ft_strjoin("/", str);
	if (str_slash == NULL)
		return (free_cd_error("malloc error", cwd));
	c_dir = ft_strjoin(cwd, str_slash);
	if (c_dir == NULL)
	{
		free (str_slash);
		return (free_cd_error("malloc error", cwd));
	}
	result = chdir(c_dir);
	if (result == CODE_ERROR)
		perror("cd error");
	free_cd (cwd, c_dir, str_slash);
}
