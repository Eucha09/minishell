/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:31:32 by yim               #+#    #+#             */
/*   Updated: 2023/02/17 13:36:48 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_ep_first(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = find_key(str);
	if (!ft_isalpha(str[0]))
	{
		if (str[0] != '_')
		{
			free(tmp);
			return (code_error("export: not an identifier", 1));
		}
	}
	while (tmp[i])
	{
		if (!ft_isalnum(tmp[i]) && tmp[i] != '_' && tmp[i] != '=')
		{
			free(tmp);
			return (code_error("export: not an identifier", 1));
		}
		i++;
	}
	free(tmp);
	return (CODE_OK);
}

char	*find_key(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (!(str[i] == '=' || str[i] == '\0'))
		i++;
	result = ft_substr(str, 0, i);
	if (result == NULL)
		return (NULL);
	return (result);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}

void	sorting_envp2(char ***sort_envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while ((*sort_envp)[i])
	{
		j = 0;
		while ((*sort_envp)[j])
		{
			if (ft_strcmp((*sort_envp)[i], (*sort_envp)[j]) < 0)
			{
				tmp = (*sort_envp)[i];
				(*sort_envp)[i] = (*sort_envp)[j];
				(*sort_envp)[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**sorting_envp(char **envp)
{
	int		i;
	char	**sort_envp;

	i = 0;
	while (envp[i])
		i++;
	sort_envp = (char **)malloc (sizeof(char *) * (i + 1));
	if (sort_envp == NULL)
		return (NULL);
	while (i >= 0)
	{
		sort_envp[i] = envp[i];
		i--;
	}
	sorting_envp2(&sort_envp);
	return (sort_envp);
}
