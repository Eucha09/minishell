/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:07:56 by yim               #+#    #+#             */
/*   Updated: 2023/02/16 17:25:39 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*find_home(char **envp)
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

int	check_cd(char **cwd, char **c_dir, char **envp, char *str)
{
	char	*home;

	if (str == NULL)
	{
		home = find_home(envp);
		if (home == NULL)
			return (code_error("cd: HOME not set", 1));
		*c_dir = ft_strdup(home);
		if (*c_dir == NULL)
			return (code_error("malloc error", 1));
	}
	else if (str[0] == '/')
	{
		free (*cwd);
		*cwd = ft_strdup("/");
		if (cwd == NULL)
			return (code_error("malloc error", 1));
	}
	return (CODE_OK);
}

int	cd2(char **str_slash, char **c_dir, char *str, char *cwd)
{
	if (str)
	{
		*str_slash = ft_strjoin("/", str);
		if (*str_slash == NULL)
			return (free_cd_error("malloc error", cwd, NULL));
		*c_dir = ft_strjoin(cwd, *str_slash);
		if (*c_dir == NULL)
			return (free_cd_error("malloc error", cwd, *str_slash));
	}
	return (CODE_OK);
}

void	change_envp(char **envp, char *old_pwd)
{
	char	*cwd;
	char	*tmp;
	char	*tmp2;

	if (check_key_double(envp, "PWD"))
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
			perror ("getcwd error");
		tmp = "PWD=";
		tmp2 = ft_strjoin(tmp, cwd);
		if (tmp2 == NULL)
			perror ("malloc error");
		ep_change_envp(envp, tmp2);
		free_cd(NULL, cwd, tmp2, "free");
	}
	if (check_key_double(envp, "OLDPWD"))
	{
		tmp = "OLDPWD=";
		tmp2 = ft_strjoin(tmp, old_pwd);
		if (tmp2 == NULL)
			perror ("malloc error");
		ep_change_envp(envp, tmp2);
		free (tmp2);
	}
}

int	cd(char **envp, char *str)
{
	char	*cwd;
	char	*c_dir;
	char	*old_pwd;
	char	*str_slash;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		code_error("getcwd: cannot access parent directories", 1);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		free_cd_error(NULL, cwd, NULL);
	if (check_cd(&cwd, &c_dir, envp, str) == CODE_ERROR)
		return (free_cd_error(old_pwd, cwd, NULL));
	if (cd2(&str_slash, &c_dir, str, cwd) == CODE_ERROR)
		return (CODE_ERROR);
	if (chdir(c_dir) == 0)
		change_envp(envp, old_pwd);
	else
		perror("cd");
	free_cd (cwd, c_dir, str_slash, str);
	free (old_pwd);
	return (CODE_OK);
}
