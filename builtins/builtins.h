/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:25:26 by yim               #+#    #+#             */
/*   Updated: 2023/01/29 17:12:18 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

# define CODE_ERROR 1
# define CODE_OK 0
# define TRUE 1
# define FALSE 0

//error
int		code_error(char *str);
//cd
int		cd(char *str, char **envp);
int		pwd(void);
//export
int		print_envp(char **envp);
int		ft_strcmp(char *s1, char *s2);
char	*find_key(char *str);
int		check_ep_first(char *str);
int		check_key_double(char **envp, char *str);
int		export(char **envp, char *str);
int		ep_find_sort(char **envp, char *str);
//env
int		env(char **envp);
//unset
int		unset(char **envp, char *str);
#endif