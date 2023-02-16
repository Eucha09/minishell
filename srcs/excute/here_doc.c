/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:24:38 by yim               #+#    #+#             */
/*   Updated: 2023/02/16 20:46:02 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	make_here_doc3(char *limiter, int fd, char *line)
{
	set_signal(DFL, IGN);
	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	exit(EXIT_SUCCESS);
}

int	make_here_doc2(char *limiter, int fd)
{
	char	*line;
	int		status;
	pid_t	pid;

	line = NULL;
	set_signal(IGN, IGN);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		make_here_doc3(limiter, fd, line);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		termsig_handler(WTERMSIG(status));
		sig_errno(WTERMSIG(status));
		set_signal(HDL, IGN);
		return (-1);
	}
	set_signal(HDL, IGN);
	return (0);
}

int	make_here_doc(char *limiter_bf)
{
	int		fd;
	int		flag;
	char	*limiter;

	limiter = ft_strjoin(limiter_bf, "\n");
	if (limiter == NULL)
		return (-1);
	fd = open("tmp_here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free (limiter);
		return (-1);
	}
	flag = make_here_doc2(limiter, fd);
	free (limiter);
	fd = open("tmp_here_doc", O_RDONLY);
	if (fd == -1)
	{
		unlink("tmp_here_doc");
		return (-1);
	}
	unlink("tmp_here_doc");
	if (flag)
		return (flag);
	return (fd);
}
