/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:57:00 by yim               #+#    #+#             */
/*   Updated: 2023/01/27 20:48:02 by yim              ###   ########.fr       */
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
		tmp = before_equal(envp[i]);
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

void	change_envp(char ***envp, char *str)
{
	int		i;
	char	*envp_key;
	char	*str_key;

	i = 0;
	str_key = before_equal(str);
	while ((*envp)[i])
	{
		envp_key = before_equal((*envp)[i]);
		if (!ft_strcmp(str_key, envp_key))
		{
			free(envp_key);
			free(str_key);
			(*envp)[i] = str;
		}
		free(envp_key);
		i++;
	}
	free(str_key);
}

int	check_key_double(char **envp, char *str)
{
	char	*envp_key;
	char	*str_key;
	int		i;

	i = 0;
	str_key = before_equal(str);
	while (envp[i])
	{
		envp_key = before_equal(envp[i]);
		if (!ft_strcmp(envp_key, str_key))
		{
			free(envp_key);
			free(str_key);
			return (TRUE);
		}
		free(envp_key);
		i++;
	}
	free(str_key);
	return (FALSE);
}

void	add_envp(char ***envp, char *str)
{
	int		i;
	char	**new_envp;

	i = 0;
	while ((*envp)[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	new_envp[i] = str;
	new_envp[i + 1] = NULL;
	while (--i >= 0)
		new_envp[i] = (*envp)[i];
	// free(*envp);
	// 나중에 envp인자 받자마자 malloc해서 복사해두고 메인 마지막에서 free?
	*envp = new_envp;
}

//export만 쳤을 경우, 즉 str가 NULL일 경우 envp 출력
//key값의 첫 글자가 _와 영어가 아니면 "export: not an identifier"오류 1 return
//key값이 있는 경우 value 바꿈, 만약 value가 없을 경우 무시
//key값이 없는 경우 envp에 추가
int	export(char ***envp, char *str)
{
	if (str == NULL)
		return (print_envp(*envp));
	if (check_ep_first(str) == CODE_ERROR)
		return (code_error("export: not an identifier"));
	if (check_key_double(*envp, str))
	{
		if (!ft_strchr(str, '='))
			return (CODE_OK);
		change_envp(envp, str);
	}
	else
		add_envp(envp, str);
	return (CODE_OK);
}
