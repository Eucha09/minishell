/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:25:26 by yim               #+#    #+#             */
/*   Updated: 2023/02/13 20:35:28 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# include "minishell.h"

# define CODE_ERROR 1
# define CODE_OK 0
# define TRUE 1
# define FALSE 0

//error
int		code_error(char *str);
int		free_code_error(char *free_str, int i);
//cd
int		cd(char **envp, char *str);
int		pwd(int file_out_fd);
//export
int		print_envp(char **envp, int	file_out_fd);
int		ft_strcmp(char *s1, char *s2);
char	*find_key(char *str);
int		check_ep_first(char *str);
int		check_key_double(char **envp, char *str);
int		ep_find_sort(char **envp, char *str);
char	**sorting_envp(char **envp);
int		ep_change_envp(char **envp, char *str);
int		export(char **envp, char **cmd, int file_out_fd);
//env
int		env(char **envp, int file_out_fd);
//unset
int		unset(char **envp, char **cmd);
//echo
int		echo(char **cmd, int file_out_fd);
//exit
int		ft_exit(t_command *cmd);
#endif