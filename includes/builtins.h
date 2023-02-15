/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:25:26 by yim               #+#    #+#             */
/*   Updated: 2023/02/15 14:35:17 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//# include "minishell.h"
# include "error.h"

# define CODE_ERROR 1
# define CODE_OK 0
# define TRUE 1
# define FALSE 0

//error
int		free_code_error(char *free_str, int i);
//cd
int		cd(char **envp, char *str);
int		pwd(int file_out_fd);
void	free_cd(char *cwd, char *c_dir, char *str_slash, char *str);
int		free_cd_error(char *str, char *cwd, char *str_slash);
//export
int		print_envp(char **envp, int file_out_fd);
int		ft_strcmp(char *s1, char *s2);
char	*find_key(char *str);
int		check_ep_first(char *str);
int		check_key_double(char **envp, char *str);
int		ep_find_sort(char **envp, char *str);
char	**sorting_envp(char **envp);
int		ep_change_envp(char **envp, char *str);
int		export(char **envp, char **cmd, int file_out_fd);
void	add_envp(char **envp, char *str);
int		check_key_double(char **envp, char *str);
//env
int		env(char **envp, int file_out_fd);
//unset
int		unset(char **envp, char **cmd);
//echo
int		echo(char **cmd, int file_out_fd);
//exit
void	ft_exit(t_command *cmd);
#endif