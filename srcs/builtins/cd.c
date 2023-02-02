/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:07:56 by yim               #+#    #+#             */
/*   Updated: 2023/01/29 21:33:39 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	free_cd(char *cwd, char *c_dir, char *str_slash)
{
	free (cwd);
	free (c_dir);
	free (str_slash);
}

static int	free_cd_error(char *str, char *cwd, char *str_slash)
{
	free (cwd);
	if (str_slash != NULL)
		free(str_slash);
	if (str != NULL)
		perror(str);
	return (CODE_ERROR);
}

static char	*find_home(char **envp)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
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

	if (*str == NULL || (*str)[0] == '~')
	{
		home = find_home(envp);
		if (home == NULL)
			return (code_error("cd: HOME not set"));
		free (*cwd);
		*cwd = ft_strdup(home);
		if (cwd == NULL)
			return (code_error("malloc error"));
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
			return (code_error("malloc error"));
	}
	return (CODE_OK);
}

int	cd(char **envp, char *str)
{
	char	*cwd;
	char	*c_dir;
	char	*str_slash;
	int		result;

	cwd = (char *)malloc(sizeof(char) * 1024);
	if (cwd == NULL)
		return (code_error("malloc error"));
	ft_memset(cwd, 0, sizeof(char) * 1024);
	getcwd(cwd, sizeof(char) * 1024);
	if (check_cd(&cwd, envp, &str) == CODE_ERROR)
		return (free_cd_error(NULL, cwd, NULL));
	str_slash = ft_strjoin("/", str);
	if (str_slash == NULL)
		return (free_cd_error("malloc error", cwd, NULL));
	c_dir = ft_strjoin(cwd, str_slash);
	if (c_dir == NULL)
		return (free_cd_error("malloc error", cwd, str_slash));
	result = chdir(c_dir);
	if (result == CODE_ERROR)
		perror("cd");
	free_cd (cwd, c_dir, str_slash);
	return (CODE_OK);
}
