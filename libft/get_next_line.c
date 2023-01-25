/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:05:12 by yim               #+#    #+#             */
/*   Updated: 2023/01/16 15:46:06 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_str(char **back_up, char *buf)
{
	char	*result;
	char	*tmp;
	size_t	back_len;
	size_t	buf_len;

	if (*back_up == NULL)
		return (gnl_ft_strdup(buf));
	else
	{
		back_len = gnl_ft_strlen(*back_up);
		buf_len = gnl_ft_strlen(buf);
		result = (char *)malloc(sizeof(char) * (back_len + buf_len + 1));
		if (result == NULL)
			return (NULL);
		gnl_ft_memcpy(result, *back_up, back_len);
		gnl_ft_memcpy(result + back_len, buf, buf_len);
		result[back_len + buf_len] = '\0';
		tmp = *back_up;
		free(tmp);
		return (result);
	}
}

char	*return_check_read_size(char **back_up, int read_size, char **buf)
{
	char	*tmp;

	if (read_size == -1)
	{
		free(*buf);
		tmp = *back_up;
		*back_up = NULL;
		free(tmp);
		return (NULL);
	}
	else
		return (return_one_line(back_up, buf));
}

char	*return_one_line(char **back_up, char **buf)
{
	int		i;
	char	*result;
	char	*after;
	char	*tmp;

	free(*buf);
	if (*back_up == NULL)
		return (NULL);
	i = check_newline(*back_up, '\n');
	if (i > 0)
	{
		result = gnl_ft_substr(*back_up, 0, i);
		after = gnl_ft_substr(*back_up, i, gnl_ft_strlen(*back_up) - i);
		tmp = *back_up;
		*back_up = after;
		free(tmp);
		return (result);
	}
	else
	{
		tmp = *back_up;
		*back_up = NULL;
		return (tmp);
	}
}

char	*get_next_line(int fd)
{
	int			read_size;
	char		*buf;
	static char	*back_up[OPEN_MAX] = {0, };

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	while (1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1 || read_size == 0)
			break ;
		buf[read_size] = '\0';
		back_up[fd] = add_str(&(back_up[fd]), buf);
		if (back_up[fd] == NULL)
		{
			free(buf);
			return (NULL);
		}
		if (check_newline(back_up[fd], '\n') > 0)
			return (return_one_line(&(back_up[fd]), &buf));
	}
	return (return_check_read_size(&(back_up[fd]), read_size, &buf));
}
