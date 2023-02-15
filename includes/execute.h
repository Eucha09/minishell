/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:06:14 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/15 14:39:00 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "astree.h"
# include "command.h"
# include "builtins.h"
# include "sig.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

int		free_return(char *tmp, char *tmp2, int num);
void	execute(t_astnode *astree, char *envp[]);
void	find_access_path(char *simplecmd, t_command *cmd);
int		check_builtins(char *simplecmd);
//here_doc
int		make_here_doc(char *limiter_bf);
int		make_here_doc2(char *limiter, int fd);
//execve
void	rezero_cmd(t_command *cmd);
int		cmd_error_check(t_command *cmd);
void	excute_first_builtins(t_command *cmd, char **envp, int fd[2]);
void	execve_command(t_command *cmd, char **envp);
//free
void	find_access_path(char *simplecmd, t_command *cmd);
void	free_double_array(char **double_array);
//excute2
void	wait_all(t_command *cmd);
void	execute_ioredirect(t_astnode *astree, t_command *cmd);
void	execute_cmdsuffix(t_astnode *astree, t_command *cmd, char *envp[]);
//execve2
void	rezero_cmd(t_command *cmd);
int		cmd_error_check(t_command *cmd);
void	excute_builtins(t_command *cmd, char **envp);
void	execve_child(t_command *cmd, int fd[2], char **envp);
void	execve_child2(t_command *cmd, int fd[2], char **envp);
#endif