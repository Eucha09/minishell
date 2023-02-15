/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:24:38 by yim               #+#    #+#             */
/*   Updated: 2023/02/14 16:28:32 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

#include "unistd.h"

int	make_here_doc3(char *limiter, int fd, char *line)
{
	set_signal(SIG_HEREDOC_CHILD);
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
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		make_here_doc3(limiter, fd, line);
	set_signal(SIG_HEREDOC_PARENT);
	waitpid(-1, &status, 0);
	set_signal(SIG_SHELL);
	return (0);
}

int	make_here_doc(char *limiter_bf)
{
	int		fd;
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
	if (make_here_doc2(limiter, fd))
		return (-1);
	free (limiter);
	fd = open("tmp_here_doc", O_RDONLY);
	if (fd == -1)
	{
		unlink("tmp_here_doc");
		return (-1);
	}
	unlink("tmp_here_doc");
	return (fd);
}