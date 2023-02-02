/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:24:38 by yim               #+#    #+#             */
/*   Updated: 2023/02/02 17:35:40 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

int	make_here_doc2(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	fd = open("tmp_here_doc", O_RDONLY);
	if (fd == -1)
	{
		unlink("tmp_here_doc");
		return (-1);
	}
	return (fd);
}

int	make_here_doc(char *limiter_bf)
{
	int		fd;
	int		file_in_fd;
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
	file_in_fd = make_here_doc2(limiter, fd);
	free (limiter);
	return (file_in_fd);
}
